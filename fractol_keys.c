/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_keys.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:24:50 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/22 23:30:29 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//	Toggles color banding/smooth colors
//	Redraws image based on new setting
void	toggle_smooth_colors(t_fract *fract)
{
	fract->smoothcol = ! fract->smoothcol;
	render_fractal(fract, RENDER_RECOLOR);
}

//	Applies an SSAA filter on the current screen
//	Strength is set to 2 by default
void	apply_ssaa_filter(t_fract *fract)
{
	t_img	tmp;

	thread_task(fract, 's');
	tmp = fract->img_main;
	fract->img_main = fract->img_temp;
	fract->img_temp = tmp;
	mlx_put_image_to_window(fract->mlx, fract->win, fract->img_main.img, 0, 0);
}

//	Changes SSAA strength and prints a message
//	SSAA can't be less than 2
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

//	Toggles julia set shifting (see fractol_keys_hooks2.c)
void	toggle_shift_mode(t_fract *fract)
{
	fract->shiftmode = !fract->shiftmode;
}
