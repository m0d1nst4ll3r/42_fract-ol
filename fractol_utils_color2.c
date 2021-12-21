/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_utils_graph2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 14:56:20 by rpohlen           #+#    #+#             */
/*   Updated: 2021/12/21 15:08:24 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//	Returns a value between color1 and color2
//	ratio should be between 0 and 1
int	get_gradient(int color1, int color2, float ratio)
{
	int	r;
	int	g;
	int	b;

	r = (get_r(color2) - get_r(color1)) * ratio + get_r(color1);
	g = (get_g(color2) - get_g(color1)) * ratio + get_g(color1);
	b = (get_b(color2) - get_b(color1)) * ratio + get_b(color1);
	return (r << 16 | g << 8 | b);
}
