/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 03:11:23 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/07 23:50:30 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_color	*rand_color(t_color *list)
{}

void	choose_color(t_fract *data, char *color)
{}

void	copy_params(t_params params, t_fract *firstwin)
{
	firstwin-> = ;
	firstwin-> = ;
	firstwin-> = ;
	firstwin-> = ;
	firstwin-> = ;
	firstwin-> = ;
	firstwin-> = ;
	firstwin-> = ;
	firstwin-> = ;
	firstwin-> = ;
	firstwin-> = ;
}

int	fractol_init(t_fract *firstwin, int ac, char **av)
{
	t_params	params;

	if (fill_params(&params, ac, av))
		return (1);
	copy_params(params, firstwin);
	firstwin->mlx = ;
	firstwin->win = ;
	firstwin->img_main = ;
	firstwin->img_temp = ;
	firstwin->colors = ;
	if (!firstwin->colors);
		//build default color
	choose_color(firstwin, params.color);
	firstwin->pos = ; //(depends on win)
	firstwin->step = ; //depends on win
	//rest (type, constant, max iter, zoom, autoiter) filled by params
}

int	main(int ac, char **av)
{
	t_fract	firstwin;

	if (fractol_init(&firstwin, ac, av))
		return (1);
	data.colors = decode_colors(COLORS_FILE);
	data.palette_size = data.colors->palette_size;
	data.palette = data.colors->palette;
	data.max_iter = 1;
	if (DEPTH > 0)
		data.max_iter = DEPTH;
	data.step = STEP;
	data.pos.x = - WIN_X / 2 * STEP;
	data.pos.y = WIN_Y / 2 * STEP;

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
