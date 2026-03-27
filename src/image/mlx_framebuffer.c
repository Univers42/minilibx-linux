/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_framebuffer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/09 14:19:26 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_ext_int.h"

t_mlx_fb	*mlx_new_fb(void *mlx, int w, int h)
{
	t_mlx_fb	*fb;

	if (!mlx || w <= 0 || h <= 0)
	{
		mlx_set_errno(MLX_EINVAL);
		return (NULL);
	}
	fb = (t_mlx_fb *)malloc(sizeof(t_mlx_fb));
	if (!fb)
	{
		mlx_set_errno(MLX_EALLOC);
		return (NULL);
	}
	fb->img = mlx_new_image(mlx, w, h);
	if (!fb->img)
	{
		free(fb);
		mlx_set_errno(MLX_EIMG);
		return (NULL);
	}
	fb->data = mlx_get_data_addr(fb->img, &fb->bpp, &fb->line_len,
			&fb->endian);
	fb->w = w;
	fb->h = h;
	return (fb);
}

void	mlx_destroy_fb(void *mlx, t_mlx_fb *fb)
{
	if (!fb)
		return ;
	if (fb->img && mlx)
		mlx_destroy_image(mlx, fb->img);
	fb->img = NULL;
	fb->data = NULL;
	free(fb);
}

void	mlx_fb_render(void *mlx, void *win, t_mlx_fb *fb)
{
	if (!mlx || !win || !fb || !fb->img)
		return ;
	mlx_put_image_to_window(mlx, win, fb->img,
		(t_mlx_point){0, 0});
}

void	mlx_fb_render_at(t_mlx_fb *fb, void *ctx[3])
{
	t_mlx_point	*pos;

	if (!fb || !fb->img || !ctx || !ctx[0] || !ctx[1] || !ctx[2])
		return ;
	pos = (t_mlx_point *)ctx[2];
	mlx_put_image_to_window(ctx[0], ctx[1], fb->img, *pos);
}
