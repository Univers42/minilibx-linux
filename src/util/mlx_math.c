/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/08 17:33:49 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_ext.h"

int	mlx_clamp_i(int val, int lo, int hi)
{
	if (val < lo)
		return (lo);
	if (val > hi)
		return (hi);
	return (val);
}

float	mlx_clamp_f(float val, float lo, float hi)
{
	if (val < lo)
		return (lo);
	if (val > hi)
		return (hi);
	return (val);
}

float	mlx_lerp_f(float a, float b, float t)
{
	return (a + (b - a) * t);
}

int	mlx_min_i(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	mlx_max_i(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}
