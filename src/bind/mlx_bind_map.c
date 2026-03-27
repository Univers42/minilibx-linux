/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_bind_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/08 17:56:05 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_ext.h"

/*
** Keysym mapper — compresses X11 keysyms into compact 0..191 indices.
** Slots   0-127: ASCII keysyms (0x00-0x7F) — direct index.
** Slots 128-131: Arrow keys (Left, Up, Right, Down).
** Slots 132-143: Function keys F1-F12.
** Slots 144-153: Numpad digits KP_0 through KP_9.
** Slots 154-158: Numpad ops (Add, Sub, Mul, Div, Enter).
** Slots 159-168: Special keys (Esc, Return, Tab, BS, Del, etc.).
** Returns -1 for unmapped keysyms.
*/

static int	map_ascii(int ks)
{
	if (ks >= 0x00 && ks <= 0x7F)
		return (ks);
	return (-1);
}

static int	map_arrows_fkeys(int ks)
{
	if (ks >= 0xFF51 && ks <= 0xFF54)
		return (128 + ks - 0xFF51);
	if (ks >= 0xFFBE && ks <= 0xFFC9)
		return (132 + ks - 0xFFBE);
	return (-1);
}

static int	map_numpad(int ks)
{
	if (ks >= 0xFFB0 && ks <= 0xFFB9)
		return (144 + ks - 0xFFB0);
	if (ks == 0xFFAB)
		return (154);
	if (ks == 0xFFAD)
		return (155);
	if (ks == 0xFFAA)
		return (156);
	if (ks == 0xFFAF)
		return (157);
	if (ks == 0xFF8D)
		return (158);
	return (-1);
}

static int	map_special(int ks)
{
	if (ks == 0xFF1B)
		return (159);
	if (ks == 0xFF0D)
		return (160);
	if (ks == 0xFF09)
		return (161);
	if (ks == 0xFF08)
		return (162);
	if (ks == 0xFFFF)
		return (163);
	if (ks == 0xFF50)
		return (164);
	if (ks == 0xFF57)
		return (165);
	if (ks == 0xFF55)
		return (166);
	if (ks == 0xFF56)
		return (167);
	if (ks == 0xFF63)
		return (168);
	return (-1);
}

int	mlx_map_keysym(int keysym)
{
	int	idx;

	idx = map_ascii(keysym);
	if (idx >= 0)
		return (idx);
	idx = map_arrows_fkeys(keysym);
	if (idx >= 0)
		return (idx);
	idx = map_numpad(keysym);
	if (idx >= 0)
		return (idx);
	return (map_special(keysym));
}
