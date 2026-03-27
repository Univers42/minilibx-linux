/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_new_xshm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/09 14:58:21 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

static t_img	*mlx_xshm_create(t_xvar *xvar, int *wh, int fmt)
{
	t_img	*img;

	img = malloc(sizeof(*img));
	if (!img)
		return (NULL);
	memset(img, 0, sizeof(*img));
	img->image = XShmCreateImage(xvar->display, xvar->visual,
			xvar->depth, fmt, NULL, &(img->shm), wh[0], wh[1]);
	if (!img->image)
	{
		free(img);
		return (NULL);
	}
	img->width = wh[0];
	img->height = wh[1];
	img->size_line = img->image->bytes_per_line;
	img->bpp = img->image->bits_per_pixel;
	img->format = fmt;
	return (img);
}

static int	mlx_xshm_setup_mem(t_img *img, int width, int height)
{
	img->shm.shmid = shmget(IPC_PRIVATE,
			(width + 32) * height * 4, IPC_CREAT | 0777);
	if (img->shm.shmid == -1)
		return (-1);
	img->data = shmat(img->shm.shmid, 0, 0);
	img->shm.shmaddr = img->data;
	img->image->data = img->data;
	if (img->data == (void *)-1)
	{
		shmctl(img->shm.shmid, IPC_RMID, 0);
		return (-1);
	}
	img->shm.readOnly = False;
	return (0);
}

static int	mlx_xshm_do_attach(t_xvar *xvar, t_img *img)
{
	XErrorHandler	save;

	*mlx_x_err() = 0;
	save = XSetErrorHandler(mlx_shm_err_handler);
	if (!XShmAttach(xvar->display, &(img->shm))
		|| (0 & XSync(xvar->display, False))
		|| *mlx_x_err())
	{
		XSetErrorHandler(save);
		shmdt(img->data);
		shmctl(img->shm.shmid, IPC_RMID, 0);
		return (-1);
	}
	XSetErrorHandler(save);
	shmctl(img->shm.shmid, IPC_RMID, 0);
	return (0);
}

static void	mlx_xshm_mk_pix(t_xvar *xvar, t_img *img)
{
	if (xvar->pshm_format == img->format)
	{
		img->pix = XShmCreatePixmap(xvar->display, xvar->root,
				img->shm.shmaddr, &(img->shm),
				img->width, img->height, xvar->depth);
		img->type = MLX_TYPE_SHM_PIXMAP;
	}
	else
	{
		img->pix = XCreatePixmap(xvar->display, xvar->root,
				img->width, img->height, xvar->depth);
		img->type = MLX_TYPE_SHM;
	}
	if (xvar->do_flush)
		XFlush(xvar->display);
}

void	*mlx_int_new_xshm_image(t_xvar *xvar, int w, int h, int fmt)
{
	t_img	*img;
	int		wh[2];

	wh[0] = w;
	wh[1] = h;
	img = mlx_xshm_create(xvar, wh, fmt);
	if (!img)
		return (NULL);
	if (mlx_xshm_setup_mem(img, w, h) == -1)
	{
		XDestroyImage(img->image);
		free(img);
		return (NULL);
	}
	if (mlx_xshm_do_attach(xvar, img) == -1)
	{
		XDestroyImage(img->image);
		free(img);
		return (NULL);
	}
	mlx_xshm_mk_pix(xvar, img);
	return (img);
}
