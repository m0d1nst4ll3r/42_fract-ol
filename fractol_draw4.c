/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_draw4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:51:58 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/12 18:39:36 by rpohlen          ###   ########.fr       */
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
		calculate_map(*fract, fract->highest_iter);
		fract->highest_iter = fract->max_iter;
	}
	draw_fractal(*fract);
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
void	reset_pos(t_fract *fractal)
{
	long double	step_tmp;

	if (fractal->type == 'm')
	{
		fractal->step = 2.5 / fractal->winx;
		step_tmp = 2.5 / fractal->winy;
		if (fractal->step < step_tmp)
			fractal->step = step_tmp;
		fractal->pos.x = -fractal->winx / 2 * fractal->step - 0.75;
		fractal->pos.y = fractal->winy / 2 * fractal->step;
	}
	else
	{
		fractal->step = 4.0 / fractal->winx;
		step_tmp = 3.0 / fractal->winy;
		if (fractal->step < step_tmp)
			fractal->step = step_tmp;
		fractal->pos.x = -fractal->winx / 2 * fractal->step;
		fractal->pos.y = fractal->winy / 2 * fractal->step;
	}
}

//	Resets view back to the beginning and renders the fractal
void	reset_view(t_fract *fractal)
{
	reset_pos(fractal);
	render_fractal(fractal, 0);
}
