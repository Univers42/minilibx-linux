/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_mouse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/09 13:42:28 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

int	mlx_mouse_move(t_xvar *xvar, t_win_list *win, int x, int y)
{
	XWarpPointer(xvar->display, None, win->window, 0, 0, 0, 0, x, y);
	return (0);
}

int	mlx_mouse_hide(t_xvar *xvar, t_win_list *win)
{
	static char	data[1] = {0};
	Cursor		cursor;
	Pixmap		blank;
	XColor		dummy;

	blank = XCreateBitmapFromData(xvar->display, win->window,
			data, 1, 1);
	cursor = XCreatePixmapCursor(xvar->display, blank, blank,
			&dummy, &dummy, 0, 0);
	XDefineCursor(xvar->display, win->window, cursor);
	XFreePixmap(xvar->display, blank);
	XFreeCursor(xvar->display, cursor);
	return (0);
}

int	mlx_mouse_show(t_xvar *xvar, t_win_list *win)
{
	XUndefineCursor(xvar->display, win->window);
	return (0);
}

int	mlx_mouse_get_pos(t_xvar *xvar, t_win_list *win,
		int *win_x_return, int *win_y_return)
{
	Window			root_ret;
	Window			child_ret;
	int				root_x;
	int				root_y;
	unsigned int	mask_ret;

	return (XQueryPointer(xvar->display, win->window,
			&root_ret, &child_ret, &root_x, &root_y,
			win_x_return, win_y_return, &mask_ret));
}
