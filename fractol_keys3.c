/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_keys3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 17:07:24 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/18 16:23:58 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* --------------------------------------------------------------------- *\
|		zoom_in zoom_out
|
|	x and y are checked for validity (in case they are outside the window)
|		in which case we zoom at the center of the window by default.
|
|	Zooming happens in two parts. (before rendering)
|
|	First we decrease or increase the step value to enlarge/decrease
|		the magnification.
|
|	Second we move the pos value to match the cursor's position,
|		that is we move it on an imaginary line between itself and
|		the cursor, on a distance depending on zoom strength.
|
|	If auto incrementation is toggled on, we also update max_iter
|		based on the step value. The function is an inverted normalized
|		log, so max_iter rises linearly on a log scale when step decreases.
|
|	AI_A, AI_B and AI_T are variables used in the inverted log equation,
|		defined in fractol.h for ease of change.
|	See fractol_keys2.c enable_autoiter for a detailed explanation on the
|		equation.
\* --------------------------------------------------------------------- */
void	zoom_in(t_fract *fract, int x, int y)
{
	if (x < 0 || x > fract->winx || y < 0 || y > fract->winy)
	{
		x = fract->winx / 2;
		y = fract->winy / 2;
	}
	fract->pos.x += x * fract->step - x * fract->step / fract->zoom;
	fract->pos.y -= y * fract->step - y * fract->step / fract->zoom;
	fract->step = fract->step / fract->zoom;
	if (fract->autoiter && fract->step <= AI_T)
		fract->max_iter = (int)(-AI_A * logl(fract->step) - AI_B);
	else if (fract->autoiter)
		fract->max_iter = 50;
	render_fractal(fract, 0);
}

void	zoom_out(t_fract *fract, int x, int y)
{
	if (x < 0 || x > fract->winx || y < 0 || y > fract->winy)
	{
		x = fract->winx / 2;
		y = fract->winy / 2;
	}
	fract->pos.x += x * fract->step - x * fract->step * fract->zoom;
	fract->pos.y -= y * fract->step - y * fract->step * fract->zoom;
	fract->step = fract->step * fract->zoom;
	if (fract->autoiter && fract->step <= AI_T)
		fract->max_iter = (int)(-AI_A * logl(fract->step) - AI_B);
	else if (fract->autoiter)
		fract->max_iter = 50;
	render_fractal(fract, 0);
}

/* --------------------------------------------------------------------- *\
|		move_view
|
|	Moving the view happens in three parts. (before rendering)
|
|	First we move the pos value to slide our area up, down, left or right.
|
|	Second we move the entire int 2D array, the iteration map, in one
|		direction to make room for the new rows/columns.
|
|	Third we calculate those rows/columns the same way we calculate an
|		entire frame, only we do it partially.
|
|	The second and third steps are done in calculate_map_partial.
\* --------------------------------------------------------------------- */
void	move_view(t_fract *fract, char direction, int n)
{
	if (direction == 'u')
		fract->pos.y = fract->pos.y + fract->step * n;
	else if (direction == 'd')
		fract->pos.y = fract->pos.y - fract->step * n;
	else if (direction == 'l')
		fract->pos.x = fract->pos.x - fract->step * n;
	else
		fract->pos.x = fract->pos.x + fract->step * n;
	calculate_map_partial(*fract, direction, n);
	render_fractal(fract, RENDER_RECOLOR);
}

//	This simply changes zoom strength based on an arbitrary scale
void	decrease_zoom_strength(t_fract *fract)
{
	if (fract->zoom <= 1.015)
		return ;
	else if (fract->zoom <= 1.1)
		fract->zoom -= 0.01;
	else if (fract->zoom <= 1.5)
		fract->zoom -= 0.05;
	else if (fract->zoom <= 2)
		fract->zoom -= 0.1;
	else if (fract->zoom <= 3)
		fract->zoom -= 0.2;
	else
		fract->zoom -= 1;
	printf("Changed zoom strength: %.2f\n", fract->zoom);
}

void	increase_zoom_strength(t_fract *fract)
{
	if (fract->zoom < 1.095)
		fract->zoom += 0.01;
	else if (fract->zoom < 1.495)
		fract->zoom += 0.05;
	else if (fract->zoom < 1.995)
		fract->zoom += 0.1;
	else if (fract->zoom < 2.995)
		fract->zoom += 0.2;
	else
		fract->zoom += 1;
	printf("Changed zoom strength: %.2f\n", fract->zoom);
}
