/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_new_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/09 14:58:20 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

int	mlx_shm_err_handler(Display *d, XErrorEvent *ev)
{
	(void)d;
	if (ev->request_code == 146 && ev->minor_code == 1)
		write(2, WARN_SHM_ATTACH, strlen(WARN_SHM_ATTACH));
	*mlx_x_err() = 1;
	return (0);
}

static void	mlx_img_setup(t_xvar *xvar, t_img *img, int *wh, int fmt)
{
	img->gc = 0;
	img->size_line = img->image->bytes_per_line;
	img->bpp = img->image->bits_per_pixel;
	img->width = wh[0];
	img->height = wh[1];
	img->pix = XCreatePixmap(xvar->display, xvar->root,
			wh[0], wh[1], xvar->depth);
	img->format = fmt;
	img->type = MLX_TYPE_XIMAGE;
	if (xvar->do_flush)
		XFlush(xvar->display);
}

void	*mlx_int_new_image(t_xvar *xvar, int width, int height, int format)
{
	t_img	*img;
	int		wh[2];

	img = malloc(sizeof(*img));
	if (!img)
		return ((void *)0);
	img->data = malloc((width + 32) * height * 4);
	if (!img->data)
	{
		free(img);
		return ((void *)0);
	}
	memset(img->data, 0, (width + 32) * height * 4);
	img->image = XCreateImage(xvar->display, xvar->visual, xvar->depth,
			format, 0, img->data, width, height, 32, 0);
	if (!img->image)
	{
		free(img->data);
		free(img);
		return ((void *)0);
	}
	wh[0] = width;
	wh[1] = height;
	mlx_img_setup(xvar, img, wh, format);
	return (img);
}

void	*mlx_new_image(t_xvar *xvar, int width, int height)
{
	t_img	*img;

	if (xvar->use_xshm)
	{
		img = mlx_int_new_xshm_image(xvar, width, height, ZPixmap);
		if (img)
			return (img);
	}
	return (mlx_int_new_image(xvar, width, height, ZPixmap));
}

void	*mlx_new_image2(t_xvar *xvar, int width, int height)
{
	t_img	*img;

	if (xvar->use_xshm)
	{
		img = mlx_int_new_xshm_image(xvar, width, height, XYPixmap);
		if (img)
			return (img);
	}
	return (mlx_int_new_image(xvar, width, height, XYPixmap));
}
