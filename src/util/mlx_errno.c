/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_errno.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/09 13:36:34 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_ext.h"
#include <unistd.h>

static int	*mlx_errno_ptr(void)
{
	static int	err_code;

	return (&err_code);
}

int	mlx_get_errno(void)
{
	return (*mlx_errno_ptr());
}

void	mlx_set_errno(int code)
{
	*mlx_errno_ptr() = code;
}

const char	*mlx_strerror(int code)
{
	static const char	*msgs[MLX_ERRMAX] = {
		"Success",
		"Memory allocation failed",
		"Image creation failed",
		"File I/O error",
		"PNG decoding error",
		"Invalid argument"
	};

	if (code < 0 || code >= MLX_ERRMAX)
		return ("Unknown error");
	return (msgs[code]);
}
