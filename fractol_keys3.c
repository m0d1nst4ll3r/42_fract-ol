/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_keys3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 17:07:24 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/18 03:58:14 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
	if (fract->autoiter && fract->step <= 0.00364)
		fract->max_iter = (int)(-400 * logl(fract->step) - 2196);
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
	if (fract->autoiter && fract->step <= 0.00364)
		fract->max_iter = (int)(-400 * logl(fract->step) - 2196);
	else if (fract->autoiter)
		fract->max_iter = 50;
	render_fractal(fract, 0);
}

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
