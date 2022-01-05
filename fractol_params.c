/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 16:12:27 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/05 17:56:22 by rpohlen          ###   ########.fr       */
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

int	is_help(char *s)
{
	if (!strcmp("help", s) || !strcmp("-help", s) || !strcmp("h", s)
			|| !strcmp("--help", s) || !strcmp("-h", s))
		return (1);
	return (0);
}

void	params_error(char *param, char *error)
{
	if (is_help(param))
		print_guide();
	else
	{
		printf("%s", error);
		print_usage();
	}
}

int	params_julia(t_params *params, int *i, int ac, char **av)
{
	params->constant.x = -1;
	params->constant.y = 0;
	if ()
}

int	params_type(t_params *params, int *i, int ac, char **av)
{
	if (i == ac)
		print_usage();
	else if (!strxcmp("julia", av[i]))
	{
		params->type = 'j';
		(*i)++;
		if (*i + 2 )
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

/* --------------------------------------------------------------------- *\
|		fill_params
|
|	Parses parameters and returns a list of them in structure form.
|
|	Returns NULL in case any error is found. Automatically prints a
|		relevant message pertaining to the error.
\* --------------------------------------------------------------------- */
t_params	fill_params(int ac, char **av)
{
	int			i;
	t_params	params;

	params_init(&params);
	i = 1;
	if (params_type(&params, &i, ac, av))
		return (NULL);
	while (i <= ac)
	{

	}

	return (params);
}
