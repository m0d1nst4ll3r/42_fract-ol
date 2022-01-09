/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_params3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 16:36:52 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/09 20:56:17 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	params_julia(t_params *params, int *i, int ac, char **av)
{
	params->type = 'j';
	params->constant.x = 0;
	params->constant.y = -0.8;
	if (*i < ac - 2 && ft_isfloat(av[(*i) + 1]) && ft_isfloat(av[(*i) + 2]))
	{
		params->constant.x = ft_atof(av[(*i) + 1]);
		params->constant.y = ft_atof(av[(*i) + 2]);
		(*i) += 2;
	}
}

int	params_type(t_params *params, int *i, int ac, char **av)
{
	if (*i >= ac)
		print_usage();
	else if (!ft_strxcmp("julia", av[*i]))
	{
		params_julia(params, i, ac, av);
		(*i)++;
		return (0);
	}
	else if (!ft_strxcmp("mandelbrot", av[*i]))
	{
		(*i)++;
		return (0);
	}
	else
		params_error(ERR_TYPE, av[*i]);
	return (1);
}

int	params_duplicate(int ac, char **av)
{
	int	i;
	int	j;

	i = 0;
	while (i < ac)
	{
		if (!ft_strcmp(av[i], "-w") || !ft_strcmp(av[i], "-c")
			|| !ft_strcmp(av[i], "-d") || !ft_strcmp(av[i], "-z")
			|| !ft_strcmp(av[i], "-f") || !ft_strcmp(av[i], "-noauto"))
		{
			j = i - 1;
			while (j > 0)
			{
				if (!ft_strcmp(av[i], av[j]))
					return (1);
				j--;
			}
		}
		i++;
	}
	return (0);
}

int	params_noauto(t_params *params, int *i)
{
	params->noauto = 1;
	(*i)++;
	return (0);
}
