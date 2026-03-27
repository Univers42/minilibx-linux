/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/09 13:02:35 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_ext_int.h"

static int	get_mod_bit(int ks)
{
	if (ks == XK_SHIFT_L || ks == XK_SHIFT_R)
		return (MLX_MOD_SHIFT);
	if (ks == XK_CTRL_L || ks == XK_CTRL_R)
		return (MLX_MOD_CTRL);
	if (ks == XK_ALT_L || ks == XK_ALT_R)
		return (MLX_MOD_ALT);
	return (0);
}

int	mlx_ext_key_dispatch(int ks, void *p)
{
	t_mlx_ext_hooks	*h;
	t_mlx_keydata	kd;
	int				bit;

	h = (t_mlx_ext_hooks *)p;
	bit = get_mod_bit(ks);
	if (bit)
		h->mods |= bit;
	kd.key = ks;
	kd.action = MLX_PRESS;
	kd.mods = h->mods;
	if (h->key_fn)
		h->key_fn(kd, h->key_param);
	return (0);
}

int	mlx_ext_keyrel_dispatch(int ks, void *p)
{
	t_mlx_ext_hooks	*h;
	t_mlx_keydata	kd;
	int				bit;

	h = (t_mlx_ext_hooks *)p;
	bit = get_mod_bit(ks);
	if (bit)
		h->mods &= ~bit;
	kd.key = ks;
	kd.action = MLX_RELEASE;
	kd.mods = h->mods;
	if (h->key_fn)
		h->key_fn(kd, h->key_param);
	return (0);
}

static void	fill_md(t_mlx_mousedata *md, int btn, int x, int y)
{
	md->button = btn;
	md->x = x;
	md->y = y;
}

int	mlx_ext_mouse_dispatch(int btn, int x, int y, void *p)
{
	t_mlx_ext_hooks	*h;
	t_mlx_mousedata	md;

	h = (t_mlx_ext_hooks *)p;
	if ((btn == 4 || btn == 5) && h->scroll_fn)
	{
		h->scroll_fn(btn, x, y, h->scroll_param);
		return (0);
	}
	if (h->mouse_fn)
	{
		fill_md(&md, btn, x, y);
		md.action = MLX_PRESS;
		h->mouse_fn(md, h->mouse_param);
	}
	return (0);
}
