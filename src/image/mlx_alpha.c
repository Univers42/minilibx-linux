/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_alpha.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/09 12:39:19 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_ext_int.h"

static void	blit_bounds(t_mlx_fb *dst, t_mlx_fb *src, t_mlx_point p, int *wh)
{
	wh[0] = src->w;
	wh[1] = src->h;
	if (p.x + wh[0] > dst->w)
		wh[0] = dst->w - p.x;
	if (p.y + wh[1] > dst->h)
		wh[1] = dst->h - p.y;
	if (p.x < 0)
		wh[0] += p.x;
	if (p.y < 0)
		wh[1] += p.y;
}

static void	alpha_row(t_mlx_fb *dst, t_mlx_fb *src, t_mlx_point p, int y)
{
	int	x;
	int	fg;
	int	bg;

	x = 0;
	while (x < src->w && (p.x + x) < dst->w)
	{
		if (p.x + x >= 0)
		{
			fg = mlx_buf_pixel_get(src, x, y);
			bg = mlx_buf_pixel_get(dst, p.x + x, p.y + y);
			mlx_buf_pixel_put(dst, p.x + x, p.y + y,
				mlx_blend_alpha(fg, bg));
		}
		x++;
	}
}

void	mlx_alpha_blit(t_mlx_fb *dst, t_mlx_fb *src, t_mlx_point p)
{
	int	wh[2];
	int	y;
	int	start_y;

	blit_bounds(dst, src, p, wh);
	if (wh[0] <= 0 || wh[1] <= 0)
		return ;
	start_y = 0;
	if (p.y < 0)
		start_y = -p.y;
	y = start_y;
	while (y < src->h && (p.y + y) < dst->h)
	{
		alpha_row(dst, src, p, y);
		y++;
	}
}

void	mlx_set_image_alpha(t_mlx_fb *fb, int alpha)
{
	int	x;
	int	y;
	int	col;

	alpha = mlx_clamp_i(alpha, 0, 255);
	y = 0;
	while (y < fb->h)
	{
		x = 0;
		while (x < fb->w)
		{
			col = mlx_buf_pixel_get(fb, x, y);
			col = (col & 0x00FFFFFF) | (alpha << 24);
			mlx_buf_pixel_put(fb, x, y, col);
			x++;
		}
		y++;
	}
}
