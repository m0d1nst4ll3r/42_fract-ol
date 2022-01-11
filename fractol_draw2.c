/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_draw2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:51:58 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/11 17:10:39 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//	Calculates escape_time and renders it based on a palette
void	render_fractal(t_fract fract)
{
	calculate_map(fract);
	draw_fractal(fract);
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
	render_fractal(*fractal);
}
