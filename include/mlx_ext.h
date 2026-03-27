/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_ext.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/09 14:19:24 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_EXT_H
# define MLX_EXT_H

# include "mlx.h"

/* --- Error codes --------------------------------------------------------- */

# define MLX_OK       0
# define MLX_EALLOC   1
# define MLX_EIMG     2
# define MLX_EFILE    3
# define MLX_EPNG     4
# define MLX_EINVAL   5
# define MLX_ERRMAX   6

/* --- Event action constants ---------------------------------------------- */

# define MLX_PRESS    1
# define MLX_RELEASE  0

/* --- Modifier key bitmask ------------------------------------------------ */

# define MLX_MOD_SHIFT  1
# define MLX_MOD_CTRL   2
# define MLX_MOD_ALT    4

/* --- Window creation flags ----------------------------------------------- */

# define MLX_WIN_RESIZABLE   1
# define MLX_WIN_DECORATED   2

/* --- Settings keys ------------------------------------------------------- */

# define MLX_SET_FPS_CAP     0
# define MLX_SET_MAX         1

/* --- Font dimensions (built-in 8x8 bitmap font) ------------------------- */

# define MLX_FONT_W    8
# define MLX_FONT_H    8

/* --- Scroll directions (mapped from X11 button 4/5) ---------------------- */

# define MLX_SCROLL_UP    4
# define MLX_SCROLL_DOWN  5

/* --- Core types ---------------------------------------------------------- */

typedef struct s_mlx_fb
{
	void	*img;
	char	*data;
	int		bpp;
	int		line_len;
	int		endian;
	int		w;
	int		h;
}	t_mlx_fb;

typedef struct s_mlx_rect
{
	int	x;
	int	y;
	int	w;
	int	h;
}	t_mlx_rect;

typedef struct s_mlx_line
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
	int	col0;
	int	col1;
}	t_mlx_line;

typedef struct s_mlx_keydata
{
	int	key;
	int	action;
	int	mods;
}	t_mlx_keydata;

typedef struct s_mlx_mousedata
{
	int	button;
	int	action;
	int	x;
	int	y;
}	t_mlx_mousedata;

typedef struct s_mlx_text
{
	int	x;
	int	y;
	int	color;
	int	scale;
}	t_mlx_text;

typedef struct s_mlx_circle
{
	int	cx;
	int	cy;
	int	r;
	int	color;
}	t_mlx_circle;

/* --- Callback typedefs --------------------------------------------------- */

typedef void	(*t_mlx_keyfn)(t_mlx_keydata kd, void *p);
typedef void	(*t_mlx_mousefn)(t_mlx_mousedata md, void *p);
typedef void	(*t_mlx_motionfn)(int x, int y, void *p);
typedef void	(*t_mlx_closefn)(void *p);
typedef void	(*t_mlx_exposefn)(void *p);
typedef void	(*t_mlx_scrollfn)(int dir, int x, int y, void *p);
typedef void	(*t_mlx_resizefn)(int w, int h, void *p);
typedef void	(*t_mlx_bindfn)(t_mlx_keydata kd, void *param);

/* --- Error system -------------------------------------------------------- */

int				mlx_get_errno(void);
void			mlx_set_errno(int code);
const char		*mlx_strerror(int code);
void			mlx_perror(const char *prefix);

/* --- Math utilities ------------------------------------------------------ */

int				mlx_clamp_i(int val, int lo, int hi);
float			mlx_clamp_f(float val, float lo, float hi);
float			mlx_lerp_f(float a, float b, float t);
int				mlx_min_i(int a, int b);
int				mlx_max_i(int a, int b);
int				mlx_abs_i(int val);

/* --- Color construction and extraction ----------------------------------- */

int				mlx_rgba(int r, int g, int b, int a);
int				mlx_rgb(int r, int g, int b);
int				mlx_get_r(int color);
int				mlx_get_g(int color);
int				mlx_get_b(int color);
int				mlx_get_a(int color);

/* --- Color operations ---------------------------------------------------- */

int				mlx_lerp_color(int c1, int c2, float t);
int				mlx_blend_alpha(int fg, int bg);
int				mlx_color_darken(int color, float f);
int				mlx_color_brighten(int color, float f);

/* --- Framebuffer management ---------------------------------------------- */

t_mlx_fb		*mlx_new_fb(void *mlx, int w, int h);
void			mlx_destroy_fb(void *mlx, t_mlx_fb *fb);
void			mlx_fb_render(void *mlx, void *win, t_mlx_fb *fb);
void			mlx_fb_render_at(t_mlx_fb *fb, void *ctx[3]);
t_mlx_fb		*mlx_fb_resize(void *mlx, t_mlx_fb *fb, t_mlx_point sz);
t_mlx_fb		*mlx_fb_copy(void *mlx, t_mlx_fb *src);

/* --- Fast pixel operations on image buffers ------------------------------ */

void			mlx_buf_pixel_put(t_mlx_fb *fb, int x, int y, int col);
int				mlx_buf_pixel_get(t_mlx_fb *fb, int x, int y);
void			mlx_buf_clear(t_mlx_fb *fb, int color);

/* --- Drawing primitives -------------------------------------------------- */

void			mlx_draw_line(t_mlx_fb *fb, t_mlx_line *ln);
void			mlx_draw_rect(t_mlx_fb *fb, t_mlx_rect *r, int col);
void			mlx_fill_rect(t_mlx_fb *fb, t_mlx_rect *r, int col);
void			mlx_draw_circle(t_mlx_fb *fb, t_mlx_circle *c);
void			mlx_fill_circle(t_mlx_fb *fb, t_mlx_circle *c);

/* --- Font / text rendering ----------------------------------------------- */

void			*mlx_get_glyph(char c);
void			mlx_put_char(t_mlx_fb *fb, char c, t_mlx_text *p);
void			mlx_put_str(t_mlx_fb *fb, const char *s,
					t_mlx_text *p);
int				mlx_text_width(const char *str, int scale);
int				mlx_text_height(int scale);

/* --- Typed event hooks --------------------------------------------------- */

void			mlx_on_key(void *win, t_mlx_keyfn fn, void *param);
void			mlx_on_mouse(void *win, t_mlx_mousefn fn, void *p);
void			mlx_on_motion(void *win, t_mlx_motionfn fn, void *p);
void			mlx_on_close(void *win, t_mlx_closefn fn, void *p);
void			mlx_on_expose(void *win, t_mlx_exposefn fn, void *p);
void			mlx_on_scroll(void *win, t_mlx_scrollfn fn, void *p);

/* --- Modifier and key state tracking ------------------------------------- */

int				mlx_get_mods(void *win);
int				mlx_is_key_down(void *mlx, int keysym);
int				mlx_is_mouse_down(void *mlx, int button);

/* --- Frame timing -------------------------------------------------------- */

double			mlx_get_time(void);
double			mlx_delta_time(void *mlx);
double			mlx_get_fps(void *mlx);

/* --- Alpha compositing and image operations ------------------------------ */

void			mlx_alpha_blit(t_mlx_fb *dst, t_mlx_fb *src, t_mlx_point p);
void			mlx_set_image_alpha(t_mlx_fb *fb, int alpha);
void			mlx_blit(t_mlx_fb *dst, t_mlx_fb *src, t_mlx_point p);
void			mlx_blit_rect(t_mlx_fb *d, t_mlx_fb *s, t_mlx_rect *sr);

/* --- Window extensions --------------------------------------------------- */

void			*mlx_new_window_ext(void *mlx, t_mlx_point sz, char *t,
					int flags);
void			mlx_set_win_title(void *mlx, void *win, char *title);
void			mlx_set_setting(int key, int value);
int				mlx_get_setting(int key);

/* --- Key binding dispatch system ----------------------------------------- */

# define MLX_BIND_SLOTS  192
# define MLX_BIND_MODS   8

int				mlx_map_keysym(int keysym);
int				mlx_mod_index(int mods);
void			mlx_bind_key(int keysym, int mods, t_mlx_bindfn fn);
void			mlx_unbind_key(int keysym, int mods);
void			mlx_unbind_all(void);
t_mlx_bindfn	mlx_find_binding(int keysym, int mods);
void			mlx_key_dispatch(void *win, void *param);

#endif
