/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 16:10:37 by rpohlen           #+#    #+#             */
/*   Updated: 2022/06/13 10:45:46 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//	Free the 2D int map up to len (typically winy but
//		possibly less in case of failed malloc)
void	free_map(float **map, int len)
{
	while (map && len--)
		free(map[len]);
	if (map)
		free(map);
}

//	Exit program cleanly, freeing the map, the colors list,
//		destroying the two images, the window, and the mlx
//		instance.
void	exit_program(t_fract fract)
{
	free_map(fract.map, fract.winy);
	fractol_lstclear(fract.colors);
	if (fract.img_main.img)
		mlx_destroy_image(fract.mlx, fract.img_main.img);
	if (fract.img_temp.img)
		mlx_destroy_image(fract.mlx, fract.img_temp.img);
	if (fract.win)
		mlx_destroy_window(fract.mlx, fract.win);
	if (fract.mlx)
	{
		mlx_destroy_display(fract.mlx);
		free(fract.mlx);
	}
	exit(0);
}
