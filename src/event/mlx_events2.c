/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/09 14:58:21 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_ext_int.h"

void	mlx_on_mouse(void *win, t_mlx_mousefn fn, void *p)
{
	t_mlx_ext_hooks	*h;

	h = mlx_ext_get_hooks(win);
	if (!h)
		return ;
	h->mouse_fn = fn;
	h->mouse_param = p;
	mlx_hook(win, X_BUTTON_PRESS, X_BUTTON_PRESS_MASK,
		(t_mlx_hcb){mlx_ext_mouse_dispatch, h});
	mlx_hook(win, X_BUTTON_RELEASE, X_BUTTON_RELEASE_MASK,
		(t_mlx_hcb){mlx_ext_mouserel_dispatch, h});
}

void	mlx_on_motion(void *win, t_mlx_motionfn fn, void *p)
{
	t_mlx_ext_hooks	*h;

	h = mlx_ext_get_hooks(win);
	if (!h)
		return ;
	h->motion_fn = fn;
	h->motion_param = p;
	mlx_hook(win, X_MOTION_NOTIFY, X_POINTER_MOTION_MASK,
		(t_mlx_hcb){mlx_ext_motion_dispatch, h});
}

void	mlx_on_expose(void *win, t_mlx_exposefn fn, void *p)
{
	t_mlx_ext_hooks	*h;

	h = mlx_ext_get_hooks(win);
	if (!h)
		return ;
	h->expose_fn = fn;
	h->expose_param = p;
	mlx_hook(win, X_EXPOSE, X_EXPOSURE_MASK,
		(t_mlx_hcb){mlx_ext_expose_dispatch, h});
}

void	mlx_on_scroll(void *win, t_mlx_scrollfn fn, void *p)
{
	t_mlx_ext_hooks	*h;

	h = mlx_ext_get_hooks(win);
	if (!h)
		return ;
	h->scroll_fn = fn;
	h->scroll_param = p;
	mlx_hook(win, X_BUTTON_PRESS, X_BUTTON_PRESS_MASK,
		(t_mlx_hcb){mlx_ext_mouse_dispatch, h});
}

void	mlx_on_close(void *win, t_mlx_closefn fn, void *p)
{
	t_mlx_ext_hooks	*h;

	h = mlx_ext_get_hooks(win);
	if (!h)
		return ;
	h->close_fn = fn;
	h->close_param = p;
	mlx_hook(win, X_DESTROY_NOTIFY, X_STRUCTURE_MASK,
		(t_mlx_hcb){mlx_ext_close_dispatch, h});
}
