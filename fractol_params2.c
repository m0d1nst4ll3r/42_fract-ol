/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_params2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 16:36:05 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/06 18:11:37 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	params_color(t_params *params, int *i, int ac, char **av)
{
	(*i)++;
	if (*i == ac)
	{
		params_error(ERR_NOCOLOR, 0);
		return (1);
	}
	params->color = av[*i];
	return (0);
}

int	params_window(t_params *params, int *i, int ac, char **av)


int	params_depth(t_params *params, int *i, int ac, char **av)
{
	(*i)++;
	if (*i == ac)
	{
		params_error(ERR_NODEPTH, 0);
		return (1);
	}
	if (!ft_isint(av[i]))
	{
		params_error(ERR_BADDEPTH, 0);
		return (1);
	}
	params->depth = ft_atoi(av[*i]);
	return (0);
}

int	params_zoom(t_params *params, int *i, int ac, char **av)
{
	(*i)++;
	if (*i == ac)
	{
		params_error(ERR_NOZOOM, 0);
		return (1);
	}
	if (!ft_isfloat(av[i]))
	{
		params_error(ERR_BADZOOM, 0);
		return (1);
	}
	params->zoom = ft_atof(av[*i]);
	return (0);
}

int	params_file(t_params *params, int *i, int ac, char **av)
{
	(*i)++;
	if (*i == ac)
	{
		params_error(ERR_NOFILE, 0);
		return (1);
	}
	params->file = av[*i];
	return (0);
}
