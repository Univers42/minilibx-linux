/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_new_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/09 12:39:21 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

static void	mlx_setup_win_attrs(t_xvar *xvar, XSetWindowAttributes *xswa)
{
	xswa->background_pixel = 0;
	xswa->border_pixel = -1;
	xswa->colormap = xvar->cmap;
	xswa->event_mask = 0xFFFFFF;
}

static void	mlx_setup_win_gc(t_xvar *xvar, t_win_list *win)
{
	XGCValues	xgcv;

	xgcv.foreground = -1;
	xgcv.function = GXcopy;
	xgcv.plane_mask = AllPlanes;
	win->gc = XCreateGC(xvar->display, win->window,
			GCFunction | GCPlaneMask | GCForeground, &xgcv);
}

void	*mlx_new_window(t_xvar *xvar, int size_x, int size_y, char *title)
{
	t_win_list				*new_win;
	XSetWindowAttributes	xswa;

	mlx_setup_win_attrs(xvar, &xswa);
	new_win = malloc(sizeof(*new_win));
	if (!new_win)
		return ((void *)0);
	new_win->window = XCreateWindow(xvar->display, xvar->root,
			0, 0, size_x, size_y, 0, CopyFromParent, InputOutput,
			xvar->visual, CWEventMask | CWBackPixel
			| CWBorderPixel | CWColormap, &xswa);
	mlx_int_anti_resize_win(xvar, new_win->window, size_x, size_y);
	XStoreName(xvar->display, new_win->window, title);
	XSetWMProtocols(xvar->display, new_win->window,
		&(xvar->wm_delete_window), 1);
	mlx_setup_win_gc(xvar, new_win);
	new_win->next = xvar->win_list;
	xvar->win_list = new_win;
	memset(&(new_win->hooks), 0, sizeof(new_win->hooks));
	XMapRaised(xvar->display, new_win->window);
	mlx_int_wait_first_expose(xvar, new_win->window);
	return (new_win);
}
