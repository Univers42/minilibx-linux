/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_pixel_put.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/09 14:19:28 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mlx_int.h"

int	mlx_pixel_put(void *mlx_ptr, void *win_ptr,
		t_mlx_point pos, int color)
{
	t_xvar		*xvar;
	t_win_list	*win;
	XGCValues	xgcv;

	xvar = (t_xvar *)mlx_ptr;
	win = (t_win_list *)win_ptr;
	xgcv.foreground = mlx_int_get_good_color(xvar, color);
	XChangeGC(xvar->display, win->gc, GCForeground, &xgcv);
	XDrawPoint(xvar->display, win->window, win->gc, pos.x, pos.y);
	if (xvar->do_flush)
		XFlush(xvar->display);
	return (0);
}
