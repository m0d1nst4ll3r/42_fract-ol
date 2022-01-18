/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_keys4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:24:50 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/18 21:36:00 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//	Activates or deactivates color banding
void	toggle_smooth_colors(t_fract *fract)
{
	fract->smoothcol = ! fract->smoothcol;
	render_fractal(fract, RENDER_RECOLOR);
}

void	activate_ssaa(t_fract *fract)
{
	thread_task(fract, 's');
	render_fractal(fract, RENDER_RECOLOR);
}
