/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_draw3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 21:08:32 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/12 21:27:38 by rpohlen          ###   ########.fr       */
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
			if (data.type == 'm')
				data.map[y][x] = escape_time(data.constant, variable,
						data.max_iter);
			else
				data.map[y][x] = escape_time(variable, data.constant,
						data.max_iter);
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
			if (data.type == 'm')
				data.map[y][x] = escape_time(data.constant, variable,
						data.max_iter);
			else
				data.map[y][x] = escape_time(variable, data.constant,
						data.max_iter);
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
			if (data.type == 'm')
				data.map[y][x] = escape_time(data.constant, variable,
						data.max_iter);
			else
				data.map[y][x] = escape_time(variable, data.constant,
						data.max_iter);
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
			if (data.type == 'm')
				data.map[y][x] = escape_time(data.constant, variable,
						data.max_iter);
			else
				data.map[y][x] = escape_time(variable, data.constant,
						data.max_iter);
			variable.y -= data.step;
			y++;
		}
		variable.x += data.step;
		x++;
	}
}
