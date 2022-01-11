/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_keys2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 17:05:40 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/11 17:06:04 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	next_color(t_fract *fract)
{
	fract->curcol = fractol_lstnext(fract->colors, fract->curcol);
	draw_fractal(*fract);
}

void	prev_color(t_fract *fract)
{
	fract->curcol = fractol_lstprev(fract->colors, fract->curcol);
	draw_fractal(*fract);
}

void	more_iter(t_fract *fract, int n)
{
	fract->max_iter += n;
	render_fractal(*fract);
	fract->autoiter = 0;
}

void	less_iter(t_fract *fract, int n)
{
	if (fract->max_iter - n < 1)
		fract->max_iter = 1;
	else
		fract->max_iter -= n;
	render_fractal(*fract);
	fract->autoiter = 0;
}
