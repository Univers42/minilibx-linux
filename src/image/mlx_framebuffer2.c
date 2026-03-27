/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_framebuffer2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/09 12:39:25 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_ext_int.h"

t_mlx_fb	*mlx_fb_resize(void *mlx, t_mlx_fb *fb, t_mlx_point sz)
{
	t_mlx_fb	*nfb;

	if (!mlx || !fb || sz.x <= 0 || sz.y <= 0)
		return (fb);
	nfb = mlx_new_fb(mlx, sz.x, sz.y);
	if (!nfb)
		return (fb);
	mlx_destroy_fb(mlx, fb);
	return (nfb);
}

static void	copy_pixels(t_mlx_fb *dst, t_mlx_fb *src)
{
	int	y;
	int	bytes_w;

	bytes_w = src->w * (src->bpp / 8);
	y = 0;
	while (y < src->h)
	{
		memcpy(dst->data + y * dst->line_len,
			src->data + y * src->line_len, bytes_w);
		y++;
	}
}

t_mlx_fb	*mlx_fb_copy(void *mlx, t_mlx_fb *src)
{
	t_mlx_fb	*dst;

	if (!mlx || !src)
	{
		mlx_set_errno(MLX_EINVAL);
		return (NULL);
	}
	dst = mlx_new_fb(mlx, src->w, src->h);
	if (!dst)
		return (NULL);
	copy_pixels(dst, src);
	return (dst);
}
