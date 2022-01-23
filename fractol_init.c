/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:57:42 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/22 23:23:28 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//	Write NULL into all pointers so we can free them anytime
static void	init_null(t_fract *fract)
{
	fract->mlx = NULL;
	fract->win = NULL;
	fract->map = NULL;
	fract->img_main.img = NULL;
	fract->img_temp.img = NULL;
	fract->colors = NULL;
	fract->curcol = NULL;
}

//	Adds the params, as read from the command line, to the data structure
//	smoothcol, ssaa_samples and shiftmode are initalized to their defaults
static void	init_copy(t_params params, t_fract *fract)
{
	fract->winx = params.winx;
	fract->winy = params.winy;
	fract->zoom = params.zoom;
	fract->max_iter = params.depth;
	fract->type = params.type;
	fract->constant = params.constant;
	fract->autoiter = !params.noauto;
	fract->smoothcol = 1;
	fract->ssaa_samples = 2;
	fract->shiftmode = 0;
}

//	Malloc the map - it's freed in exit_program
static int	init_map(t_fract *fract)
{
	int	i;

	fract->map = malloc(fract->winy * sizeof(*fract->map));
	if (!fract->map)
		return (1);
	i = 0;
	while (i < fract->winy)
	{
		fract->map[i] = malloc(fract->winx * sizeof(**fract->map));
		if (!fract->map[i])
		{
			free_map(fract->map, i);
			return (1);
		}
		i++;
	}
	return (0);
}

//	Attempts to initialize mlx, create the window,
//		and create its two images
//	If at any point something breaks, we exit the program
static int	init_mlx(t_fract *f)
{
	f->mlx = mlx_init();
	if (!f->mlx)
		return (1);
	f->win = mlx_new_window(f->mlx, f->winx, f->winy, "fol");
	if (!f->win)
		return (1);
	f->img_main.img = mlx_new_image(f->mlx, f->winx, f->winy);
	if (!f->img_main.img)
		return (1);
	f->img_main.addr = mlx_get_data_addr(f->img_main.img,
			&f->img_main.bpp, &f->img_main.llen, &f->img_main.end);
	f->img_temp.img = mlx_new_image(f->mlx, f->winx, f->winy);
	if (!f->img_temp.img)
		return (1);
	f->img_temp.addr = mlx_get_data_addr(f->img_temp.img,
			&f->img_temp.bpp, &f->img_temp.llen, &f->img_temp.end);
	return (0);
}

/* --------------------------------------------------------------------- *\
|		fractol_init
|
|	Initializes program in several steps -
|
|	1. Initialize all pointers to NULL to avoid free problems
|	2. Use command line arguments to fill a params structure
|	   Exit if an error is found
|	3. Copy all the data from the params structure to the fract one
|	4. Attempt to initialize mlx, a window and two images
|	5. Allocate memory for the iterations map
|	6. Use the colors file to create a list of palettes
|	   Create a default palette if no colors could be created
|	7. Assign a starting color based on the given color name
|
|	In case of any failure, the program will exit after freeing all.
\* --------------------------------------------------------------------- */
int	fractol_init(t_fract *fract, int ac, char **av)
{
	t_params	params;

	init_null(fract);
	if (fill_params(&params, ac, av))
		return (1);
	init_copy(params, fract);
	if (init_mlx(fract))
		return (2);
	if (init_map(fract))
		return (3);
	fract->colors = decode_colors(params.file);
	if (!fract->colors)
	{
		print_error(ERR_NOCOLORS, NULL);
		fract->colors = default_color();
		if (!fract->colors)
			return (4);
	}
	fractol_assign_color(fract, params.color);
	reset_pos(fract);
	return (0);
}
