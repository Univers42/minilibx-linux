/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_font_render.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/08 17:44:36 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_ext_int.h"

static void	draw_scaled_px(t_mlx_fb *fb, t_mlx_point pos, int scale, int col)
{
	int	sy;
	int	sx;

	sy = 0;
	while (sy < scale)
	{
		sx = 0;
		while (sx < scale)
		{
			mlx_buf_pixel_put(fb, pos.x + sx, pos.y + sy, col);
			sx++;
		}
		sy++;
	}
}

static void	render_row(t_mlx_fb *fb, t_mlx_text *p, unsigned char row, int dy)
{
	int			bit;
	t_mlx_point	pos;

	bit = 7;
	while (bit >= 0)
	{
		if (row & (1 << bit))
		{
			pos.x = p->x + (7 - bit) * p->scale;
			pos.y = p->y + dy * p->scale;
			draw_scaled_px(fb, pos, p->scale, p->color);
		}
		bit--;
	}
}

void	mlx_put_char(t_mlx_fb *fb, char c, t_mlx_text *p)
{
	const unsigned char	*glyph;
	int					row;

	glyph = mlx_get_glyph(c);
	row = 0;
	while (row < MLX_FONT_H)
	{
		render_row(fb, p, glyph[row], row);
		row++;
	}
}

void	mlx_put_str(t_mlx_fb *fb, const char *s, t_mlx_text *p)
{
	int			i;
	t_mlx_text	cur;

	cur = *p;
	i = 0;
	while (s[i])
	{
		mlx_put_char(fb, s[i], &cur);
		cur.x += MLX_FONT_W * cur.scale;
		i++;
	}
}
