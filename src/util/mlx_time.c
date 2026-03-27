/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/08 17:45:20 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_ext_int.h"

static double	*prev_dt_time(void)
{
	static double	t = -1.0;

	return (&t);
}

double	mlx_get_time(void)
{
	struct timespec	ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ((double)ts.tv_sec + (double)ts.tv_nsec / 1e9);
}

double	mlx_delta_time(void *mlx)
{
	double	*prev;
	double	now;
	double	dt;

	(void)mlx;
	prev = prev_dt_time();
	now = mlx_get_time();
	if (*prev < 0.0)
		*prev = now;
	dt = now - *prev;
	*prev = now;
	return (dt);
}

double	mlx_get_fps(void *mlx)
{
	static double	prev_t = -1.0;
	double			now;
	double			dt;

	(void)mlx;
	now = mlx_get_time();
	if (prev_t < 0.0)
		prev_t = now;
	dt = now - prev_t;
	prev_t = now;
	if (dt <= 0.0)
		return (0.0);
	return (1.0 / dt);
}
