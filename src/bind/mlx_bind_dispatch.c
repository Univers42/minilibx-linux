/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_bind_dispatch.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/09 13:36:39 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_ext.h"

void	mlx_unbind_key(int keysym, int mods)
{
	mlx_bind_key(keysym, mods, 0);
}

/*
** Internal callback connected to mlx_on_key by mlx_key_dispatch().
** On key press, looks up the binding table and calls the registered
** handler (if any) with the original t_mlx_keydata + user param.
*/

static void	bind_dispatch_cb(t_mlx_keydata kd, void *param)
{
	t_mlx_bindfn	fn;

	if (kd.action != MLX_PRESS)
		return ;
	fn = mlx_find_binding(kd.key, kd.mods);
	if (fn)
		fn(kd, param);
}

/*
** Connects the binding dispatch system to a window.
** After calling this, any key press on `win` will look up the
** binding table and dispatch to the registered t_mlx_bindfn.
** `param` is forwarded to every bound callback.
**
** Usage:
**   mlx_bind_key('w', 0, my_move_up_fn);
**   mlx_bind_key(0xff52, MLX_MOD_CTRL, my_zoom_fn);
**   mlx_key_dispatch(win, app);
**   mlx_loop(mlx);
*/

void	mlx_key_dispatch(void *win, void *param)
{
	mlx_on_key(win, bind_dispatch_cb, param);
}
