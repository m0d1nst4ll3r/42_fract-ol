/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 16:12:27 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/06 19:22:26 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	params_init(t_params *params)
{
	params->winx = DEFAULT_WINX;
	params->winy = DEFAULT_WINY;
	params->zoom = DEFAULT_ZOOM;
	params->depth = DEFAULT_DEPTH;
	params->type = 'm';
	params->noauto = 0;
	params->file = DEFAULT_FILE;
	params->color = NULL;
	params->constant.x = 0;
	params->constant.y = 0;
}

int	params_is_help(char *s)
{
	if (!ft_strcmp("help", s) || !ft_strcmp("-help", s) || !ft_strcmp("h", s)
		|| !ft_strcmp("--help", s) || !ft_strcmp("-h", s))
		return (1);
	return (0);
}

void	params_error(int code, char *param)
{
	if (param && params_is_help(param))
		print_guide();
	else
	{
		if (code)
			print_error(code, param);
		print_usage();
	}
}

int	params_check(t_params *params, int *i, int ac, char **av)
{
	if (!ft_strcmp("-c", av[*i]))
		return (params_color(params, i, ac, av));
	else if (!ft_strcmp("-w", av[*i]))
		return (params_window(params, i, ac, av));
	else if (!ft_strcmp("-d", av[*i]))
		return (params_depth(params, i, ac, av));
	else if (!ft_strcmp("-z", av[*i]))
		return (params_zoom(params, i, ac, av));
	else if (!ft_strcmp("-f", av[*i]))
		return (params_file(params, i, ac, av));
	else if (!ft_strcmp("-noauto", av[*i]))
		return (params_noauto(params, i));
	else
	{
		params_error(ERR_PARAM, av[*i]);
		return (1);
	}
}

/* --------------------------------------------------------------------- *\
|		fill_params
|
|	Parses parameters and returns a list of them in structure form.
|
|	Returns NULL in case any error is found. Automatically prints a
|		relevant message pertaining to the error.
\* --------------------------------------------------------------------- */
int	fill_params(t_params *params, int ac, char **av)
{
	int			i;

	params_init(params);
	i = 1;
	if (params_type(params, &i, ac, av))
		return (1);
	while (i < ac)
	{
		if (params_check(params, &i, ac, av))
			return (1);
	}
	return (0);
}
