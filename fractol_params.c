/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 16:12:27 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/06 18:10:52 by rpohlen          ###   ########.fr       */
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

void	params_error(int code, char *param)
{
	if (param && is_help(param))
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
	if (!strcmp("-c", av[i]))
		return (params_color(&params, i, ac, av));
	else if (!strcmp("-w", av[i]))
		return (params_window(&params, i, ac, av));
	else if (!strcmp("-d", av[i]))
		return (params_depth(&params, i, ac, av));
	else if (!strcmp("-z", av[i]))
		return (params_zoom(&params, i, ac, av));
	else if (!strcmp("-f", av[i]))
		return (params_file(&params, i, ac, av));
	else if (!strcmp("-noauto", av[i]))
		return (params_noauto(&params, i));
	else
	{
		params_error(ERR_PARAM, av[i]);
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
t_params	fill_params(int ac, char **av)
{
	int			i;
	t_params	params;

	params_init(&params);
	i = 1;
	if (params_type(&params, &i, ac, av))
		return (NULL);
	while (i < ac)
	{
		if (params_check(&params, &i, ac, av))
			return (NULL);
	}
	return (params);
}
