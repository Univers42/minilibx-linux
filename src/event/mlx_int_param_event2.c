/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_int_param_event2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/09 14:58:21 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

static int	mlx_param_motion(t_xvar *xvar, XEvent *ev, t_win_list *win)
{
	(void)xvar;
	win->hooks[MotionNotify].hook(ev->xbutton.x, ev->xbutton.y,
		win->hooks[MotionNotify].param);
	return (0);
}

static int	mlx_param_expose(t_xvar *xvar, XEvent *ev, t_win_list *win)
{
	(void)xvar;
	if (!ev->xexpose.count)
		win->hooks[Expose].hook(win->hooks[Expose].param);
	return (0);
}

int	mlx_int_param_generic(t_xvar *xvar, XEvent *ev, t_win_list *win)
{
	(void)xvar;
	win->hooks[ev->type].hook(win->hooks[ev->type].param);
	return (0);
}

static void	init_param_events(t_param_fn *tab)
{
	int	i;

	i = 0;
	while (i < 36)
	{
		tab[i] = mlx_int_param_generic;
		i++;
	}
	tab[0] = mlx_int_param_undef;
	tab[1] = mlx_int_param_undef;
	tab[2] = mlx_int_param_keypress;
	tab[3] = mlx_int_param_keyrelease;
	tab[4] = mlx_int_param_btnpress;
	tab[5] = mlx_int_param_btnrelease;
	tab[6] = mlx_param_motion;
	tab[12] = mlx_param_expose;
}

t_param_fn	*mlx_get_param_events(void)
{
	static t_param_fn	tab[36];
	static int			init;

	if (!init)
	{
		init_param_events(tab);
		init = 1;
	}
	return (tab);
}
