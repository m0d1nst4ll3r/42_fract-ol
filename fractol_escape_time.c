/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_escape_time.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 13:59:29 by rpohlen           #+#    #+#             */
/*   Updated: 2022/06/12 14:50:40 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* --------------------------------------------------------------------- *\
|		escape_time
|
|	Takes in a complex number [c] and a complex number [s]
|
|	[s] is our starting value, [c] is the constant we're adding
|
|	Iterates at maximum [depth] times, squaring the result of the last
|		iteration ([s] if first) and adding [c] to it
|
|	When the resulting complex number is farther than a certain radius from
|		the center of our complex numbers graph (0, 0), stop iterating
|	(this is calculated with pythagore's theorem)
|
|	The number of iterations we've reached is then returned to be used
|		for coloring
|
|	x2 and y2 are used to save on the number of multiplications
|	long doubles are used to reach the highest precision possible (e-22)
|
|	For the Mandelbrot set, s will always be 0, 0 and c will vary based
|		on the area of the set and the pixel transformations
|	For any Julia set, c will always be a set value and s will vary based
|		on the area of the set and the pixel transformations
|
|	The iteration value is returned as a float and not an int - it accounts
|		for differences in the escaped value to allow smooth coloring.
|	When the result from an iteration escapes (we set the limit to 2^8), it
|		does not always escape the same distance. The closer it is to 2^8,
|		the closer it would've been to have taken another iteration to
|		escape. The closer it is from 2^16, the closer it would've been to
|		have not needed this iteration at all.
|	Hence, the value that escaped is transformed into a ratio between 0 and
|		1 with logarithms to produce a partial iteration value.
|	Don't ask me what that log formula does exactly though... I still don 't
|		get it.
\* --------------------------------------------------------------------- */
static float	escape_time(t_complex s, t_complex c, int depth)
{
	long double	x2;
	long double	y2;
	int			iter;

	x2 = s.x * s.x;
	y2 = s.y * s.y;
	iter = 0;
	while (x2 + y2 <= (1 << 16) && iter < depth)
	{
		s.y = c.y + 2 * s.x * s.y;
		s.x = c.x + x2 - y2;
		x2 = s.x * s.x;
		y2 = s.y * s.y;
		iter++;
	}
	if (iter < depth)
		return ((float)iter + 1
			- logf((logf((float)x2 + (float)y2) / 2) / logf(2)) / logf(2));
	return ((float)iter);
}

//	mandelbrot power 3
static float	escape_time_m3(t_complex s, t_complex c, int depth)
{
	long double	x2;
	long double	y2;
	int			iter;

	x2 = s.x * s.x;
	y2 = s.y * s.y;
	iter = 0;
	while (x2 + y2 <= (1 << 16) && iter < depth)
	{
		s.y = c.y - y2 * s.y + 3 * x2 * s.y;
		s.x = c.x + x2 * s.x - 3 * y2 * s.x;
		x2 = s.x * s.x;
		y2 = s.y * s.y;
		iter++;
	}
	if (iter < depth)
		return ((float)iter + 1
			- logf((logf((float)x2 + (float)y2) / 2) / logf(3)) / logf(3));
	return ((float)iter);
}

//	mandelbrot power 4
static float	escape_time_m4(t_complex s, t_complex c, int depth)
{
	long double	x2;
	long double	y2;
	int			iter;

	x2 = s.x * s.x;
	y2 = s.y * s.y;
	iter = 0;
	while (x2 + y2 <= (1 << 16) && iter < depth)
	{
		s.y = c.y + 4 * x2 * s.x * s.y - 4 * y2 * s.y * s.x;
		s.x = c.x + x2 * x2 + y2 * y2 - 6 * x2 * y2;
		x2 = s.x * s.x;
		y2 = s.y * s.y;
		iter++;
	}
	if (iter < depth)
		return ((float)iter + 1
			- logf((logf((float)x2 + (float)y2) / 2) / logf(4)) / logf(4));
	return ((float)iter);
}

//	mandelbrot power 5
static float	escape_time_m5(t_complex s, t_complex c, int depth)
{
	long double	x2;
	long double	y2;
	int			iter;

	x2 = s.x * s.x;
	y2 = s.y * s.y;
	iter = 0;
	while (x2 + y2 <= (1 << 16) && iter < depth)
	{
		s.y = c.y + y2 * y2 * s.y + 5 * x2 * x2 * s.y - 10 * y2 * s.y * x2;
		s.x = c.x + x2 * x2 * s.x + 5 * y2 * y2 * s.x - 10 * x2 * s.x * y2;
		x2 = s.x * s.x;
		y2 = s.y * s.y;
		iter++;
	}
	if (iter < depth)
		return ((float)iter + 1
			- logf((logf((float)x2 + (float)y2) / 2) / logf(5)) / logf(5));
	return ((float)iter);
}

/* --------------------------------------------------------------------- *\
|		escape_time_global
|
|	Chooses which escape time to use depending on fractal type.
|
|	Types:
|		m		mandelbrot		Zn² + C		starts at 0
|		3		mandel cube		Zn³ + C				  0
|		4		mandel 4		Zn⁴ + C				  0
|		5		mandel 5		Zn⁵ + C				  0
|		j		julia			Zn² + C		starts at (variable)
\* --------------------------------------------------------------------- */
float	escape_time_global(t_complex variable, t_complex constant,
		int depth, char type)
{
	if (type == 'm')
		return (escape_time(constant, variable, depth));
	if (type == '3')
		return (escape_time_m3(constant, variable, depth));
	if (type == '4')
		return (escape_time_m4(constant, variable, depth));
	if (type == '5')
		return (escape_time_m5(constant, variable, depth));
	else if (type == 'j')
		return (escape_time(variable, constant, depth));
	return (0);
}
