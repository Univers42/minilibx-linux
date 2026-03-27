/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_errno2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/08 17:33:55 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_ext.h"
#include <unistd.h>

static int	mlx_ext_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	mlx_perror(const char *prefix)
{
	int			code;
	const char	*msg;

	code = mlx_get_errno();
	msg = mlx_strerror(code);
	if (prefix)
	{
		write(2, prefix, mlx_ext_strlen(prefix));
		write(2, ": ", 2);
	}
	write(2, msg, mlx_ext_strlen(msg));
	write(2, "\n", 1);
}
