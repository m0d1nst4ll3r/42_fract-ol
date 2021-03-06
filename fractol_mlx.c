/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_mlx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 13:42:03 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/11 16:07:13 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//	Custom pixel put necessary to save on a lot of lag
//	Uses the image's array directly instead of mlx's own pixel put
void	pixel_put(t_img img, int x, int y, int color)
{
	char	*dst;

	dst = img.addr + (y * img.llen + x * img.bpp / 8);
	*(int *)dst = color;
}
