/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_draw_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/09 13:36:39 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_ext_int.h"

void	mlx_ext_bres_init(t_mlx_bres *b, t_mlx_line *ln)
{
	b->dx = mlx_abs_i(ln->x1 - ln->x0);
	b->dy = mlx_abs_i(ln->y1 - ln->y0);
	b->sx = -1;
	if (ln->x0 < ln->x1)
		b->sx = 1;
	b->sy = -1;
	if (ln->y0 < ln->y1)
		b->sy = 1;
	b->err = b->dx - b->dy;
	b->steps = mlx_max_i(b->dx, b->dy);
	b->step = 0;
	b->cr = 0.0f;
	b->cg = 0.0f;
	b->cb = 0.0f;
}

static void	init_color_deltas(t_mlx_bres *b, t_mlx_line *ln)
{
	float	inv;

	if (b->steps <= 0)
		return ;
	inv = 1.0f / (float)b->steps;
	b->cr = inv * (float)(mlx_get_r(ln->col1) - mlx_get_r(ln->col0));
	b->cg = inv * (float)(mlx_get_g(ln->col1) - mlx_get_g(ln->col0));
	b->cb = inv * (float)(mlx_get_b(ln->col1) - mlx_get_b(ln->col0));
}

int	mlx_ext_bres_color(t_mlx_line *ln, t_mlx_bres *b)
{
	int	r;
	int	g;
	int	bv;

	r = mlx_clamp_i(mlx_get_r(ln->col0) + (int)(b->cr * b->step), 0, 255);
	g = mlx_clamp_i(mlx_get_g(ln->col0) + (int)(b->cg * b->step), 0, 255);
	bv = mlx_clamp_i(mlx_get_b(ln->col0) + (int)(b->cb * b->step), 0, 255);
	return (mlx_rgb(r, g, bv));
}

void	mlx_draw_line(t_mlx_fb *fb, t_mlx_line *ln)
{
	t_mlx_bres	b;

	if (!fb || !ln)
		return ;
	mlx_ext_bres_init(&b, ln);
	init_color_deltas(&b, ln);
	mlx_buf_pixel_put(fb, ln->x0, ln->y0, ln->col0);
	while (b.step < b.steps)
	{
		b.step++;
		if (b.err * 2 > -b.dy)
		{
			b.err -= b.dy;
			ln->x0 += b.sx;
		}
		if (b.err * 2 < b.dx)
		{
			b.err += b.dx;
			ln->y0 += b.sy;
		}
		mlx_buf_pixel_put(fb, ln->x0, ln->y0,
			mlx_ext_bres_color(ln, &b));
	}
}
