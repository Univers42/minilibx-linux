/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_draw_rect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/08 17:44:40 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_ext_int.h"

static void	draw_hline(t_mlx_fb *fb, int y, int *xr, int col)
{
	int	x;

	x = xr[0];
	while (x <= xr[1])
	{
		mlx_buf_pixel_put(fb, x, y, col);
		x++;
	}
}

static void	draw_vline(t_mlx_fb *fb, int x, int *yr, int col)
{
	int	y;

	y = yr[0];
	while (y <= yr[1])
	{
		mlx_buf_pixel_put(fb, x, y, col);
		y++;
	}
}

void	mlx_draw_rect(t_mlx_fb *fb, t_mlx_rect *r, int col)
{
	int	xr[2];
	int	yr[2];

	if (!fb || !r || r->w <= 0 || r->h <= 0)
		return ;
	xr[0] = r->x;
	xr[1] = r->x + r->w - 1;
	yr[0] = r->y;
	yr[1] = r->y + r->h - 1;
	draw_hline(fb, r->y, xr, col);
	draw_hline(fb, yr[1], xr, col);
	draw_vline(fb, r->x, yr, col);
	draw_vline(fb, xr[1], yr, col);
}

void	mlx_fill_rect(t_mlx_fb *fb, t_mlx_rect *r, int col)
{
	int	x;
	int	y;

	if (!fb || !r || r->w <= 0 || r->h <= 0)
		return ;
	y = r->y;
	while (y < r->y + r->h)
	{
		x = r->x;
		while (x < r->x + r->w)
		{
			mlx_buf_pixel_put(fb, x, y, col);
			x++;
		}
		y++;
	}
}
