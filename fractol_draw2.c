/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_draw2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 19:42:44 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/12 21:20:13 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	offset_map_d(t_fract data, int n)
{
	int	x;
	int	y;

	y = 0;
	while (y < data.winy - n)
	{
		x = 0;
		while (x < data.winx)
		{
			data.map[y][x] = data.map[y + n][x];
			x++;
		}
		y++;
	}
}

static void	offset_map_u(t_fract data, int n)
{
	int	x;
	int	y;

	y = data.winy - 1;
	while (y >= n)
	{
		x = 0;
		while (x < data.winx)
		{
			data.map[y][x] = data.map[y - n][x];
			x++;
		}
		y--;
	}
}

static void	offset_map_r(t_fract data, int n)
{
	int	x;
	int	y;

	x = 0;
	while (x < data.winx - n)
	{
		y = 0;
		while (y < data.winy)
		{
			data.map[y][x] = data.map[y][x + n];
			y++;
		}
		x++;
	}
}

static void	offset_map_l(t_fract data, int n)
{
	int	x;
	int	y;

	x = data.winx - 1;
	while (x >= n)
	{
		y = 0;
		while (y < data.winy)
		{
			data.map[y][x] = data.map[y][x - n];
			y++;
		}
		x--;
	}
}

void	calculate_map_partial(t_fract data, char direction, int n)
{
	if (direction == 'u')
	{
		offset_map_u(data, n);
		fill_map_u(data, n);
	}
	else if (direction == 'd')
	{
		offset_map_d(data, n);
		fill_map_d(data, n);
	}
	else if (direction == 'r')
	{
		offset_map_r(data, n);
		fill_map_r(data, n);
	}
	else
	{
		offset_map_l(data, n);
		fill_map_l(data, n);
	}
}
