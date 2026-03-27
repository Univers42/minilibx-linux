/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/09 13:02:35 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_ext_int.h"

int	mlx_ext_mouserel_dispatch(int btn, int x, int y, void *p)
{
	t_mlx_ext_hooks	*h;
	t_mlx_mousedata	md;

	h = (t_mlx_ext_hooks *)p;
	if (btn == 4 || btn == 5)
		return (0);
	if (h->mouse_fn)
	{
		md.button = btn;
		md.x = x;
		md.y = y;
		md.action = MLX_RELEASE;
		h->mouse_fn(md, h->mouse_param);
	}
	return (0);
}

int	mlx_ext_motion_dispatch(int x, int y, void *p)
{
	t_mlx_ext_hooks	*h;

	h = (t_mlx_ext_hooks *)p;
	if (h->motion_fn)
		h->motion_fn(x, y, h->motion_param);
	return (0);
}

int	mlx_ext_close_dispatch(void *p)
{
	t_mlx_ext_hooks	*h;

	h = (t_mlx_ext_hooks *)p;
	if (h->close_fn)
		h->close_fn(h->close_param);
	return (0);
}

int	mlx_ext_expose_dispatch(void *p)
{
	t_mlx_ext_hooks	*h;

	h = (t_mlx_ext_hooks *)p;
	if (h->expose_fn)
		h->expose_fn(h->expose_param);
	return (0);
}

int	mlx_get_mods(void *win)
{
	t_mlx_ext_hooks	*h;

	h = mlx_ext_get_hooks(win);
	if (!h)
		return (0);
	return (h->mods);
}
