/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/09 14:58:21 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

static int	win_count(t_xvar *xvar)
{
	int			i;
	t_win_list	*win;

	i = 0;
	win = xvar->win_list;
	while (win)
	{
		win = win->next;
		++i;
	}
	return (i);
}

int	mlx_loop_end(t_xvar *xvar)
{
	xvar->end_loop = 1;
	return (1);
}

static int	mlx_is_close_ev(t_xvar *xvar, XEvent *ev)
{
	if (ev->type != ClientMessage)
		return (0);
	if (ev->xclient.message_type != xvar->wm_protocols)
		return (0);
	if ((Atom)ev->xclient.data.l[0] != xvar->wm_delete_window)
		return (0);
	return (1);
}

static void	mlx_dispatch_ev(t_xvar *xvar, XEvent *ev)
{
	t_win_list	*win;
	t_param_fn	*pe;

	win = xvar->win_list;
	while (win && (win->window != ev->xany.window))
		win = win->next;
	if (!win)
		return ;
	if (mlx_is_close_ev(xvar, ev)
		&& win->hooks[DestroyNotify].hook)
		win->hooks[DestroyNotify].hook(
			win->hooks[DestroyNotify].param);
	pe = mlx_get_param_events();
	if (ev->type < MLX_MAX_EVENT && win->hooks[ev->type].hook)
		pe[ev->type](xvar, ev, win);
}

int	mlx_loop(t_xvar *xvar)
{
	XEvent	ev;

	mlx_int_set_win_event_mask(xvar);
	xvar->do_flush = 0;
	while (win_count(xvar) && !xvar->end_loop)
	{
		while (!xvar->end_loop
			&& (!xvar->loop_hook || XPending(xvar->display)))
		{
			XNextEvent(xvar->display, &ev);
			mlx_dispatch_ev(xvar, &ev);
		}
		XSync(xvar->display, False);
		if (xvar->loop_hook)
			xvar->loop_hook(xvar->loop_param);
	}
	return (0);
}
