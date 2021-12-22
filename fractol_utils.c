/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 10:11:46 by rpohlen           #+#    #+#             */
/*   Updated: 2021/12/22 13:35:37 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* --------------------------------------------------------------------- *\
|		pendulum
|	
|	For an array of length len, returns a cycling value from start to
|		end, then end to start.
|
|	Examples :
|	for val equal to
|	0 1 2 3 4 5 6 7 8 9 10
|	- if len = 4
|	0 1 2 3 3 2 1 0 0 1 2
|	- if len = 2
|	0 1 1 0 0 1 1 0 0 1 1
|
|	This is used in fractol for cycling through color palettes.
\* --------------------------------------------------------------------- */
int	pendulum(int len, int val)
{
	int	mod;

	mod = val % ((len + 1) * 2);
	if (mod > len)
		return (len * 2 - mod + 1);
	else
		return (mod);
}

//	Prints out values useful for debugging
void	print_info(t_fract data)
{
	printf("=-._.-=Fractal Information=-._.-=\n");
	printf("- Current pos : %Le, %Le\n", data.posx, data.posy);
	printf("- Current step : %Le\n", data.step);
	printf("- Current depth : %d\n", data.depth);
}
