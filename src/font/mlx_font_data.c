/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_font_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/09 14:58:21 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_ext.h"

/*
** 8x8 bitmap font — CP437-inspired glyphs for ASCII 32..126.
** Each glyph is 8 bytes; bit 7 = leftmost pixel.
** Index: character - 32.  Characters outside range get space.
*/

void	*mlx_get_glyph(char c)
{
	static const unsigned char	font[95][8] = {
		#include "mlx_font.dat"
	};
	int							idx;

	idx = (int)c - 32;
	if (idx < 0 || idx >= 95)
		idx = 0;
	return ((void *)font[idx]);
}
