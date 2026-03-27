/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/09 14:19:23 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_H
# define MLX_H

typedef struct s_mlx_point
{
	int	x;
	int	y;
}	t_mlx_point;

typedef struct s_mlx_str
{
	int	x;
	int	y;
	int	color;
}	t_mlx_str;

typedef int		(*t_mlx_hookfn)();

typedef struct s_mlx_hcb
{
	t_mlx_hookfn	funct;
	void			*param;
}	t_mlx_hcb;

void	*mlx_init(void);
void	*mlx_new_window(void *mlx_ptr, int size_x, int size_y, char *title);
int		mlx_clear_window(void *mlx_ptr, void *win_ptr);
int		mlx_pixel_put(void *mlx_ptr, void *win_ptr,
			t_mlx_point pos, int color);
void	*mlx_new_image(void *mlx_ptr, int width, int height);
char	*mlx_get_data_addr(void *img_ptr, int *bits_per_pixel,
			int *size_line, int *endian);
int		mlx_put_image_to_window(void *mlx_ptr, void *win_ptr,
			void *img_ptr, t_mlx_point pos);
int		mlx_get_color_value(void *mlx_ptr, int color);
int		mlx_mouse_hook(void *win_ptr, int (*funct_ptr)(), void *param);
int		mlx_key_hook(void *win_ptr, int (*funct_ptr)(), void *param);
int		mlx_expose_hook(void *win_ptr, int (*funct_ptr)(), void *param);
int		mlx_loop_hook(void *mlx_ptr, int (*funct_ptr)(), void *param);
int		mlx_loop(void *mlx_ptr);
int		mlx_loop_end(void *mlx_ptr);
int		mlx_string_put(void *mlx_ptr, void *win_ptr,
			t_mlx_str txt, char *string);
void	mlx_set_font(void *mlx_ptr, void *win_ptr, char *name);
void	*mlx_xpm_to_image(void *mlx_ptr, char **xpm_data,
			int *width, int *height);
void	*mlx_xpm_file_to_image(void *mlx_ptr, char *filename,
			int *width, int *height);
int		mlx_destroy_window(void *mlx_ptr, void *win_ptr);
int		mlx_destroy_image(void *mlx_ptr, void *img_ptr);
int		mlx_destroy_display(void *mlx_ptr);
int		mlx_hook(void *win_ptr, int x_event,
			int x_mask, t_mlx_hcb cb);
int		mlx_do_key_autorepeatoff(void *mlx_ptr);
int		mlx_do_key_autorepeaton(void *mlx_ptr);
int		mlx_do_sync(void *mlx_ptr);
int		mlx_mouse_get_pos(void *mlx_ptr, void *win_ptr, int *x, int *y);
int		mlx_mouse_move(void *mlx_ptr, void *win_ptr, int x, int y);
int		mlx_mouse_hide(void *mlx_ptr, void *win_ptr);
int		mlx_mouse_show(void *mlx_ptr, void *win_ptr);
int		mlx_get_screen_size(void *mlx_ptr, int *sizex, int *sizey);

#endif
