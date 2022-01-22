/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_keys4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:24:50 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/22 11:37:37 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//	Activates or deactivates color banding
void	toggle_smooth_colors(t_fract *fract)
{
	fract->smoothcol = ! fract->smoothcol;
	render_fractal(fract, RENDER_RECOLOR);
}

void	apply_ssaa_filter(t_fract *fract)
{
	t_img	tmp;

	thread_task(fract, 's');
	tmp = fract->img_main;
	fract->img_main = fract->img_temp;
	fract->img_temp = tmp;
	mlx_put_image_to_window(fract->mlx, fract->win, fract->img_main.img, 0, 0);
}

void	decrease_ssaa_strength(t_fract *fract)
{
	if (fract->ssaa_samples > 2)
	{
		fract->ssaa_samples--;
		printf("\e[0;32mSSAA Strength:\e[0m %d\n", fract->ssaa_samples);
	}
}

void	increase_ssaa_strength(t_fract *fract)
{
	fract->ssaa_samples++;
	printf("\e[0;32mSSAA Strength:\e[0m %d\n", fract->ssaa_samples);
}

void	toggle_shift_mode(t_fract *fract)
{
	fract->shiftmode = !fract->shiftmode;
}
