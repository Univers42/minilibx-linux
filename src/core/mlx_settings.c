/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_settings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/09 12:23:27 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_ext.h"

static int	*settings_array(void)
{
	static int	s[2];

	return (s);
}

void	mlx_set_setting(int key, int value)
{
	int	*s;

	s = settings_array();
	if (key >= 0 && key < MLX_SET_MAX)
		s[key] = value;
}

int	mlx_get_setting(int key)
{
	int	*s;

	s = settings_array();
	if (key >= 0 && key < MLX_SET_MAX)
		return (s[key]);
	return (0);
}
