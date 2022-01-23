/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_draw_ssaa.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 13:07:56 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/23 01:46:33 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//	Adds r, g and b values from an rgb color to total r, g, b values
static void	addcol(int color, int *rgb)
{
	rgb[0] += get_r(color);
	rgb[1] += get_g(color);
	rgb[2] += get_b(color);
}

//	Averages all the colors and returns the combined rgb result
static int	getavg(int *rgb, int samples)
{
	rgb[0] /= samples;
	rgb[1] /= samples;
	rgb[2] /= samples;
	return (get_rgb(rgb[0], rgb[1], rgb[2]));
}

//	Gets color from a floating point iteration according to a palette
//	See fractol_draw.c for further explanation in similar function
static int	getcol(t_fract data, float iter)
{
	int	color;

	if ((int)iter >= data.max_iter)
		color = 0;
	else
		color = get_gradient(
				data.curcol->palette[(int)iter % data.curcol->palette_size],
				data.curcol->palette[
				((int)iter + 1) % data.curcol->palette_size],
				iter - (int)iter);
	return (color);
}

//	The first (and original) pixel's color can be directly used
//		without needing to run the escape_time function again
static void	initcol(t_fract data, float init, int *rgb)
{
	int	color;

	color = getcol(data, init);
	rgb[0] = get_r(color);
	rgb[1] = get_g(color);
	rgb[2] = get_b(color);
}

/* --------------------------------------------------------------------- *\
|		draw_ssaa
|
|	For a given complex point, calculate the escape time of a grid of
|		complex points around it, add their resulting colors together,
|		and average them out.
|
|	The grid is of size ssaa_samples x ssaa_samples. For a value of 2,
|		we will calculate 3 new points (the first one already having
|		been calculated beforehand). For a value of 10, 99 new points.
|
|	Since the grid needs to be located between the given complex point and
|		the next pixel's complex point (located one step ahead), we
|		divide step by the grid's size. For a grid of 2, our new step is
|		step / 2.
|
|	The bigger the grid, the longer the calculations, but the more accurate
|		the resulting colors.
|
|	This is essentially upscaling the resolution, and downscaling the
|		resulting image by color averages.
\* --------------------------------------------------------------------- */
int	draw_ssaa(t_fract data, t_complex point, float init)
{
	int			rgb[3];
	int			x;
	int			y;
	t_complex	spoint;
	float		sstep;

	initcol(data, init, rgb);
	sstep = data.step / data.ssaa_samples;
	spoint.y = point.y;
	y = 0;
	while (++y <= data.ssaa_samples)
	{
		spoint.x = point.x;
		x = 0;
		while (++x <= data.ssaa_samples)
		{
			if (y != 1 || x != 1)
				addcol(getcol(data,
						escape_time_global(spoint, data.constant,
							data.max_iter, data.type)), rgb);
			spoint.x += sstep;
		}
		spoint.y -= sstep;
	}
	return (getavg(rgb, data.ssaa_samples * data.ssaa_samples));
}
