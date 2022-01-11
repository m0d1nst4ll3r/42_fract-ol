/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 12:34:02 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/11 17:19:00 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//	Attempts to assign a named color to the t_fract structure provided
//	Colors are stored in its "colors" element, as a chained list
//	If the named color does not exist in the list, pick the first one
void	fractol_assign_color(t_fract *data, char *name)
{
	t_color	*color;

	color = NULL;
	if (name)
		color = fractol_lstseek(data->colors, name);
	if (!color)
		color = data->colors;
	data->curcol = color;
}
