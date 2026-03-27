/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_draw_circle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/08 17:44:24 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_ext_int.h"

void	mlx_ext_circle_pts(t_mlx_fb *fb, t_mlx_circle *c, t_mlx_point o)
{
	mlx_buf_pixel_put(fb, c->cx + o.x, c->cy + o.y, c->color);
	mlx_buf_pixel_put(fb, c->cx - o.x, c->cy + o.y, c->color);
	mlx_buf_pixel_put(fb, c->cx + o.x, c->cy - o.y, c->color);
	mlx_buf_pixel_put(fb, c->cx - o.x, c->cy - o.y, c->color);
	mlx_buf_pixel_put(fb, c->cx + o.y, c->cy + o.x, c->color);
	mlx_buf_pixel_put(fb, c->cx - o.y, c->cy + o.x, c->color);
	mlx_buf_pixel_put(fb, c->cx + o.y, c->cy - o.x, c->color);
	mlx_buf_pixel_put(fb, c->cx - o.y, c->cy - o.x, c->color);
}

void	mlx_draw_circle(t_mlx_fb *fb, t_mlx_circle *c)
{
	t_mlx_point	o;
	int			d;

	if (!fb || !c || c->r <= 0)
		return ;
	o.x = 0;
	o.y = c->r;
	d = 3 - 2 * c->r;
	mlx_ext_circle_pts(fb, c, o);
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
		mlx_ext_circle_pts(fb, c, o);
	}
}
