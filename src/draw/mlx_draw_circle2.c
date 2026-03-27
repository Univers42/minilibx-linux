/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_draw_circle2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/08 17:44:25 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_ext_int.h"

void	mlx_ext_circle_fill_row(t_mlx_fb *fb, t_mlx_circle *c, t_mlx_point o)
{
	int	x;

	x = c->cx - o.x;
	while (x <= c->cx + o.x)
	{
		mlx_buf_pixel_put(fb, x, c->cy + o.y, c->color);
		mlx_buf_pixel_put(fb, x, c->cy - o.y, c->color);
		x++;
	}
	x = c->cx - o.y;
	while (x <= c->cx + o.y)
	{
		mlx_buf_pixel_put(fb, x, c->cy + o.x, c->color);
		mlx_buf_pixel_put(fb, x, c->cy - o.x, c->color);
		x++;
	}
}

void	mlx_fill_circle(t_mlx_fb *fb, t_mlx_circle *c)
{
	t_mlx_point	o;
	int			d;

	if (!fb || !c || c->r <= 0)
		return ;
	o.x = 0;
	o.y = c->r;
	d = 3 - 2 * c->r;
	mlx_ext_circle_fill_row(fb, c, o);
	while (o.y >= o.x)
	{
		o.x++;
		if (d > 0)
		{
			o.y--;
			d = d + 4 * (o.x - o.y) + 10;
		}
		else
			d = d + 4 * o.x + 6;
		mlx_ext_circle_fill_row(fb, c, o);
	}
}
