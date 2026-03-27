/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/09 14:58:21 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_ext_int.h"

static t_hookstore	*get_hookstore(void)
{
	static t_hookstore	store;

	return (&store);
}

static t_mlx_ext_hooks	*find_hooks(void *win)
{
	t_hookstore	*s;
	int			i;

	s = get_hookstore();
	i = 0;
	while (i < MAX_WIN_HOOKS)
	{
		if (s->wins[i] == win)
			return (&s->hooks[i]);
		i++;
	}
	return (NULL);
}

static t_mlx_ext_hooks	*alloc_hooks(void *win)
{
	t_hookstore	*s;
	int			i;

	s = get_hookstore();
	i = 0;
	while (i < MAX_WIN_HOOKS)
	{
		if (!s->wins[i])
		{
			s->wins[i] = win;
			memset(&s->hooks[i], 0, sizeof(t_mlx_ext_hooks));
			return (&s->hooks[i]);
		}
		i++;
	}
	return (NULL);
}

t_mlx_ext_hooks	*mlx_ext_get_hooks(void *win)
{
	t_mlx_ext_hooks	*h;

	h = find_hooks(win);
	if (h)
		return (h);
	return (alloc_hooks(win));
}

void	mlx_on_key(void *win, t_mlx_keyfn fn, void *param)
{
	t_mlx_ext_hooks	*h;

	h = mlx_ext_get_hooks(win);
	if (!h)
		return ;
	h->key_fn = fn;
	h->key_param = param;
	mlx_hook(win, X_KEY_PRESS, X_KEY_PRESS_MASK,
		(t_mlx_hcb){mlx_ext_key_dispatch, h});
	mlx_hook(win, X_KEY_RELEASE, X_KEY_RELEASE_MASK,
		(t_mlx_hcb){mlx_ext_keyrel_dispatch, h});
}
