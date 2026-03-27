/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_pixel_buf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/09 12:39:35 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_ext_int.h"

void	mlx_buf_pixel_put(t_mlx_fb *fb, int x, int y, int col)
{
	char	*dst;

	if (!fb || !fb->data)
		return ;
	if (x < 0 || x >= fb->w || y < 0 || y >= fb->h)
		return ;
	dst = fb->data + (y * fb->line_len + x * (fb->bpp / 8));
	*(unsigned int *)dst = col;
}

int	mlx_buf_pixel_get(t_mlx_fb *fb, int x, int y)
{
	char	*src;

	if (!fb || !fb->data)
		return (0);
	if (x < 0 || x >= fb->w || y < 0 || y >= fb->h)
		return (0);
	src = fb->data + (y * fb->line_len + x * (fb->bpp / 8));
	return (*(unsigned int *)src);
}

void	mlx_buf_clear(t_mlx_fb *fb, int color)
{
	int	x;
	int	y;

	if (!fb || !fb->data)
		return ;
	y = 0;
	while (y < fb->h)
	{
		x = 0;
		while (x < fb->w)
		{
			mlx_buf_pixel_put(fb, x, y, color);
			x++;
		}
		y++;
	}
}
