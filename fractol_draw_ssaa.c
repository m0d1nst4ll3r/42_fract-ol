/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_draw_ssaa.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 13:07:56 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/22 12:20:22 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	addcol(int color, int *rgb)
{
	rgb[0] += get_r(color);
	rgb[1] += get_g(color);
	rgb[2] += get_b(color);
}

static int	getavg(int *rgb, int samples)
{
	rgb[0] /= samples;
	rgb[1] /= samples;
	rgb[2] /= samples;
	if (rgb[0] > 0xff || rgb[1] > 0xff || rgb[2] > 0xff)
	{
		printf("Caution! Color overflow at ");
		printf("%d\t%d\t%d\n", rgb[0], rgb[1], rgb[2]);
	}
	return (get_rgb(rgb[0], rgb[1], rgb[2]));
}

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

static void	initcol(t_fract data, float init, int *rgb)
{
	int	color;

	color = getcol(data, init);
	rgb[0] = get_r(color);
	rgb[1] = get_g(color);
	rgb[2] = get_b(color);
}

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
