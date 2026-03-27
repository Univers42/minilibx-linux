/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_color_pack.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/08 17:34:53 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_ext.h"

int	mlx_rgba(int r, int g, int b, int a)
{
	return ((a & 0xFF) << 24 | (r & 0xFF) << 16
		| (g & 0xFF) << 8 | (b & 0xFF));
}

int	mlx_rgb(int r, int g, int b)
{
	return (mlx_rgba(r, g, b, 0xFF));
}

int	mlx_get_r(int color)
{
	return ((color >> 16) & 0xFF);
}

int	mlx_get_g(int color)
{
	return ((color >> 8) & 0xFF);
}

int	mlx_get_b(int color)
{
	return (color & 0xFF);
}
