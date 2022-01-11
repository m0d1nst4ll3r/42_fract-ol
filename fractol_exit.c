/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 16:10:37 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/11 16:11:43 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//	Free the 2D int map up to len (typically winy but
//		possibly less in case of failed malloc)
void	free_map(int **map, int len)
{
	while (map && len--)
		free(map[len]);
}
