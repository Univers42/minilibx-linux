/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_int_anti_resize_win.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/09 12:39:22 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

int	mlx_int_anti_resize_win(t_xvar *xvar, Window win, int w, int h)
{
	XSizeHints	hints;
	long		supplied;

	XGetWMNormalHints(xvar->display, win, &hints, &supplied);
	hints.width = w;
	hints.height = h;
	hints.min_width = w;
	hints.min_height = h;
	hints.max_width = w;
	hints.max_height = h;
	hints.flags = PPosition | PSize | PMinSize | PMaxSize;
	XSetWMNormalHints(xvar->display, win, &hints);
	return (0);
}
