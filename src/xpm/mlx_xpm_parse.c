/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_xpm_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/09 13:02:32 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

static void	*xpm_cleanup(t_xpm_ctx *ctx, t_xvar *xvar)
{
	if (ctx->colors)
		free(ctx->colors);
	if (ctx->tab)
		free(ctx->tab);
	if (ctx->colors_direct)
		free(ctx->colors_direct);
	if (ctx->img)
	{
		XDestroyImage(ctx->img->image);
		XFreePixmap(xvar->display, ctx->img->pix);
		free(ctx->img);
	}
	return ((void *)0);
}

static int	xpm_parse_hdr(t_xpm_ctx *c, void *info,
		int sz, t_xpm_line_fn f)
{
	char	*line;

	line = f(info, &c->pos, sz);
	if (!line)
		return (0);
	c->tab = mlx_int_str_to_wordtab(line);
	if (!c->tab)
		return (0);
	c->width = atoi(c->tab[0]);
	c->height = atoi(c->tab[1]);
	c->nc = atoi(c->tab[2]);
	c->cpp = atoi(c->tab[3]);
	free(c->tab);
	c->tab = 0;
	if (!c->width || !c->height || !c->nc || !c->cpp)
		return (0);
	return (1);
}

static int	xpm_alloc_colors(t_xpm_ctx *c)
{
	int	n;

	c->method = 0;
	if (c->cpp <= 2)
	{
		c->method = 1;
		n = 256;
		if (c->cpp == 2)
			n = 65536;
		c->colors_direct = malloc(n * sizeof(int));
		if (!c->colors_direct)
			return (0);
	}
	else
	{
		c->colors = malloc(c->nc * sizeof(t_xpm_col));
		if (!c->colors)
			return (0);
	}
	return (1);
}

void	*mlx_int_parse_xpm(t_xvar *xvar, void *info,
		int info_size, t_xpm_line_fn f)
{
	t_xpm_ctx	ctx;

	memset(&ctx, 0, sizeof(ctx));
	if (!xpm_parse_hdr(&ctx, info, info_size, f))
		return (xpm_cleanup(&ctx, xvar));
	if (!xpm_alloc_colors(&ctx))
		return (xpm_cleanup(&ctx, xvar));
	if (!xpm_read_colors(&ctx, info, info_size, f))
		return (xpm_cleanup(&ctx, xvar));
	ctx.img = mlx_new_image(xvar, ctx.width, ctx.height);
	if (!ctx.img)
		return (xpm_cleanup(&ctx, xvar));
	if (!xpm_parse_pixels(&ctx, info, info_size, f))
		return (xpm_cleanup(&ctx, xvar));
	if (ctx.colors)
		free(ctx.colors);
	if (ctx.colors_direct)
		free(ctx.colors_direct);
	return (ctx.img);
}
