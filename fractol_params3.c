/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_params3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 16:36:52 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/06 16:38:44 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	params_julia(t_params *params, int *i, int ac, char **av)
{
	params->constant.x = -1;
	params->constant.y = 0;
	if ()
}

int	params_type(t_params *params, int *i, int ac, char **av)
{
	if (i >= ac)
		print_usage();
	else if (!strxcmp("julia", av[i]))
	{
		params->type = 'j';
		(*i)++;
		if ()
			params_julia(params, i, ac, av);
		return (0);
	}
	else if (!strxcmp("mandelbrot", av[i]))
	{
		(*i)++;
		return (0);
	}
	else if (is_help(av[i]))
		print_guide();
	else
		print_usage();
	return (1);
}

int	params_noauto(t_params *params, int *i)
{
	params->noauto = 1;
	(*i)++;
	return (0);
}
