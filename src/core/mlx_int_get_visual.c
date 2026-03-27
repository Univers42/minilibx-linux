/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_int_get_visual.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/09 12:23:26 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

int	mlx_int_get_visual(t_xvar *xvar)
{
	XVisualInfo	*vi;
	XVisualInfo	tmpl;
	int			nb_item;

	xvar->private_cmap = 0;
	xvar->visual = DefaultVisual(xvar->display, xvar->screen);
	if (xvar->visual->class == TrueColor)
		return (0);
	tmpl.class = TrueColor;
	tmpl.depth = xvar->depth;
	vi = XGetVisualInfo(xvar->display,
			VisualDepthMask | VisualClassMask, &tmpl, &nb_item);
	if (!vi)
		return (-1);
	xvar->visual = vi->visual;
	xvar->private_cmap = 1;
	return (0);
}
