/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_string_put.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/09 14:19:28 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mlx_int.h"

int	mlx_string_put(void *mlx_ptr, void *win_ptr,
		t_mlx_str txt, char *string)
{
	t_xvar		*xvar;
	t_win_list	*win;
	XGCValues	xgcv;

	xvar = (t_xvar *)mlx_ptr;
	win = (t_win_list *)win_ptr;
	xgcv.foreground = mlx_int_get_good_color(xvar, txt.color);
	XChangeGC(xvar->display, win->gc, GCForeground, &xgcv);
	XDrawString(xvar->display, win->window, win->gc,
		txt.x, txt.y, string, strlen(string));
	if (xvar->do_flush)
		XFlush(xvar->display);
	return (0);
}
