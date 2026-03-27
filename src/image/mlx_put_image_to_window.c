/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_put_image_to_window.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/09 14:19:26 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mlx_int.h"

static void	mlx_img_blit(t_xvar *xvar, t_win_list *win,
		t_img *img, t_mlx_point pos)
{
	GC	gc;

	gc = win->gc;
	if (img->gc)
	{
		gc = img->gc;
		XSetClipOrigin(xvar->display, gc, pos.x, pos.y);
	}
	if (img->type == MLX_TYPE_SHM)
		XShmPutImage(xvar->display, img->pix, win->gc,
			img->image, 0, 0, 0, 0,
			img->width, img->height, False);
	if (img->type == MLX_TYPE_XIMAGE)
		XPutImage(xvar->display, img->pix, win->gc,
			img->image, 0, 0, 0, 0,
			img->width, img->height);
	XCopyArea(xvar->display, img->pix, win->window, gc,
		0, 0, img->width, img->height, pos.x, pos.y);
	if (xvar->do_flush)
		XFlush(xvar->display);
}

int	mlx_put_image_to_window(void *mlx_ptr, void *win_ptr,
		void *img_ptr, t_mlx_point pos)
{
	mlx_img_blit((t_xvar *)mlx_ptr,
		(t_win_list *)win_ptr, (t_img *)img_ptr, pos);
	return (0);
}
