/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_escape_time.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 13:59:29 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/19 14:13:32 by rpohlen          ###   ########.fr       */
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
|	When the resulting complex number is farther than a radius of 2 from
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
\* --------------------------------------------------------------------- */
float	escape_time(t_complex s, t_complex c, int depth)
{
	long double	x2;
	long double	y2;
	int			iter;

	x2 = s.x * s.x;
	y2 = s.y * s.y;
	iter = 0;
	while (x2 + y2 <= (1 << 16) && iter < depth)
	{
		s.y = c.y + (s.x + s.x) * s.y;
		s.x = c.x + x2 - y2;
		x2 = s.x * s.x;
		y2 = s.y * s.y;
		iter++;
	}
	if (iter < depth)
		return ((float)iter + 1
			- logf((logf((float)x2 + (float)y2) / 2) / logf(2.0)) / logf(2.0));
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
|		j		julia			Zn² + C		starts at X
|		b		burning ship	something	starts at 0
\* --------------------------------------------------------------------- */
float	escape_time_global(t_complex variable, t_complex constant,
		int depth, char type)
{
	if (type == 'm')
		return (escape_time(constant, variable, depth));
	else if (type == 'j')
		return (escape_time(variable, constant, depth));
	return (0);
}
