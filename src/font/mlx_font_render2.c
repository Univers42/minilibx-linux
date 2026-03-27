/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_font_render2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/08 17:44:36 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_ext.h"

static int	ext_strlen(const char *s)
{
	int	n;

	n = 0;
	while (s[n])
		n++;
	return (n);
}

int	mlx_text_width(const char *str, int scale)
{
	if (!str)
		return (0);
	return (ext_strlen(str) * MLX_FONT_W * scale);
}

int	mlx_text_height(int scale)
{
	return (MLX_FONT_H * scale);
}
