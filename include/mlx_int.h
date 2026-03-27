/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_int.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/09 14:58:20 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_INT_H
# define MLX_INT_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/mman.h>
# include <X11/Xlib.h>
# include <X11/Xutil.h>
# include <sys/ipc.h>
# include <sys/shm.h>
# include <X11/extensions/XShm.h>
# include <X11/XKBlib.h>

# define MLX_TYPE_SHM_PIXMAP 3
# define MLX_TYPE_SHM 2
# define MLX_TYPE_XIMAGE 1
# define MLX_MAX_EVENT LASTEvent
# define ENV_DISPLAY "DISPLAY"
# define LOCALHOST "localhost"
# define ERR_NO_TRUECOLOR "MinilibX: No TrueColor Visual.\n"
# define WARN_SHM_ATTACH "MinilibX: Can't attach shared memory.\n"

typedef struct s_xpm_col
{
	int		name;
	int		col;
}	t_xpm_col;

typedef struct s_col_name
{
	char	*name;
	int		color;
}	t_col_name;

typedef struct s_event_list
{
	int		mask;
	int		(*hook)();
	void	*param;
}	t_event_list;

typedef struct s_win_list
{
	Window				window;
	GC					gc;
	struct s_win_list	*next;
	int					(*mouse_hook)();
	int					(*key_hook)();
	int					(*expose_hook)();
	void				*mouse_param;
	void				*key_param;
	void				*expose_param;
	t_event_list		hooks[MLX_MAX_EVENT];
}	t_win_list;

typedef struct s_img
{
	XImage			*image;
	Pixmap			pix;
	GC				gc;
	int				size_line;
	int				bpp;
	int				width;
	int				height;
	int				type;
	int				format;
	char			*data;
	XShmSegmentInfo	shm;
}	t_img;

typedef struct s_xvar
{
	Display		*display;
	Window		root;
	int			screen;
	int			depth;
	Visual		*visual;
	Colormap	cmap;
	int			private_cmap;
	t_win_list	*win_list;
	int			(*loop_hook)();
	void		*loop_param;
	int			use_xshm;
	int			pshm_format;
	int			do_flush;
	int			decrgb[6];
	Atom		wm_delete_window;
	Atom		wm_protocols;
	int			end_loop;
}	t_xvar;

typedef int		(*t_param_fn)(t_xvar *, XEvent *, t_win_list *);
typedef char	*(*t_xpm_line_fn)(void *, int *, int);

typedef struct s_xpm_ctx
{
	t_xpm_col	*colors;
	int			*colors_direct;
	char		**tab;
	t_img		*img;
	int			width;
	int			height;
	int			nc;
	int			cpp;
	int			method;
	int			pos;
}	t_xpm_ctx;

int				mlx_int_do_nothing(void *param);
int				mlx_int_get_good_color(t_xvar *xvar, int color);
int				mlx_int_anti_resize_win(t_xvar *xvar, Window win,
					int w, int h);
int				mlx_int_wait_first_expose(t_xvar *xvar, Window win);
int				mlx_int_rgb_conversion(t_xvar *xvar);
int				mlx_int_deal_shm(t_xvar *xvar);
void			*mlx_int_new_xshm_image(t_xvar *xvar, int width,
					int height, int format);
void			*mlx_int_new_image(t_xvar *xvar, int width,
					int height, int format);
char			**mlx_int_str_to_wordtab(char *str);

# ifndef MLX_H

int				mlx_get_color_value(t_xvar *xvar, int color);
void			*mlx_new_image(t_xvar *xvar, int width, int height);

# endif

int				mlx_shm_err_handler(Display *d, XErrorEvent *ev);
int				mlx_int_get_visual(t_xvar *xvar);
int				mlx_int_set_win_event_mask(t_xvar *xvar);
int				mlx_int_str_str_cote(char *str, char *find, int len);
int				mlx_int_str_str(char *str, char *find, int len);
int				mlx_int_param_undef(t_xvar *x, XEvent *e,
					t_win_list *w);
int				mlx_int_param_keypress(t_xvar *x, XEvent *e,
					t_win_list *w);
int				mlx_int_param_keyrelease(t_xvar *x, XEvent *e,
					t_win_list *w);
int				mlx_int_param_btnpress(t_xvar *x, XEvent *e,
					t_win_list *w);
int				mlx_int_param_btnrelease(t_xvar *x, XEvent *e,
					t_win_list *w);
int				mlx_int_param_generic(t_xvar *x, XEvent *e,
					t_win_list *w);
int				*mlx_x_err(void);
t_param_fn		*mlx_get_param_events(void);
t_col_name		*mlx_get_col_names(void);

unsigned int	mlx_int_strlcpy(char *dst, char *src, unsigned int size);
char			*mlx_int_get_line(void *info, int *pos, int size);
char			*mlx_int_static_line(void *info, int *pos, int size);
int				mlx_int_get_col_name(char *str, int size);
int				mlx_int_get_text_rgb(char *name, char *end);
int				mlx_int_xpm_set_pixel(t_img *img, int offset,
					int col, int x);
void			*mlx_int_parse_xpm(t_xvar *xvar, void *info,
					int info_size, t_xpm_line_fn f);
int				mlx_int_file_get_rid_comment(char *ptr, int size);
int				xpm_parse_pixels(t_xpm_ctx *ctx, void *info,
					int size, t_xpm_line_fn f);
int				xpm_read_colors(t_xpm_ctx *c, void *info,
					int sz, t_xpm_line_fn f);

#endif
