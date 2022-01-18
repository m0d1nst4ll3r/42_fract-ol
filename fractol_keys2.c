/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_keys2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 17:05:40 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/18 03:57:24 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	next_color(t_fract *fract)
{
	fract->curcol = fractol_lstnext(fract->colors, fract->curcol);
	printf("Switching to color %s\n", fract->curcol->name);
	render_fractal(fract, RENDER_RECOLOR);
}

void	prev_color(t_fract *fract)
{
	fract->curcol = fractol_lstprev(fract->colors, fract->curcol);
	printf("Switching to color %s\n", fract->curcol->name);
	render_fractal(fract, RENDER_RECOLOR);
}

void	more_iter(t_fract *fract, int n)
{
	fract->autoiter = 0;
	fract->max_iter += n;
	if (fract->max_iter > fract->highest_iter)
		render_fractal(fract, RENDER_REITER);
	else
		render_fractal(fract, RENDER_RECOLOR);
}

void	less_iter(t_fract *fract, int n)
{
	fract->autoiter = 0;
	if (fract->max_iter - n < 1)
		fract->max_iter = 1;
	else
		fract->max_iter -= n;
	render_fractal(fract, RENDER_RECOLOR);
}

void	enable_autoiter(t_fract *fract)
{
	fract->autoiter = 1;
	if (fract->step <= 0.00364)
		fract->max_iter = (int)(-400 * logl(fract->step) - 2196);
	else
		fract->max_iter = 50;
	if (fract->max_iter > fract->highest_iter)
		render_fractal(fract, RENDER_REITER);
	else
		render_fractal(fract, RENDER_RECOLOR);
}
