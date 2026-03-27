/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_xpm_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/09 14:58:21 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

unsigned int	mlx_int_strlcpy(char *dst, char *src, unsigned int size)
{
	unsigned int	count;
	unsigned int	i;

	count = 0;
	while (src[count] != '\0')
		++count;
	i = 0;
	while (src[i] != '\0' && i < (size - 1))
	{
		dst[i] = src[i];
		++i;
	}
	dst[i] = '\0';
	return (count);
}

char	*mlx_int_get_line(void *info, int *pos, int size)
{
	int		pos2;
	int		pos3;
	int		pos4;
	char	*ptr;

	ptr = (char *)info;
	pos2 = mlx_int_str_str(ptr + *pos, "\"", size - *pos);
	if (pos2 == -1)
		return ((char *)0);
	pos3 = mlx_int_str_str(ptr + *pos + pos2 + 1, "\"",
			size - *pos - pos2 - 1);
	if (pos3 == -1)
		return ((char *)0);
	*(ptr + *pos + pos2) = 0;
	*(ptr + *pos + pos2 + 1 + pos3) = 0;
	pos4 = *pos + pos2 + 1;
	*pos += pos2 + pos3 + 2;
	return (ptr + pos4);
}

char	*mlx_int_static_line(void *info, int *pos, int size)
{
	static char	*copy;
	static int	len;
	int			len2;
	char		*str;

	(void)size;
	str = ((char **)info)[(*pos)++];
	len2 = strlen(str);
	if (len2 > len)
	{
		if (copy)
			free(copy);
		copy = malloc(len2 + 1);
		if (!copy)
			return ((char *)0);
		len = len2;
	}
	mlx_int_strlcpy(copy, str, len2);
	return (copy);
}

int	mlx_int_get_col_name(char *str, int size)
{
	int	result;

	result = 0;
	while (size--)
		result = (result << 8) + *(str++);
	return (result);
}

int	mlx_int_get_text_rgb(char *name, char *end)
{
	int			i;
	char		buff[64];
	t_col_name	*cn;

	if (*name == '#')
		return (strtol(name + 1, 0, 16));
	if (end)
	{
		snprintf(buff, 64, "%s %s", name, end);
		name = buff;
	}
	cn = mlx_get_col_names();
	i = 0;
	while (cn[i].name)
	{
		if (!strcasecmp(cn[i].name, name))
			return (cn[i].color);
		i++;
	}
	return (0);
}
