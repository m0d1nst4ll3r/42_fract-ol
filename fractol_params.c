/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 16:12:27 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/22 23:11:36 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* --------------------------------------------------------------------- *\
|		params_init
|
|	See fractol.h for detailed descriptions of elements
|
|	- winx			Defaults to the define (1800 as of writing)
|	- winy			... 1000
|	- zoom			... 1.05
|	- depth			... 200
|	- type			Defaults to mandelbrot
|	- noauto		Defaults to 0, auto max_iter incrementation is on
|	- file			Defaults to "colors.fract" as per define
|	- color			Defaults to the first color (NULL is handled later)
|	- constant		Defaults to 0, 0, the mandelbrot value
\* --------------------------------------------------------------------- */
static void	params_init(t_params *params)
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

//	Used to check whether the user needs help
static int	params_is_help(char *s)
{
	if (!ft_strcmp("help", s) || !ft_strcmp("-help", s) || !ft_strcmp("h", s)
		|| !ft_strcmp("--help", s) || !ft_strcmp("-h", s))
		return (1);
	return (0);
}

//	When the string that caused a param error contains "help" in some form,
//		prints the user guide, otherwise, prints an error string and
//		regular usage.
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

//	Depending on the flag found, launches a specific function
//	If the flag does not exist, error out
static int	params_check(t_params *params, int *i, int ac, char **av)
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
|	Parses program arguments and fills a list of parameters.
|
|	Returns 1 in case any error is found. Automatically prints a
|		relevant message pertaining to the error, as well as a
|		usage/user guide message.
\* --------------------------------------------------------------------- */
int	fill_params(t_params *params, int ac, char **av)
{
	int			i;

	if (params_duplicate(ac, av))
	{
		params_error(ERR_DUPLICATE, 0);
		return (1);
	}
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
