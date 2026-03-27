/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_ext_int.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/09 14:58:20 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_EXT_INT_H
# define MLX_EXT_INT_H

# include "mlx_ext.h"
# include "mlx_int.h"
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <unistd.h>

/* --- X11 event type constants -------------------------------------------- */

# define X_KEY_PRESS       2
# define X_KEY_RELEASE     3
# define X_BUTTON_PRESS    4
# define X_BUTTON_RELEASE  5
# define X_MOTION_NOTIFY   6
# define X_EXPOSE          12
# define X_DESTROY_NOTIFY  17
# define X_CONFIGURE       22

# define X_KEY_PRESS_MASK      1
# define X_KEY_RELEASE_MASK    2
# define X_BUTTON_PRESS_MASK   4
# define X_BUTTON_RELEASE_MASK 8
# define X_POINTER_MOTION_MASK 64
# define X_EXPOSURE_MASK       32768
# define X_STRUCTURE_MASK      131072

/* --- X11 keysym constants for modifier keys ------------------------------ */

# define XK_SHIFT_L    0xffe1
# define XK_SHIFT_R    0xffe2
# define XK_CTRL_L     0xffe3
# define XK_CTRL_R     0xffe4
# define XK_ALT_L      0xffe9
# define XK_ALT_R      0xffea

/* --- Internal Bresenham line drawing state ------------------------------- */

typedef struct s_mlx_bres
{
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		steps;
	int		step;
	float	cr;
	float	cg;
	float	cb;
}	t_mlx_bres;

/* --- Internal key/mouse state tracking ----------------------------------- */

# define MLX_MAX_KEYS   512
# define MLX_MAX_BTNS   8

typedef struct s_mlx_input_state
{
	int		keys[MLX_MAX_KEYS];
	int		btns[MLX_MAX_BTNS];
	int		initialized;
}	t_mlx_input_state;

/* --- Internal event callback storage (per window) ------------------------ */

typedef struct s_mlx_ext_hooks
{
	t_mlx_keyfn		key_fn;
	void			*key_param;
	t_mlx_mousefn	mouse_fn;
	void			*mouse_param;
	t_mlx_motionfn	motion_fn;
	void			*motion_param;
	t_mlx_closefn	close_fn;
	void			*close_param;
	t_mlx_exposefn	expose_fn;
	void			*expose_param;
	t_mlx_scrollfn	scroll_fn;
	void			*scroll_param;
	t_mlx_resizefn	resize_fn;
	void			*resize_param;
	int				mods;
}	t_mlx_ext_hooks;

# define MAX_WIN_HOOKS 16

typedef struct s_hookstore
{
	void			*wins[MAX_WIN_HOOKS];
	t_mlx_ext_hooks	hooks[MAX_WIN_HOOKS];
}	t_hookstore;

/* --- Singleton accessors ------------------------------------------------- */

t_mlx_ext_hooks		*mlx_ext_get_hooks(void *win);
t_mlx_input_state	*mlx_ext_get_input(void);

/* --- Internal Bresenham helpers ------------------------------------------ */

void				mlx_ext_bres_init(t_mlx_bres *b, t_mlx_line *ln);
int					mlx_ext_bres_color(t_mlx_line *ln, t_mlx_bres *b);

/* --- Internal circle drawing helpers ------------------------------------- */

void				mlx_ext_circle_pts(t_mlx_fb *fb, t_mlx_circle *c,
						t_mlx_point o);
void				mlx_ext_circle_fill_row(t_mlx_fb *fb, t_mlx_circle *c,
						t_mlx_point o);

/* --- Internal event dispatch helpers ------------------------------------- */

int					mlx_ext_key_dispatch(int ks, void *p);
int					mlx_ext_keyrel_dispatch(int ks, void *p);
int					mlx_ext_mouse_dispatch(int btn, int x, int y, void *p);
int					mlx_ext_mouserel_dispatch(int btn, int x, int y,
						void *p);
int					mlx_ext_motion_dispatch(int x, int y, void *p);
int					mlx_ext_close_dispatch(void *p);
int					mlx_ext_expose_dispatch(void *p);

#endif
