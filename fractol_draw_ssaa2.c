/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_draw_ssaa2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 12:20:31 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/22 12:20:44 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	*render_ssaa(void *arg)
{
	int			x;
	int			y;
	int			thread;
	t_fract		*data;
	t_complex	point;

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
			point.x = data->pos.x + data->step * x;
			point.y = data->pos.y - data->step * y;
			pixel_put(data->img_temp, x, y,
				draw_ssaa(*data, point, data->map[y][x]));
		}
		y += NUMTHREADS;
	}
	pthread_exit(EXIT_SUCCESS);
}
