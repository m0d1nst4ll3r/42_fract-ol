/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 16:12:27 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/04 17:15:25 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_params(t_params *params)
{
	params->winx = DEFAULT_WINX;
	params->winy = DEFAULT_WINY;
	params->zoom = DEFAULT_ZOOM;
	params->depth = DEFAULT_DEPTH;
	params->type = 'm';
	params->noauto = 0;
	params->file = DEFAULT_FILE;
	params->color = NULL;
}

t_params	fill_params(int ac, char **av)
{
	t_params	params;

	init_params(&params);
	if (ac-- == 1)
		return (NULL);
	while (ac--)
	{

	}

	return (params);
}
