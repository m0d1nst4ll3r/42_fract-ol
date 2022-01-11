/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 03:11:23 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/11 17:31:43 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int ac, char **av)
{
	t_fract	fract;

	if (fractol_init(&fract, ac, av))
		return (1);
	render_fractal(fract);
	mlx_put_image_to_window(fract.mlx, fract.win, fract.img_temp.img, 0, 0);

	mlx_hook(fract.win, 2, 1L << 0, key_hook, &fract);
	mlx_hook(fract.win, 4, 1L << 2, mouse_hook, &fract);
	mlx_loop(fract.mlx);
	return (0);
}
