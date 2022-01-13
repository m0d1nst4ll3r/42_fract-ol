/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 16:10:37 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/13 23:45:48 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//	Free the 2D int map up to len (typically winy but
//		possibly less in case of failed malloc)
void	free_map(float **map, int len)
{
	while (map && len--)
		free(map[len]);
}
