/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_xpm_parse2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/09 13:36:37 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

static void	xpm_store_col(t_xpm_ctx *c, char *ln, int rgb, int i)
{
	if (c->method)
		c->colors_direct[mlx_int_get_col_name(ln, c->cpp)] = rgb;
	else
	{
		c->colors[i].name = mlx_int_get_col_name(ln, c->cpp);
		c->colors[i].col = rgb;
	}
}

int	xpm_read_colors(t_xpm_ctx *c, void *info,
		int sz, t_xpm_line_fn f)
{
	int		idx;
	int		j;
	int		rgb;
	char	*ln;

	idx = c->nc;
	while (idx--)
	{
		ln = f(info, &c->pos, sz);
		if (!ln)
			return (0);
		c->tab = mlx_int_str_to_wordtab(ln + c->cpp);
		if (!c->tab)
			return (0);
		j = 0;
		while (c->tab[j] && strcmp(c->tab[j++], "c"))
			;
		if (!c->tab[j])
			return (0);
		rgb = mlx_int_get_text_rgb(c->tab[j], c->tab[j + 1]);
		xpm_store_col(c, ln, rgb, idx);
		free(c->tab);
		c->tab = 0;
	}
	return (1);
}

static int	xpm_find_color(t_xpm_ctx *ctx, int col_name)
{
	int	j;

	j = ctx->nc;
	while (j--)
	{
		if (ctx->colors[j].name == col_name)
			return (ctx->colors[j].col);
	}
	return (-1);
}

static int	xpm_get_pixel_col(t_xpm_ctx *ctx, char *line, int x)
{
	int	col;

	col = mlx_int_get_col_name(line + ctx->cpp * x, ctx->cpp);
	if (ctx->method)
		col = ctx->colors_direct[col];
	else
		col = xpm_find_color(ctx, col);
	if (col == -1)
		col = 0xFF000000;
	return (col);
}

int	xpm_parse_pixels(t_xpm_ctx *ctx, void *info,
		int size, t_xpm_line_fn f)
{
	int		i;
	int		x;
	char	*line;

	i = ctx->height;
	while (i--)
	{
		line = f(info, &ctx->pos, size);
		if (!line)
			return (0);
		x = -1;
		while (++x < ctx->width)
			mlx_int_xpm_set_pixel(ctx->img,
				(ctx->height - 1 - i) * ctx->img->size_line,
				xpm_get_pixel_col(ctx, line, x), x);
	}
	return (1);
}
