/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_window_ext.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/09 13:36:35 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_ext_int.h"

void	*mlx_new_window_ext(void *mlx, t_mlx_point sz, char *t, int flags)
{
	void	*win;

	win = mlx_new_window(mlx, sz.x, sz.y, t);
	if (!win)
		return (NULL);
	if (flags & MLX_WIN_RESIZABLE)
		mlx_int_anti_resize_win((t_xvar *)mlx,
			((t_win_list *)win)->window, 0, 0);
	return (win);
}

void	mlx_set_win_title(void *mlx, void *win, char *title)
{
	t_xvar		*xvar;
	t_win_list	*wl;

	xvar = (t_xvar *)mlx;
	wl = (t_win_list *)win;
	XStoreName(xvar->display, wl->window, title);
	XFlush(xvar->display);
}
