/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 03:11:23 by rpohlen           #+#    #+#             */
/*   Updated: 2022/06/12 16:41:39 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int ac, char **av)
{
	t_fract	fract;

	if (fractol_init(&fract, ac, av))
		exit_program(fract);
	render_fractal(&fract, 0);
	mlx_hook(fract.win, 2, 1L << 0, key_hook, &fract);
	mlx_hook(fract.win, 4, 1L << 2, mouse_hook, &fract);
	mlx_hook(fract.win, 6, 1L << 6, pointer_motion_hook, &fract);
	mlx_hook(fract.win, 33, 1, clientmsg_hook, &fract);
	mlx_loop(fract.mlx);
	return (0);
}
