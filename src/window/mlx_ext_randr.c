/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_ext_randr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/03/09 15:37:15 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef MLX_USE_XRANDR

# include "mlx_int.h"
# include <X11/extensions/Xrandr.h>

static int	randr_find_output(t_xvar *xvar, XRRScreenResources *res,
		XRROutputInfo **out)
{
	int				i;
	int				idx;
	XRROutputInfo	*info;

	*out = NULL;
	idx = -1;
	i = res->noutput;
	while (i--)
	{
		info = XRRGetOutputInfo(xvar->display, res, res->outputs[i]);
		if (info->connection == RR_Connected)
		{
			*out = info;
			idx = i;
			i = 0;
		}
		else
			XRRFreeOutputInfo(info);
	}
	if (idx > 0)
		res->outputs[0] = res->outputs[idx];
	return (idx);
}

static RRMode	randr_find_mode(t_xvar *xvar, Window win,
		XRROutputInfo *o, XRRScreenResources *res)
{
	XWindowAttributes	watt;
	int					i;
	int					j;
	int					best;

	if (!XGetWindowAttributes(xvar->display, win, &watt))
		return (None);
	best = -1;
	i = -1;
	while (++i < o->nmode)
	{
		j = -1;
		while (++j < res->nmode)
			if (res->modes[j].id == o->modes[i]
				&& res->modes[j].width >= (unsigned int)watt.width
				&& res->modes[j].height >= (unsigned int)watt.height
				&& (best == -1
					|| res->modes[best].width > res->modes[j].width
					|| res->modes[best].height > res->modes[j].height))
				best = i;
	}
	if (best < 0)
		return (None);
	return (o->modes[best]);
}

static void	randr_apply_grab(t_xvar *xvar, t_win_list *win,
		int fullscreen)
{
	XMoveWindow(xvar->display, win->window, 0, 0);
	XMapRaised(xvar->display, win->window);
	if (fullscreen)
	{
		XGrabKeyboard(xvar->display, win->window, False,
			GrabModeAsync, GrabModeAsync, CurrentTime);
	}
	else
	{
		XUngrabPointer(xvar->display, CurrentTime);
		XUngrabKeyboard(xvar->display, CurrentTime);
	}
	XSync(xvar->display, False);
	sleep(1);
}

static int	randr_cleanup(XRRScreenResources *res,
		XRROutputInfo *info, XRRCrtcInfo *crtc)
{
	if (crtc)
		XRRFreeCrtcInfo(crtc);
	if (info)
		XRRFreeOutputInfo(info);
	XRRFreeScreenResources(res);
	return (0);
}

int	mlx_ext_fullscreen(t_xvar *xvar, t_win_list *win, int fullscreen)
{
	XRRScreenResources	*res;
	XRROutputInfo		*o_info;
	XRRCrtcInfo			*crtc;
	static RRMode		smode;
	RRMode				target;

	res = XRRGetScreenResources(xvar->display, xvar->root);
	if (randr_find_output(xvar, res, &o_info) < 0 || !o_info)
		return (randr_cleanup(res, NULL, NULL));
	crtc = XRRGetCrtcInfo(xvar->display, res, o_info->crtc);
	target = smode;
	if (fullscreen)
		target = randr_find_mode(xvar, win->window, o_info, res);
	if (!target)
		return (randr_cleanup(res, o_info, crtc));
	if (fullscreen)
		smode = crtc->mode;
	XRRSetCrtcConfig(xvar->display, res, o_info->crtc,
		CurrentTime, 0, 0, target, crtc->rotation,
		&res->outputs[0], 1);
	if (!fullscreen)
		smode = 0;
	randr_apply_grab(xvar, win, fullscreen);
	randr_cleanup(res, o_info, crtc);
	return (1);
}

#endif
