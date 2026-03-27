/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/09 12:23:25 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

static int	mlx_init_visual(t_xvar *xvar)
{
	if (mlx_int_get_visual(xvar) == -1)
	{
		free(xvar);
		return (0);
	}
	return (1);
}

static void	mlx_init_atoms(t_xvar *xvar)
{
	xvar->wm_delete_window = XInternAtom(xvar->display,
			"WM_DELETE_WINDOW", False);
	xvar->wm_protocols = XInternAtom(xvar->display,
			"WM_PROTOCOLS", False);
}

static void	mlx_init_defaults(t_xvar *xvar)
{
	xvar->win_list = 0;
	xvar->loop_hook = 0;
	xvar->loop_param = (void *)0;
	xvar->do_flush = 1;
	xvar->end_loop = 0;
}

void	*mlx_init(void)
{
	t_xvar	*xvar;

	xvar = malloc(sizeof(*xvar));
	if (!xvar)
		return ((void *)0);
	xvar->display = XOpenDisplay("");
	if (xvar->display == 0)
	{
		free(xvar);
		return ((void *)0);
	}
	xvar->screen = DefaultScreen(xvar->display);
	xvar->root = DefaultRootWindow(xvar->display);
	xvar->cmap = DefaultColormap(xvar->display, xvar->screen);
	xvar->depth = DefaultDepth(xvar->display, xvar->screen);
	if (!mlx_init_visual(xvar))
		return ((void *)0);
	mlx_init_defaults(xvar);
	mlx_init_atoms(xvar);
	mlx_int_deal_shm(xvar);
	if (xvar->private_cmap)
		xvar->cmap = XCreateColormap(xvar->display, xvar->root,
				xvar->visual, AllocNone);
	mlx_int_rgb_conversion(xvar);
	return (xvar);
}
