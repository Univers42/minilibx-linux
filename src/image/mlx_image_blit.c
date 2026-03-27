/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_image_blit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/09 12:39:19 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_ext_int.h"

static void	copy_row(t_mlx_fb *dst, t_mlx_fb *src, t_mlx_point p, int y)
{
	char	*d;
	char	*s;
	int		len;

	s = src->data + y * src->line_len;
	d = dst->data + (p.y + y) * dst->line_len + p.x * (dst->bpp / 8);
	len = src->w * (src->bpp / 8);
	if (p.x + src->w > dst->w)
		len = (dst->w - p.x) * (dst->bpp / 8);
	if (len > 0)
		memcpy(d, s, len);
}

void	mlx_blit(t_mlx_fb *dst, t_mlx_fb *src, t_mlx_point p)
{
	int	y;
	int	max_y;

	if (p.x >= dst->w || p.y >= dst->h)
		return ;
	if (p.x < 0 || p.y < 0)
		return ;
	max_y = src->h;
	if (p.y + max_y > dst->h)
		max_y = dst->h - p.y;
	y = 0;
	while (y < max_y)
	{
		copy_row(dst, src, p, y);
		y++;
	}
}

static void	rect_row(t_mlx_fb *d, t_mlx_fb *s, t_mlx_rect *sr, int y)
{
	int	x;
	int	col;

	x = 0;
	while (x < sr->w && (sr->x + x) < s->w)
	{
		col = mlx_buf_pixel_get(s, sr->x + x, sr->y + y);
		mlx_buf_pixel_put(d, x, y, col);
		x++;
	}
}

void	mlx_blit_rect(t_mlx_fb *d, t_mlx_fb *s, t_mlx_rect *sr)
{
	int	y;
	int	max_y;

	if (!sr || sr->x < 0 || sr->y < 0)
		return ;
	if (sr->x >= s->w || sr->y >= s->h)
		return ;
	max_y = sr->h;
	if (sr->y + max_y > s->h)
		max_y = s->h - sr->y;
	if (max_y > d->h)
		max_y = d->h;
	y = 0;
	while (y < max_y)
	{
		rect_row(d, s, sr, y);
		y++;
	}
}
