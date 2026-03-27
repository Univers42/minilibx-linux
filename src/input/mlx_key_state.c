/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_key_state.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/08 17:45:20 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_ext_int.h"

int	mlx_is_key_down(void *mlx, int keysym)
{
	t_xvar	*xvar;
	char	keys[32];
	int		kc;

	xvar = (t_xvar *)mlx;
	kc = XKeysymToKeycode(xvar->display, keysym);
	if (kc == 0)
		return (0);
	XQueryKeymap(xvar->display, keys);
	return ((keys[kc / 8] >> (kc % 8)) & 1);
}

static unsigned int	query_btn_mask(void *mlx)
{
	t_xvar			*xvar;
	Window			r;
	Window			c;
	int				xy[4];
	unsigned int	mask;

	xvar = (t_xvar *)mlx;
	r = DefaultRootWindow(xvar->display);
	XQueryPointer(xvar->display, r, &r, &c,
		&xy[0], &xy[1], &xy[2], &xy[3], &mask);
	return (mask);
}

int	mlx_is_mouse_down(void *mlx, int button)
{
	unsigned int	mask;

	if (button < 1 || button > 5)
		return (0);
	mask = query_btn_mask(mlx);
	return ((mask & (1 << (button + 7))) != 0);
}
