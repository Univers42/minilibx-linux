/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/09 14:19:26 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mlx_int.h"

int	mlx_hook(void *win_ptr, int x_event,
		int x_mask, t_mlx_hcb cb)
{
	t_win_list	*win;

	win = (t_win_list *)win_ptr;
	win->hooks[x_event].hook = cb.funct;
	win->hooks[x_event].param = cb.param;
	win->hooks[x_event].mask = x_mask;
	return (0);
}

int	mlx_do_key_autorepeatoff(void *mlx_ptr)
{
	XAutoRepeatOff(((t_xvar *)mlx_ptr)->display);
	return (0);
}

int	mlx_do_key_autorepeaton(void *mlx_ptr)
{
	XAutoRepeatOn(((t_xvar *)mlx_ptr)->display);
	return (0);
}

int	mlx_do_sync(void *mlx_ptr)
{
	XSync(((t_xvar *)mlx_ptr)->display, False);
	return (0);
}
