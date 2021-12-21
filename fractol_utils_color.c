/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_utils_color.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 10:22:40 by rpohlen           #+#    #+#             */
/*   Updated: 2021/12/21 15:09:33 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//	Combines 8 bit r g b values into one 32 bit int
int	get_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

//	Extracts 8 bit r value from 32 bit rgb value
int	get_r(int rgb)
{
	return (rgb >> 16 & 0xff);
}

//	Extracts 8 bit g value from 32 bit rgb value
int	get_g(int rgb)
{
	return (rgb >> 8 & 0xff);
}

//	Extracts 8 bit b value from 32 bit rgb value
int	get_b(int rgb)
{
	return (rgb & 0xff);
}
