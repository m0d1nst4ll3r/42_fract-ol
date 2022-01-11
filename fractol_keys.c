/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_keys.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 18:35:07 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/11 17:32:09 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* --------------------------------------------------------------------- *\
|		key_hook
|
|	List of keys :
|		65505	shift				zoom in
|		65507	ctrl				zoom out
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
|		54		6					increase max iter by 1
|		53		5					decrease max iter by 1
|		52		3					increase max iter by 10
|		51		4					decrease max iter by 10
|		50		2					increase max iter by 100
|		49		1					decrease max iter by 100
|		65289	tab					enable auto iter
|		105		i					display info
|		65307	esc					close window
\* --------------------------------------------------------------------- */
int	key_hook(int key, t_fract *fract)
{
	int x;
	int y;

	printf("Key down %d\n", key);
	if (key == 65505)
	{
		mlx_mouse_get_pos(fract->mlx, fract->win, &x, &y);
		zoom_in(fract, x, y);
	}
	else if (key == 65507)
	{
		mlx_mouse_get_pos(fract->mlx, fract->win, &x, &y);
		zoom_out(fract, x, y);
	}
	//else if (key == 65362 || key == 119)
	//else if (key == 65364 || key == 115)
	//else if (key == 65361 || key == 97)
	//else if (key == 65363 || key == 100)
	else if (key == 114)
		reset_view(fract);
	else if (key == 101)
		next_color(fract);
	else if (key == 113)
		prev_color(fract);
	else if (key == 54)
		more_iter(fract, 1);
	else if (key == 53)
		less_iter(fract, 1);
	else if (key == 52)
		more_iter(fract, 10);
	else if (key == 51)
		less_iter(fract, 10);
	else if (key == 50)
		more_iter(fract, 100);
	else if (key == 49)
		less_iter(fract, 100);
	//else if (key == 65289)
	//else if (key == 105)
	//else if (key == 65307)
/*	if (key == 61 || key == 45 || (key >= 65361 && key <= 65364))
	{
		if (key == 61)
			data->max_iter += DEPTH_MOD;
		else if (key == 45 && data->max_iter <= DEPTH_MOD)
			data->max_iter = 1;
		else if (key == 45)
			data->max_iter -= DEPTH_MOD;
		else if (key == 65362)
			data->pos.y += MOVE_MOD * data->step;
		else if (key == 65361)
			data->pos.x -= MOVE_MOD * data->step;
		else if (key == 65364)
			data->pos.y -= MOVE_MOD * data->step;
		else if (key == 65363)
			data->pos.x += MOVE_MOD * data->step;
		draw_fractal(*data);
		mlx_put_image_to_window(data->mlx, data->win, data->img_main.img, 0, 0);
	}
	else if (key == 104)
		print_info(*data);*/
	return (0);
}

/* --------------------------------------------------------------------- *\
|		mouse_hook
|
|	List of mouse buttons :
|		3		right mouse button		(hold) move view
|										(click) zoom in
|		1		left mouse button		(hold) draw zoom area
|										(click) zoom out
|		4		mousewheel up			zoom in
|		5		mousewheel down			zoom out
\* --------------------------------------------------------------------- */
int	mouse_hook(int key, int x, int y, t_fract *data)
{
	printf("Mouse down %d\t\t%d\t%d\n", key, x, y);
	(void)data;
	(void)x;
	(void)y;
	/*if (key == 4 || key == 5)
	{
		if (key == 4)
		{
			data->pos.x += x * data->step - x * data->step / data->zoom;
			data->pos.y -= y * data->step - y * data->step / data->zoom;
			data->step = data->step / data->zoom;
		}
		else if (key == 5)
		{
			data->pos.x -= x * data->step - x * data->step / data->zoom;
			data->pos.y += y * data->step - y * data->step / data->zoom;
			data->step = data->step * data->zoom;
		}
		draw_fractal(*data);
		mlx_put_image_to_window(data->mlx, data->win, data->img_main.img, 0, 0);
	}*/
	return (0);
}
