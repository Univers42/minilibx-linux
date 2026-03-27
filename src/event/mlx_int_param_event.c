/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_int_param_event.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/09 13:02:34 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

int	mlx_int_param_undef(t_xvar *xvar, XEvent *ev, t_win_list *win)
{
	(void)xvar;
	(void)ev;
	(void)win;
	return (0);
}

int	mlx_int_param_keypress(t_xvar *xvar, XEvent *ev, t_win_list *win)
{
	win->hooks[KeyPress].hook(
		XkbKeycodeToKeysym(xvar->display, ev->xkey.keycode, 0, 0),
		win->hooks[KeyPress].param);
	return (0);
}

int	mlx_int_param_keyrelease(t_xvar *xvar, XEvent *ev, t_win_list *win)
{
	win->hooks[KeyRelease].hook(
		XkbKeycodeToKeysym(xvar->display, ev->xkey.keycode, 0, 0),
		win->hooks[KeyRelease].param);
	return (0);
}

int	mlx_int_param_btnpress(t_xvar *xvar, XEvent *ev, t_win_list *win)
{
	(void)xvar;
	win->hooks[ButtonPress].hook(ev->xbutton.button,
		ev->xbutton.x, ev->xbutton.y,
		win->hooks[ButtonPress].param);
	return (0);
}

int	mlx_int_param_btnrelease(t_xvar *xvar, XEvent *ev, t_win_list *win)
{
	(void)xvar;
	win->hooks[ButtonRelease].hook(ev->xbutton.button,
		ev->xbutton.x, ev->xbutton.y,
		win->hooks[ButtonRelease].param);
	return (0);
}
