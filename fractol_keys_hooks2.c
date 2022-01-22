/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_keys_hooks2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 11:41:12 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/22 11:59:14 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	pointer_motion_hook(int x, int y, t_fract *fract)
{
	if (fract->type == 'j' && fract->shiftmode)
	{
		fract->constant.x = fract->pos.x + x * fract->step;
		fract->constant.y = fract->pos.y - y * fract->step;
		render_fractal(fract, 0);
	}
	return (0);
}
