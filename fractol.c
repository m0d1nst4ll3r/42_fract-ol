/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 03:11:23 by rpohlen           #+#    #+#             */
/*   Updated: 2021/12/18 01:01:35 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	pixel_put(t_fract data, int x, int y, int color)
{
	char	*dst;

	dst = data.addr + (y * data.llen + x * data.bpp / 8);
	*(int *)dst = color;
}

int	escape_time(long double cx, long double cy, int depth)
{
	long double	x;
	long double	y;
	long double	x2;
	long double	y2;
	int		iter;

	x2 = 0;
	y2 = 0;
	x = 0;
	y = 0;
	iter = 0;
	while (iter < depth)
	{
		y = cy + (x + x) * y;
		x = cx + x2 - y2;
		x2 = x * x;
		y2 = y * y;
		if (x2 + y2 > 4)
			break;
		iter++;
	}
	if (depth == iter)
		return (0);
	return (0xFFFF00 + 0xFF - (int)(((float)depth - (float)iter) / (float)depth * 0xFF));
	//return (0xffffff);
}

void	draw(t_fract data)
{
	for (int y = 0; y < WIN_Y; y++)
		for (int x = 0; x < WIN_X; x++)
			pixel_put(data, x, y, escape_time(data.posx + x * data.step, data.posy - y * data.step, data.depth));
}

int	key_hook(int key, t_fract *data)
{
	if (key == 61 || (key == 45 && data->depth > 1) || (key >= 65361 && key <= 65364))
	{
		if (key == 61)
			data->depth++;
		else if (key == 45)
			data->depth--;
		else if (key == 65362)
			data->posy += 5 * data->step;
		else if (key == 65361)
			data->posx -= 5 * data->step;
		else if (key == 65364)
			data->posy -= 5 * data->step;
		else if (key == 65363)
			data->posx += 5 * data->step;
		draw(*data);
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	}
	return (0);
}

int	mouse_hook(int key, int x, int y, t_fract *data)
{
	if (key == 4 || key == 5)
	{
		if (key == 4)
		{
			data->posx += x * data->step - x * data->step / ZOOM;
			data->posy -= y * data->step - y * data->step / ZOOM;
			data->step = data->step / ZOOM;
		}
		else if (key == 5)
		{
			data->posx -= x * data->step - x * data->step / ZOOM;
			data->posy += y * data->step - y * data->step / ZOOM;
			data->step = data->step * ZOOM;
		}
		draw(*data);
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	}
	return (0);
}

//void	mouse_pos(int key)

int	main(void)
{
	t_fract	data;

	data.depth = 1;
	if (DEPTH > 0)
		data.depth = DEPTH;
	data.step = STEP;
	data.posx = - WIN_X / 2 * STEP;
	data.posy = WIN_Y / 2 * STEP;

	data.mlx = mlx_init();
	data.img = mlx_new_image(data.mlx, WIN_X, WIN_Y);
	data.addr = mlx_get_data_addr(data.img, &data.bpp, &data.llen, &data.end);
	data.win = mlx_new_window(data.mlx, WIN_X, WIN_Y, "test");

	draw(data);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);

	printf("mlx %p, win %p\n", data.mlx, data.win);
	printf("data %p\n", &data);
	mlx_hook(data.win, 2, 1L<<0, key_hook, &data);
	mlx_hook(data.win, 4, 1L<<2, mouse_hook, &data);
	//	mlx_mouse_hook(data.win, mouse_hook, &data);
	//	mlx_hook(data.win, 2, 1L<<0, mouse_hook, &data);
	//	mlx_hook(data.win, 7, 1L<<7, mouse_hook, &data);
	mlx_loop(data.mlx);
	return (0);
}
