/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_int_str_to_wordtab.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/09 13:02:31 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

static int	match_at(char *str, char *find)
{
	char	*s;
	char	*f;

	s = str;
	f = find;
	while (*(f++) == *(s++))
		if (!*f)
			return (1);
	return (0);
}

int	mlx_int_str_str(char *str, char *find, int len)
{
	int		len_f;
	int		pos;

	len_f = strlen(find);
	if (len_f > len)
		return (-1);
	pos = 0;
	while (*(str + len_f - 1))
	{
		if (match_at(str, find))
			return (pos);
		str++;
		pos++;
	}
	return (-1);
}

int	mlx_int_str_str_cote(char *str, char *find, int len)
{
	int		len_f;
	int		pos;
	int		cote;

	len_f = strlen(find);
	if (len_f > len)
		return (-1);
	cote = 0;
	pos = 0;
	while (*(str + len_f - 1))
	{
		if (*str == '"')
			cote = 1 - cote;
		if (!cote && match_at(str, find))
			return (pos);
		str++;
		pos++;
	}
	return (-1);
}
