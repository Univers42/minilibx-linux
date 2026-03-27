/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_int_str_to_wordtab2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/09 13:02:32 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

static int	is_sep(char c)
{
	return (c == ' ' || c == '\t');
}

static int	count_words(char *str, int len)
{
	int	pos;
	int	nb;

	nb = 0;
	pos = 0;
	while (pos < len)
	{
		while (is_sep(*(str + pos)))
			pos++;
		if (*(str + pos))
			nb++;
		while (*(str + pos) && !is_sep(*(str + pos)))
			pos++;
	}
	return (nb);
}

static void	fill_tab(char **tab, char *str, int len)
{
	int	pos;
	int	nb;

	nb = 0;
	pos = 0;
	while (pos < len)
	{
		while (is_sep(*(str + pos)))
		{
			*(str + pos) = 0;
			pos++;
		}
		if (*(str + pos))
		{
			tab[nb] = str + pos;
			nb++;
		}
		while (*(str + pos) && !is_sep(*(str + pos)))
			pos++;
	}
	tab[nb] = 0;
}

char	**mlx_int_str_to_wordtab(char *str)
{
	char	**tab;
	int		nb_word;
	int		len;

	len = strlen(str);
	nb_word = count_words(str, len);
	tab = malloc((1 + nb_word) * sizeof(*tab));
	if (!tab)
		return ((char **)0);
	fill_tab(tab, str, len);
	return (tab);
}
