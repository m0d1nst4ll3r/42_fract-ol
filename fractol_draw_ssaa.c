/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_draw_ssaa.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 20:16:06 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/18 21:39:05 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//	Used to choose between all the escape time functions
//		depending on fractal type
float	escape_time_choose(t_complex variable, t_complex constant,
		int depth, char type)
{
	if (type == 'm')
		return (escape_time(constant, variable, depth));
/*	else if (type == '3')
		return (escape_time_m3(constant, variable, depth));
	else if (type == '4')
		return (escape_time_m4(constant, variable, depth));
	else if (type == '5')
		return (escape_time_m5(constant, variable, depth));*/
	else if (type == 'j')
		return (escape_time(variable, constant, depth));
	return (0);
}

static int	get_num_samples(void)
{
	int	i;
	int	total;

	i = 1;
	total = 0;
	while (i <= SSAA_LAYERS)
	{
		total += 4 * i;
		i++;
	}
	return (total + 1);
}

/* --------------------------------------------------------------------- *\
|		escape_time_ssaa
|
|	SSAA (Super Sampling Anti Aliasing) is a method where instead of
|		taking the result of a single pixel's calculations, you take
|		the results of a cloud of pixels around it and average all of
|		them out.
|
|	This cloud of pixels is not actual pixels around it but virtual
|		ones, in-between pixels, as if the resolution was higher than
|		it currently is.
|
|	The benefit of doing this is smoothing out sharp changes in pixel
|		colors that result in jagged and/or generally ugly graphics
|		in games and other graphical programs.
|
|	As it happens, fractol is sometimes quite ugly, and has sharply-
|		changing colors when iteration counts change really fast. SSAA
|		provides a way to smooth this out.
|
|	This function simply does the same as regular functions, but takes
|		several samples per point and averages their results. It does
|		so in a diamond shape around the point, in a certain number of
|		layers (defined by SSAA_LAYERS), around a certain distance
|		from the point (defined by SSAA_DIV).
|
|	1 layer will cause 5 samples per pixel, 2 will cause 13, 3 is 25,
|		4 is 41, 5 is 61, 6 is 85...
|
|	Since X samples multiply rendering time by X, 1 or 2 layers should
|		be the limit for usability, but more than that can be used to
|		create super-smooth images, although at the cost of minutes of
|		rendering time.
\* --------------------------------------------------------------------- */
static float	escape_time_ssaa(t_fract fract,
		long double x, long double y, float iter)
{
	int			layer;
	int			i;
	float		total;
	float		distance;
	t_complex	point;

	point.x = x;
	point.y = y;
	distance = fract.step / SSAA_DIV;
	layer = 0;
	total = iter;
	while (++layer <= SSAA_LAYERS)
	{
		point.y += distance;
		i = 0;
		while (i < layer)
		{
			total += escape_time_choose(point, fract.constant,
					fract.highest_iter, fract.type);
			point.y -= distance;
			point.x += distance;
			i++;
		}
		i = 0;
		while (i < layer)
		{
			total += escape_time_choose(point, fract.constant,
					fract.highest_iter, fract.type);
			point.y -= distance;
			point.x -= distance;
			i++;
		}
		i = 0;
		while (i < layer)
		{
			total += escape_time_choose(point, fract.constant,
					fract.highest_iter, fract.type);
			point.y += distance;
			point.x -= distance;
			i++;
		}
		i = 0;
		while (i < layer)
		{
			total += escape_time_choose(point, fract.constant,
					fract.highest_iter, fract.type);
			point.y += distance;
			point.x += distance;
			i++;
		}
	}
	return (total / get_num_samples());
}

void	*calculate_map_ssaa(void *arg)
{
	int			x;
	int			y;
	int			thread;
	t_fract		*data;

	data = (t_fract *)arg;
	pthread_mutex_lock(&(data->mutex));
	data->thread++;
	thread = data->thread;
	pthread_mutex_unlock(&(data->mutex));
	y = thread;
	while (y < data->winy)
	{
		x = -1;
		while (++x < data->winx)
		{
			if (data->map[y][x] >= data->highest_iter)
				data->map[y][x] = escape_time_ssaa(*data,
						data->pos.x + data->step * x,
						data->pos.y - data->step * y, data->map[y][x]);
		}
		y += NUMTHREADS;
	}
	pthread_exit(EXIT_SUCCESS);
}
