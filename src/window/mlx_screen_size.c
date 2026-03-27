/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_screen_size.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/09 12:39:23 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

int	mlx_get_screen_size(void *mlx_ptr, int *sizex, int *sizey)
{
	XWindowAttributes	xwa;
	t_xvar				*xvar;

	xvar = mlx_ptr;
	XGetWindowAttributes(xvar->display, xvar->root, &xwa);
	*sizex = xwa.width;
	*sizey = xwa.height;
	return (0);
}
