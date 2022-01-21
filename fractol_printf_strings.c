/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_printf_strings.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:58:26 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/20 16:54:08 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

char	*str_iter(char autoiter)
{
	if (autoiter)
		return ("auto");
	return ("manual");
}

char	*str_color(char smoothcol)
{
	if (smoothcol)
		return ("smooth");
	return ("banding");
}
