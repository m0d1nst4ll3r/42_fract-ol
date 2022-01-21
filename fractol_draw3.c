/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_draw3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 21:08:32 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/20 19:30:37 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	fill_map_d(t_fract data, int n)
{
	int			x;
	int			y;
	t_complex	variable;

	variable.y = data.pos.y - data.step * (data.winy - 1);
	y = data.winy - 1;
	while (y >= data.winy - n)
	{
		variable.x = data.pos.x;
		x = 0;
		while (x < data.winx)
		{
			data.map[y][x] = escape_time_global(variable, data.constant,
					data.max_iter, data.type);
			variable.x += data.step;
			x++;
		}
		variable.y += data.step;
		y--;
	}
}

void	fill_map_u(t_fract data, int n)
{
	int			x;
	int			y;
	t_complex	variable;

	variable.y = data.pos.y;
	y = 0;
	while (y < n)
	{
		variable.x = data.pos.x;
		x = 0;
		while (x < data.winx)
		{
			data.map[y][x] = escape_time_global(variable, data.constant,
					data.max_iter, data.type);
			variable.x += data.step;
			x++;
		}
		variable.y -= data.step;
		y++;
	}
}

void	fill_map_r(t_fract data, int n)
{
	int			x;
	int			y;
	t_complex	variable;

	variable.x = data.pos.x + data.step * (data.winx - 1);
	x = data.winx - 1;
	while (x >= data.winx - n)
	{
		variable.y = data.pos.y;
		y = 0;
		while (y < data.winy)
		{
			data.map[y][x] = escape_time_global(variable, data.constant,
					data.max_iter, data.type);
			variable.y -= data.step;
			y++;
		}
		variable.x -= data.step;
		x--;
	}
}

void	fill_map_l(t_fract data, int n)
{
	int			x;
	int			y;
	t_complex	variable;

	variable.x = data.pos.x;
	x = 0;
	while (x < n)
	{
		variable.y = data.pos.y;
		y = 0;
		while (y < data.winy)
		{
			data.map[y][x] = escape_time_global(variable, data.constant,
					data.max_iter, data.type);
			variable.y -= data.step;
			y++;
		}
		variable.x += data.step;
		x++;
	}
}

void	thread_task(t_fract *data, char task)
{
	int			err;
	int			i;
	pthread_t	threads[NUMTHREADS];

	if (pthread_mutex_init(&(data->mutex), NULL))
		return ;
	data->thread = -1;
	i = -1;
	while (++i < NUMTHREADS)
	{
		if (task == 'c')
			err = pthread_create(threads + i, NULL, &calculate_map, data);
		else if (task == 'd')
			err = pthread_create(threads + i, NULL, &draw_fractal, data);
		else if (task == 's')
			err = pthread_create(threads + i, NULL, &render_ssaa, data);
		if (err)
			return ;
	}
	i = -1;
	while (++i < NUMTHREADS)
		pthread_join(threads[i], NULL);
	pthread_mutex_destroy(&data->mutex);
}
