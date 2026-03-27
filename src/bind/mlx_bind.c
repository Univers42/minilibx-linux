/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_bind.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/09 15:37:15 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_ext.h"
#include <string.h>

static t_mlx_bindfn	*get_bind_table(void)
{
	static t_mlx_bindfn	table[MLX_BIND_SLOTS * MLX_BIND_MODS];

	return (table);
}

int	mlx_mod_index(int mods)
{
	return (mods & (MLX_MOD_SHIFT | MLX_MOD_CTRL | MLX_MOD_ALT));
}

void	mlx_bind_key(int keysym, int mods, t_mlx_bindfn fn)
{
	t_mlx_bindfn	*table;
	int				slot;
	int				mod_idx;

	slot = mlx_map_keysym(keysym);
	if (slot < 0 || slot >= MLX_BIND_SLOTS)
		return ;
	mod_idx = mlx_mod_index(mods);
	table = get_bind_table();
	table[slot * MLX_BIND_MODS + mod_idx] = fn;
}

void	mlx_unbind_all(void)
{
	t_mlx_bindfn	*table;

	table = get_bind_table();
	memset(table, 0,
		sizeof(t_mlx_bindfn) * MLX_BIND_SLOTS * MLX_BIND_MODS);
}

t_mlx_bindfn	mlx_find_binding(int keysym, int mods)
{
	t_mlx_bindfn	*table;
	int				slot;
	int				mod_idx;

	slot = mlx_map_keysym(keysym);
	if (slot < 0 || slot >= MLX_BIND_SLOTS)
		return (NULL);
	mod_idx = mlx_mod_index(mods);
	table = get_bind_table();
	return (table[slot * MLX_BIND_MODS + mod_idx]);
}
