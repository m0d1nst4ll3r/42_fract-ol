/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 03:11:23 by rpohlen           #+#    #+#             */
/*   Updated: 2021/12/21 14:26:57 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	*palette_fire(int size)
{
	int	*palette;
	int	step;
	int	r;
	int	g;
	int	b;

	palette = malloc(size * sizeof(int));
	r = 0;
	g = 0;
	b = 0;
	for (int i = 0; i < size; i++)
	{
		step = 255 * 3 / size;
		while (step > 0)
		{
			if (r < 255)
				r++;
			else if (g < 255)
				g++;
			else
				b++;
			step--;
		}
		palette[i] = get_rgb(r, g, b);
	}
	return (palette);
}

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
		iter++;
		if (x2 + y2 > 4)
			break;
	}
	return (iter);
}

void	draw(t_fract data)
{
	int		color;
	int		iter;

	for (int y = 0; y < WIN_Y; y++)
	{
		for (int x = 0; x < WIN_X; x++)
		{
			iter = escape_time(data.posx + x * data.step, data.posy - y * data.step, data.depth);
			if (iter == data.depth)
				color = 0;
			else
				color = data.palette[pendulum(data.palette_size - 1, iter)];
			pixel_put(data, x, y, color);
		}
	}
}

int	key_hook(int key, t_fract *data)
{
	if (key == 61 || key == 45 || (key >= 65361 && key <= 65364))
	{
		if (key == 61)
			data->depth += DEPTH_MOD;
		else if (key == 45 && data->depth <= DEPTH_MOD)
			data->depth = 1;
		else if (key == 45)
			data->depth -= DEPTH_MOD;
		else if (key == 65362)
			data->posy += MOVE_MOD * data->step;
		else if (key == 65361)
			data->posx -= MOVE_MOD * data->step;
		else if (key == 65364)
			data->posy -= MOVE_MOD * data->step;
		else if (key == 65363)
			data->posx += MOVE_MOD * data->step;
		draw(*data);
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	}
	else if (key == 104)
		print_info(*data);
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

int	main(void)
{
	t_fract	data;

	data.palette_size = 25;
	data.palette = palette_fire(data.palette_size);
	data.depth = 1;
	if (DEPTH > 0)
		data.depth = DEPTH;
	data.step = STEP;
	data.posx = - WIN_X / 2 * STEP;
	data.posy = WIN_Y / 2 * STEP;

	data.mlx = mlx_init();
	data.img = mlx_new_image(data.mlx, WIN_X, WIN_Y);
	data.addr = mlx_get_data_addr(data.img, &data.bpp, &data.llen, &data.end);
	data.win = mlx_new_window(data.mlx, WIN_X, WIN_Y, "=-._.-=fract-ol=-._.-=");

	draw(data);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);

	mlx_hook(data.win, 2, 1L<<0, key_hook, &data);
	mlx_hook(data.win, 4, 1L<<2, mouse_hook, &data);
	mlx_loop(data.mlx);
	return (0);
}
