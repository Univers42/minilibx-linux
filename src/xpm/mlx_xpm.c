/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_xpm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/09 13:36:37 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

int	mlx_int_xpm_set_pixel(t_img *img, int offset, int col, int x)
{
	int		opp;
	int		dec;
	char	*data;

	opp = img->bpp / 8;
	data = img->data + offset;
	dec = opp;
	while (dec--)
	{
		if (img->image->byte_order)
			*(data + x * opp + dec) = col & 0xFF;
		else
			*(data + x * opp + opp - dec - 1) = col & 0xFF;
		col >>= 8;
	}
	return (0);
}

int	mlx_int_file_get_rid_comment(char *ptr, int size)
{
	int	begin;
	int	end;

	begin = mlx_int_str_str_cote(ptr, "/*", size);
	while (begin != -1)
	{
		end = mlx_int_str_str(ptr + begin + 2, "*/",
				size - begin - 2);
		memset(ptr + begin, ' ', end + 4);
		begin = mlx_int_str_str_cote(ptr, "/*", size);
	}
	begin = mlx_int_str_str_cote(ptr, "//", size);
	while (begin != -1)
	{
		end = mlx_int_str_str(ptr + begin + 2, "\n",
				size - begin - 2);
		memset(ptr + begin, ' ', end + 3);
		begin = mlx_int_str_str_cote(ptr, "//", size);
	}
	return (0);
}

void	*mlx_xpm_file_to_image(t_xvar *xvar, char *file,
		int *width, int *height)
{
	int		fd;
	int		size;
	char	*ptr;
	t_img	*img;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return ((void *)0);
	size = lseek(fd, 0, SEEK_END);
	if (size <= 0)
		return (close(fd), (void *)0);
	ptr = mmap(0, size, PROT_WRITE | PROT_READ, MAP_PRIVATE, fd, 0);
	if (ptr == MAP_FAILED)
		return (close(fd), (void *)0);
	mlx_int_file_get_rid_comment(ptr, size);
	img = mlx_int_parse_xpm(xvar, ptr, size, mlx_int_get_line);
	if (img)
	{
		*width = img->width;
		*height = img->height;
	}
	munmap(ptr, size);
	close(fd);
	return (img);
}

void	*mlx_xpm_to_image(t_xvar *xvar, char **xpm_data,
		int *width, int *height)
{
	t_img	*img;

	img = mlx_int_parse_xpm(xvar, xpm_data, 0, mlx_int_static_line);
	if (img)
	{
		*width = img->width;
		*height = img->height;
	}
	return (img);
}
