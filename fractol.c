/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 03:11:23 by rpohlen           #+#    #+#             */
/*   Updated: 2021/12/23 19:25:05 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int ac, char **av)
{
	t_fract	data;

	(void)ac;
	(void)av;
	data.colors = decode_colors(COLORS_FILE);
	data.palette_size = data.colors->palette_size;
	data.palette = data.colors->palette;
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
