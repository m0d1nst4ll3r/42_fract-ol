/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_params2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 16:36:05 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/06 19:19:30 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	params_color(t_params *params, int *i, int ac, char **av)
{
	if (*i >= ac - 1)
	{
		params_error(ERR_NOCOLOR, 0);
		return (1);
	}
	params->color = av[(*i) + 1];
	*i += 2;
	return (0);
}

int	params_window(t_params *params, int *i, int ac, char **av)
{
	int	winx;
	int	winy;

	if (*i >= ac - 2)
	{
		params_error(ERR_NOWIN, 0);
		return (1);
	}
	winx = ft_atoi(av[(*i) + 1]);
	winy = ft_atoi(av[(*i) + 2]);
	if (!ft_isint(av[(*i) + 1]) || !ft_isint(av[(*i) + 2])
		|| winx < 100 || winy < 100)
	{
		params_error(ERR_BADWIN, av[(*i) + 1]);
		return (1);
	}
	params->winx = winx;
	params->winy = winy;
	*i += 3;
	return (0);
}

int	params_depth(t_params *params, int *i, int ac, char **av)
{
	int	depth;

	if (*i >= ac - 1)
	{
		params_error(ERR_NODEPTH, 0);
		return (1);
	}
	depth = ft_atoi(av[(*i) + 1]);
	if (!ft_isint(av[(*i) + 1]) || depth < 1)
	{
		params_error(ERR_BADDEPTH, av[(*i) + 1]);
		return (1);
	}
	params->depth = depth;
	*i += 2;
	return (0);
}

int	params_zoom(t_params *params, int *i, int ac, char **av)
{
	float	zoom;

	if (*i >= ac - 1)
	{
		params_error(ERR_NOZOOM, 0);
		return (1);
	}
	zoom = ft_atof(av[(*i) + 1]);
	if (zoom <= 1)
	{
		params_error(ERR_BADZOOM, av[(*i) + 1]);
		return (1);
	}
	params->zoom = zoom;
	*i += 2;
	return (0);
}

int	params_file(t_params *params, int *i, int ac, char **av)
{
	if (*i >= ac - 1)
	{
		params_error(ERR_NOFILE, 0);
		return (1);
	}
	params->file = av[(*i) + 1];
	*i += 2;
	return (0);
}
