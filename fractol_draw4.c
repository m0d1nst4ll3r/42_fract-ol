/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_draw4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:51:58 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/18 03:58:25 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* --------------------------------------------------------------------- *\
|		render_fractal
|
|	Renders and displays a view of the fractal according to current
|		position and zoom values.
|
|	Flag is tested against the following defines values :
|		- RENDER_RECOLOR	do not recalculate the iterations map
|						  used when no calculations are needed
|						  (ex: changing colors)
|		- RENDER_REITER		recalculate the iterations map partially
|						  used when increasing max_iter beyond the
|						  highest iteration value calculated so far
|						  (only the black pixels need to be recalculated)
|
|	The operation requires swapping two images, exactly like double
|		buffering. This avoids writing over an image being displayed
|		which is necessary to avoid screen-tearing.
\* --------------------------------------------------------------------- */
void	render_fractal(t_fract *fract, int flag)
{
	t_img	tmp;

	if (flag != RENDER_RECOLOR)
	{
		if (flag != RENDER_REITER)
			fract->highest_iter = 0;
		thread_task(fract, 'c');
		fract->highest_iter = fract->max_iter;
	}
	thread_task(fract, 'd');
	tmp = fract->img_main;
	fract->img_main = fract->img_temp;
	fract->img_temp = tmp;
	mlx_put_image_to_window(fract->mlx, fract->win, fract->img_main.img, 0, 0);
}

/* --------------------------------------------------------------------- *\
|		fractol_reset_pos
|
|	Resets a fractal's step, pos.x and pos.y to default ones.
|
|	A bigger window will naturally cause a lower step (more zoomed).
|
|	Mandelbrot fractals are offset by -0.75 on the x axis to account for
|		its particular shape.
|	Julia fractals are always centered around 0.
|
|	Mandelbrot graphs are considered to be :
|		x	-2 to 0.5
|		y	-1.5 to 1.5
|	Julia graphs are considered to be :
|		x	-2 to 2
|		y	-1.5 to 1.5
\* --------------------------------------------------------------------- */
void	reset_pos(t_fract *fract)
{
	long double	step_tmp;

	if (fract->type == 'm')
	{
		fract->step = 2.5 / fract->winx;
		step_tmp = 2.5 / fract->winy;
		if (fract->step < step_tmp)
			fract->step = step_tmp;
		fract->pos.x = -fract->winx / 2 * fract->step - 0.75;
		fract->pos.y = fract->winy / 2 * fract->step;
	}
	else
	{
		fract->step = 4.0 / fract->winx;
		step_tmp = 3.0 / fract->winy;
		if (fract->step < step_tmp)
			fract->step = step_tmp;
		fract->pos.x = -fract->winx / 2 * fract->step;
		fract->pos.y = fract->winy / 2 * fract->step;
	}
	if (fract->autoiter && fract->step <= 0.00364)
		fract->max_iter = (int)(-400 * logl(fract->step) - 2196);
	else if (fract->autoiter)
		fract->max_iter = 50;
}

//	Resets view back to the beginning and renders the fractal
void	reset_view(t_fract *fractal)
{
	reset_pos(fractal);
	render_fractal(fractal, 0);
}
