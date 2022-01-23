/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_draw3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 21:08:32 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/23 01:37:18 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//	Recaculates map partially according to an offset value
//	This is done after shifting the map, to optimize moving the view
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

/* --------------------------------------------------------------------- *\
|		thread_task
|
|	Executes a job in multiple threads, with the help of pthread.
|
|	Each instance of the job will auto-assign an id, using mutex locking,
|		so that they do so in an orderly and structured manner.
|
|	The id is initialized at -1 and the first thread increments it directly
|		to 0.
|
|	This id is then used to decide where to start each instance's loop, and
|		the number of threads is used to decide by how much to increment
|		the index.
|
|	The threads are then automatically handled by the cpu, and distributed
|		in an optimized manner to the available cores.
|
|	NUMTHREADS should be set at least to the amount of available cores to
|		see the best results. Too high a number causes slowdowns, but
|		anything below 100 typically does not see enough diminishing returns
|		to make a difference.
\* --------------------------------------------------------------------- */
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
