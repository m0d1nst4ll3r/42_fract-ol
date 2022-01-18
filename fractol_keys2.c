/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_keys2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 17:05:40 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/18 16:23:18 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//	Simply change colors with lst functions (see those)
//	At the end or beginning of the list, we loop back
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

/* --------------------------------------------------------------------- *\
|		more_iter less_iter
|
|	Changing iterations is optimized to save on calculations.
|
|	When the value is decreased, nothing is recalculated, we only redraw
|		according to the new value, while remembering the old one.
|
|	When the value is increased, we check against the old one (the
|		highest one we've reached thus far) and only recalculate if
|		the new one is higher. In that case, we don't even recalculate
|		everything : we only recalculate pixels that are black (others
|		are guaranteed not to ever change when max_iter rises).
\* --------------------------------------------------------------------- */
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

/* --------------------------------------------------------------------- *\
|		enable_autoiter
|
|	To automatically increase iterations, we use an
|
|		inverted normalized logarithmic equation
|
|	logarithmic		we use a log
|	inverted		we multiply it by -1
|	normalized		we add a certain value (in this case, subtract)
|
|	Auto-increasing iterations mean we increase max_iter as step decreases.
|	But it needs to rise linearly, not on a normal scale, but on a log
|		scale. Meaning at e-3 we have 200, at e-22 we have 20 000, and
|		in-between at e-11, we have 10 000.
|	If it rised linearly on a normal scale, since e-22 is so small,
|		e-6 to e-22 would roughly have the same value (close to 20 000).
|	Rising linearly on a log scale means dividing step by 10 makes
|		max_iter rise by the same amount every time.
|
|	log(x) does exactly this, but it rises when x rises.
|	-log(x) is inverted : it rises when x decreases.
|	a * -log(x) makes it rise much faster, so we can reach ~20 000 by e-22
|	a * -log(x) + b allows us to finetune the starting value at e-3
|	When a is 400 and b is - 2196, the function returns 200 at 0.0025
|		and rises to ~20 000 at e-22
|
|	AI_A is a, AI_B is b, AI_T is the threshold at which the step value
|		is too big and the function starts going negative (we limit it
|		at an arbitrary number of 50).
\* --------------------------------------------------------------------- */
void	enable_autoiter(t_fract *fract)
{
	fract->autoiter = 1;
	if (fract->step <= AI_T)
		fract->max_iter = (int)(-AI_A * logl(fract->step) - AI_B);
	else
		fract->max_iter = 50;
	if (fract->max_iter > fract->highest_iter)
		render_fractal(fract, RENDER_REITER);
	else
		render_fractal(fract, RENDER_RECOLOR);
}
