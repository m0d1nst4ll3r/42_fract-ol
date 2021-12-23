/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_keys.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 18:35:07 by rpohlen           #+#    #+#             */
/*   Updated: 2021/12/23 18:49:29 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	key_hook(int key, t_fract *data)
{
	if (key == 61 || key == 45 || (key >= 65361 && key <= 65364))
	{
		if (key == 61)
			data->max_iter += DEPTH_MOD;
		else if (key == 45 && data->max_iter <= DEPTH_MOD)
			data->max_iter = 1;
		else if (key == 45)
			data->max_iter -= DEPTH_MOD;
		else if (key == 65362)
			data->pos.y += MOVE_MOD * data->step;
		else if (key == 65361)
			data->pos.x -= MOVE_MOD * data->step;
		else if (key == 65364)
			data->pos.y -= MOVE_MOD * data->step;
		else if (key == 65363)
			data->pos.x += MOVE_MOD * data->step;
		draw_mandelbrot(*data);
		mlx_put_image_to_window(data->mlx, data->win, data->img_main.img, 0, 0);
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
			data->pos.x += x * data->step - x * data->step / ZOOM;
			data->pos.y -= y * data->step - y * data->step / ZOOM;
			data->step = data->step / ZOOM;
		}
		else if (key == 5)
		{
			data->pos.x -= x * data->step - x * data->step / ZOOM;
			data->pos.y += y * data->step - y * data->step / ZOOM;
			data->step = data->step * ZOOM;
		}
		draw_mandelbrot(*data);
		mlx_put_image_to_window(data->mlx, data->win, data->img_main.img, 0, 0);
	}
	return (0);
}
