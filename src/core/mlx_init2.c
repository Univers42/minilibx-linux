/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/09 12:23:26 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

static void	mlx_check_shm_env(t_xvar *xvar)
{
	char	*dpy;
	char	buff[33];

	gethostname(buff, 32);
	dpy = getenv(ENV_DISPLAY);
	if (dpy && strlen(dpy) && *dpy != ':'
		&& strncmp(dpy, buff, strlen(buff))
		&& strncmp(dpy, LOCALHOST, strlen(LOCALHOST)))
	{
		xvar->pshm_format = -1;
		xvar->use_xshm = 0;
	}
}

int	mlx_int_deal_shm(t_xvar *xvar)
{
	int		use_pshm;
	int		bidon;

	xvar->use_xshm = XShmQueryVersion(xvar->display,
			&bidon, &bidon, &(use_pshm));
	if (xvar->use_xshm && use_pshm)
		xvar->pshm_format = XShmPixmapFormat(xvar->display);
	else
		xvar->pshm_format = -1;
	mlx_check_shm_env(xvar);
	return (0);
}

static void	mlx_rgb_shift(unsigned long *mask, int *dec, int *bits)
{
	*dec = 0;
	*bits = 0;
	while (!(*mask & 1))
	{
		*mask >>= 1;
		(*dec)++;
	}
	while (*mask & 1)
	{
		*mask >>= 1;
		(*bits)++;
	}
}

int	mlx_int_rgb_conversion(t_xvar *xvar)
{
	unsigned long	rmask;
	unsigned long	gmask;
	unsigned long	bmask;

	memset(xvar->decrgb, 0, sizeof(int) * 6);
	rmask = xvar->visual->red_mask;
	gmask = xvar->visual->green_mask;
	bmask = xvar->visual->blue_mask;
	mlx_rgb_shift(&rmask, &xvar->decrgb[0], &xvar->decrgb[1]);
	mlx_rgb_shift(&gmask, &xvar->decrgb[2], &xvar->decrgb[3]);
	mlx_rgb_shift(&bmask, &xvar->decrgb[4], &xvar->decrgb[5]);
	return (0);
}
