/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_lib_xpm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/09 13:36:38 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef MLX_USE_LIBXPM

# include "mlx_int.h"
# include <X11/xpm.h>

static int	mlx_int_egal_img(XImage *a, XImage *b)
{
	if (a->width != b->width || a->height != b->height)
		return (0);
	if (a->xoffset != b->xoffset || a->format != b->format)
		return (0);
	if (a->byte_order != b->byte_order)
		return (0);
	if (a->bitmap_unit != b->bitmap_unit)
		return (0);
	if (a->bitmap_bit_order != b->bitmap_bit_order)
		return (0);
	if (a->bitmap_pad != b->bitmap_pad || a->depth != b->depth)
		return (0);
	if (a->bytes_per_line != b->bytes_per_line)
		return (0);
	if (a->bits_per_pixel != b->bits_per_pixel)
		return (0);
	if (a->red_mask != b->red_mask)
		return (0);
	if (a->green_mask != b->green_mask)
		return (0);
	if (a->blue_mask != b->blue_mask)
		return (0);
	return (1);
}

static void	xpm_lib_patch(t_xvar *xvar, t_img *im2, XImage *img1)
{
	if (im2->type == MLX_TYPE_SHM_PIXMAP)
	{
		XFreePixmap(xvar->display, im2->pix);
		im2->pix = XCreatePixmap(xvar->display, xvar->root,
				img1->width, img1->height, xvar->depth);
	}
	if (im2->type > MLX_TYPE_XIMAGE)
	{
		XShmDetach(xvar->display, &(im2->shm));
		shmdt(im2->data);
	}
	XDestroyImage(im2->image);
	im2->image = img1;
	im2->data = img1->data;
	im2->type = MLX_TYPE_XIMAGE;
	im2->size_line = img1->bytes_per_line;
	im2->bpp = img1->bits_per_pixel;
}

static void	*xpm_lib_build(t_xvar *xvar, XImage *img1, XImage *img2,
		int *dims)
{
	t_img	*im2;

	if (img2)
		XDestroyImage(img2);
	im2 = mlx_new_image(xvar, img1->width, img1->height);
	if (!im2)
	{
		XDestroyImage(img1);
		return ((void *)0);
	}
	dims[0] = img1->width;
	dims[1] = img1->height;
	if (mlx_int_egal_img(im2->image, img1))
	{
		memcpy(im2->data, img1->data,
			img1->height * img1->bytes_per_line);
		XDestroyImage(img1);
		return (im2);
	}
	xpm_lib_patch(xvar, im2, img1);
	return (im2);
}

void	*mlx_xpm_file_to_image(t_xvar *xvar, char *file,
		int *width, int *height)
{
	XImage			*img1;
	XImage			*img2;
	XpmAttributes	xpm_att;
	int				dims[2];
	void			*result;

	xpm_att.visual = xvar->visual;
	xpm_att.colormap = xvar->cmap;
	xpm_att.depth = xvar->depth;
	xpm_att.bitmap_format = ZPixmap;
	xpm_att.valuemask = XpmDepth | XpmBitmapFormat
		| XpmVisual | XpmColormap;
	if (XpmReadFileToImage(xvar->display, file, &img1, &img2,
			&xpm_att))
		return ((void *)0);
	result = xpm_lib_build(xvar, img1, img2, dims);
	*width = dims[0];
	*height = dims[1];
	return (result);
}

void	*mlx_xpm_to_image(t_xvar *xvar, char **data,
		int *width, int *height)
{
	XImage			*img1;
	XImage			*img2;
	XpmAttributes	xpm_att;
	int				dims[2];
	void			*result;

	xpm_att.visual = xvar->visual;
	xpm_att.colormap = xvar->cmap;
	xpm_att.depth = xvar->depth;
	xpm_att.bitmap_format = ZPixmap;
	xpm_att.valuemask = XpmDepth | XpmBitmapFormat
		| XpmVisual | XpmColormap;
	if (XpmCreateImageFromData(xvar->display, data, &img1, &img2,
			&xpm_att))
		return ((void *)0);
	result = xpm_lib_build(xvar, img1, img2, dims);
	*width = dims[0];
	*height = dims[1];
	return (result);
}

#endif
