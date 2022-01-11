/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_keys3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 17:07:24 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/11 17:27:59 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	zoom_in(t_fract *fract, int x, int y)
{
	printf("Zoom at %d\t%d\n", x, y);
	fract->pos.x += x * fract->step - x * fract->step / fract->zoom;
	fract->pos.y -= y * fract->step - y * fract->step / fract->zoom;
	fract->step = fract->step / fract->zoom;
}

void	zoom_out(t_fract *fract, int x, int y)
{
	printf("Zoom at %d\t%d\n", x, y);
	fract->pos.x -= x * fract->step - x * fract->step / fract->zoom;
	fract->pos.y += y * fract->step - y * fract->step / fract->zoom;
	fract->step = fract->step * fract->zoom;
}
