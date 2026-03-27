##
## Makefile for MiniLibX in /home/boulon/work/c/raytraceur/minilibx
##
## Made by Olivier Crouzet
## Login   <ol@epitech.net>
##
## Started on  Tue Oct  5 15:56:43 2004 Olivier Crouzet
## Last update Tue May 15 15:41:20 2007 Olivier Crouzet
##

## Please use configure script


INC	=%%%%

UNAME = $(shell uname)
CC	= gcc
ifeq ($(UNAME),FreeBSD)
	CC = clang
endif

NAME		= libmlx.a
NAME_UNAME	= libmlx_$(UNAME).a

SRC	= src/core/mlx_init.c src/core/mlx_init2.c \
	src/core/mlx_int_get_visual.c src/core/mlx_int_do_nothing.c \
	src/core/mlx_settings.c \
	src/window/mlx_new_window.c src/window/mlx_destroy_window.c \
	src/window/mlx_clear_window.c src/window/mlx_int_anti_resize_win.c \
	src/window/mlx_int_wait_first_expose.c \
	src/window/mlx_window_ext.c src/window/mlx_screen_size.c \
	src/window/mlx_destroy_display.c src/window/mlx_ext_randr.c \
	src/image/mlx_new_image.c src/image/mlx_new_xshm.c \
	src/image/mlx_destroy_image.c src/image/mlx_get_data_addr.c \
	src/image/mlx_put_image_to_window.c src/image/mlx_alpha.c \
	src/image/mlx_image_blit.c src/image/mlx_framebuffer.c \
	src/image/mlx_framebuffer2.c src/image/mlx_pixel_buf.c \
	src/event/mlx_hook.c src/event/mlx_key_hook.c \
	src/event/mlx_mouse_hook.c src/event/mlx_expose_hook.c \
	src/event/mlx_loop_hook.c src/event/mlx_int_param_event.c \
	src/event/mlx_int_param_event2.c \
	src/event/mlx_int_set_win_event_mask.c \
	src/event/mlx_flush_event.c src/event/mlx_loop.c \
	src/event/mlx_events.c src/event/mlx_events2.c \
	src/event/mlx_events3.c src/event/mlx_events4.c \
	src/draw/mlx_pixel_put.c src/draw/mlx_draw_line.c \
	src/draw/mlx_draw_rect.c src/draw/mlx_draw_circle.c \
	src/draw/mlx_draw_circle2.c \
	src/color/mlx_get_color_value.c src/color/mlx_color_pack.c \
	src/color/mlx_color_pack2.c src/color/mlx_color_ops.c \
	src/color/mlx_rgb.c \
	src/font/mlx_string_put.c src/font/mlx_set_font.c \
	src/font/mlx_font_data.c src/font/mlx_font_render.c \
	src/font/mlx_font_render2.c \
	src/input/mlx_mouse.c src/input/mlx_key_state.c \
	src/bind/mlx_bind.c src/bind/mlx_bind_map.c \
	src/bind/mlx_bind_dispatch.c \
	src/util/mlx_int_str_to_wordtab.c \
	src/util/mlx_int_str_to_wordtab2.c \
	src/util/mlx_math.c src/util/mlx_math2.c \
	src/util/mlx_errno.c src/util/mlx_errno2.c src/util/mlx_time.c \
	src/xpm/mlx_xpm_utils.c src/xpm/mlx_xpm_parse.c \
	src/xpm/mlx_xpm_parse2.c src/xpm/mlx_xpm.c \
	src/xpm/mlx_lib_xpm.c

OBJ_DIR = obj
OBJ	= $(addprefix $(OBJ_DIR)/,$(SRC:%.c=%.o))
CFLAGS	= -O3 -I include -I$(INC)

all	: $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(NAME)	: $(OBJ)
	ar -r $(NAME) $(OBJ)
	ranlib $(NAME)
	cp $(NAME) $(NAME_UNAME)

check: all
	@test/run_tests.sh

show:
	@printf "NAME  		: $(NAME)\n"
	@printf "NAME_UNAME	: $(NAME_UNAME)\n"
	@printf "CC		: $(CC)\n"
	@printf "CFLAGS		: $(CFLAGS)\n"
	@printf "SRC		:\n	$(SRC)\n"
	@printf "OBJ		:\n	$(OBJ)\n"

clean	:
	rm -rf $(OBJ_DIR)/ $(NAME) $(NAME_UNAME) *~ core *.core

.PHONY: all check show clean
