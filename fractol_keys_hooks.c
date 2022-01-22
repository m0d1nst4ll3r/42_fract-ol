/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_keys.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 18:35:07 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/22 11:39:51 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* --------------------------------------------------------------------- *\
|		key_hook
|
|	List of keys :
|		65505	shift				zoom in
|		61		-					zoom in
|		65507	ctrl				zoom out
|		45		=					zoom out
|		65362	upper arrow			move up
|		119		w					move up
|		65364	down arrow			move down
|		115		s					move down
|		65361	left arrow			move left
|		97		a					move left
|		65363	right arrow			move right
|		100		d					move right
|		114		r					reset view
|		101		e					next color
|		113		q					prev color
|		99		c					toggle smooth coloring
|		54		6					increase max iter by 1
|		53		5					decrease max iter by 1
|		52		3					increase max iter by 10
|		51		4					decrease max iter by 10
|		50		2					increase max iter by 100
|		49		1					decrease max iter by 100
|		65289	tab					enable auto iter
|		122		z					decrease zoom strength
|		120		x					increase zoom strength
|		105		i					display info
|		32		spacebar			render ssaa filter
|		118		v					decrease ssaa strength
|		98		b					increase ssaa strength
|		65293	return				toggle julia shift mode
|		65307	esc					close window
\* --------------------------------------------------------------------- */
static int	key_hook3(int key, t_fract *fract)
{
	if (key == 50)
		more_iter(fract, 1000);
	else if (key == 49)
		less_iter(fract, 1000);
	else if (key == 65289)
		enable_autoiter(fract);
	else if (key == 122)
		decrease_zoom_strength(fract);
	else if (key == 120)
		increase_zoom_strength(fract);
	else if (key == 105)
		print_info(*fract);
	else if (key == 32)
		apply_ssaa_filter(fract);
	else if (key == 118)
		decrease_ssaa_strength(fract);
	else if (key == 98)
		increase_ssaa_strength(fract);
	else if (key == 65293)
		toggle_shift_mode(fract);
	else if (key == 65307)
		exit_program(*fract);
	return (0);
}

static int	key_hook2(int key, t_fract *fract)
{
	if (key == 114)
		reset_view(fract);
	else if (key == 101)
		next_color(fract);
	else if (key == 113)
		prev_color(fract);
	else if (key == 99)
		toggle_smooth_colors(fract);
	else if (key == 56)
		more_iter(fract, 1);
	else if (key == 55)
		less_iter(fract, 1);
	else if (key == 54)
		more_iter(fract, 10);
	else if (key == 53)
		less_iter(fract, 10);
	else if (key == 52)
		more_iter(fract, 100);
	else if (key == 51)
		less_iter(fract, 100);
	else
		return (key_hook3(key, fract));
	return (0);
}

int	key_hook(int key, t_fract *fract)
{
	int	x;
	int	y;

	if (key == 65505 || key == 61)
	{
		mlx_mouse_get_pos(fract->mlx, fract->win, &x, &y);
		zoom_in(fract, x, y);
	}
	else if (key == 65507 || key == 45)
	{
		mlx_mouse_get_pos(fract->mlx, fract->win, &x, &y);
		zoom_out(fract, x, y);
	}
	else if (key == 65362 || key == 119)
		move_view(fract, 'u', MOVE_MOD);
	else if (key == 65364 || key == 115)
		move_view(fract, 'd', MOVE_MOD);
	else if (key == 65361 || key == 97)
		move_view(fract, 'l', MOVE_MOD);
	else if (key == 65363 || key == 100)
		move_view(fract, 'r', MOVE_MOD);
	else
		return (key_hook2(key, fract));
	return (0);
}

/* --------------------------------------------------------------------- *\
|		mouse_hook
|
|	List of mouse buttons :
|		1		left mouse button		zoom in
|		4		mousewheel up			zoom in
|		3		right mouse button		zoom out
|		5		mousewheel down			zoom out
\* --------------------------------------------------------------------- */
int	mouse_hook(int key, int x, int y, t_fract *fract)
{
	if (key == 1 || key == 4)
		zoom_in(fract, x, y);
	else if (key == 3 || key == 5)
		zoom_out(fract, x, y);
	return (0);
}

int	clientmsg_hook(t_fract *fract)
{
	exit_program(*fract);
	return (0);
}
