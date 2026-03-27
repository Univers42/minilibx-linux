/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_color_ops.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/08 17:34:51 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_ext.h"

static int	lerp_ch(int c1, int c2, float t, int shift)
{
	int	a;
	int	b;
	int	v;

	a = (c1 >> shift) & 0xFF;
	b = (c2 >> shift) & 0xFF;
	v = a + (int)((b - a) * t);
	if (v < 0)
		v = 0;
	if (v > 255)
		v = 255;
	return (v);
}

int	mlx_lerp_color(int c1, int c2, float t)
{
	int	r;
	int	g;
	int	b;

	if (t <= 0.0f)
		return (c1);
	if (t >= 1.0f)
		return (c2);
	r = lerp_ch(c1, c2, t, 16);
	g = lerp_ch(c1, c2, t, 8);
	b = lerp_ch(c1, c2, t, 0);
	return ((r << 16) | (g << 8) | b);
}

int	mlx_blend_alpha(int fg, int bg)
{
	int	a;
	int	ch[3];

	a = mlx_get_a(fg);
	if (a == 0)
		return (bg);
	if (a == 255)
		return (fg);
	ch[0] = (mlx_get_r(fg) * a + mlx_get_r(bg) * (255 - a)) / 255;
	ch[1] = (mlx_get_g(fg) * a + mlx_get_g(bg) * (255 - a)) / 255;
	ch[2] = (mlx_get_b(fg) * a + mlx_get_b(bg) * (255 - a)) / 255;
	return (mlx_rgb(ch[0], ch[1], ch[2]));
}

int	mlx_color_darken(int color, float f)
{
	int	r;
	int	g;
	int	b;

	f = mlx_clamp_f(f, 0.0f, 1.0f);
	r = (int)(mlx_get_r(color) * f);
	g = (int)(mlx_get_g(color) * f);
	b = (int)(mlx_get_b(color) * f);
	return (mlx_rgb(r, g, b));
}

int	mlx_color_brighten(int color, float f)
{
	int	r;
	int	g;
	int	b;

	r = mlx_clamp_i(mlx_get_r(color) + (int)(255 * f), 0, 255);
	g = mlx_clamp_i(mlx_get_g(color) + (int)(255 * f), 0, 255);
	b = mlx_clamp_i(mlx_get_b(color) + (int)(255 * f), 0, 255);
	return (mlx_rgb(r, g, b));
}
