/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_params3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 16:36:52 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/20 22:56:03 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//	Used to decode the two potential floating point numbers following
//		"julia" in the command line
//	Note that if the numbers are incorrect, they are ignored and treated
//		as regular flags like "-c" (and will error out)
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

//	Used to decode the first command line argument which should contain
//		fractal type.
//	If it is absent, we simply print usage.
int	params_type(t_params *params, int *i, int ac, char **av)
{
	if (*i >= ac)
	{
		print_usage();
		return (1);
	}
	else if (!ft_strxcmp("julia", av[*i]))
		params_julia(params, i, ac, av);
	else if (!ft_strxcmp("mandelbrot", av[*i]) || !ft_strcmp("m2", av[*i]))
		params->type = 'm';
	else if (!ft_strcmp("mandel3", av[*i]) || !ft_strcmp("m3", av[*i]))
		params->type = '3';
	else if (!ft_strcmp("mandel4", av[*i]) || !ft_strcmp("m4", av[*i]))
		params->type = '4';
	else if (!ft_strcmp("mandel5", av[*i]) || !ft_strcmp("m5", av[*i]))
		params->type = '5';
	else
	{
		params_error(ERR_TYPE, av[*i]);
		return (1);
	}
	(*i)++;
	return (0);
}

//	Used to check for duplicate flags
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

//	The only flag which doesn't have any mandatory or optional value
int	params_noauto(t_params *params, int *i)
{
	params->noauto = 1;
	(*i)++;
	return (0);
}
