/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 03:11:23 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/08 23:18:41 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//	Attempts to assign a named color to the t_fract structure provided
//	Colors are stored in its "colors" element, as a chained list
//	If the named color does not exist in the list, pick the first one
void	pick_color(t_fract *data, char *name)
{
	t_color	*color;

	color = fractol_lstseek(data->colors, name);
	if (!color)
		color = data->colors;
	data->current = color;
}

void	copy_params(t_params params, t_fract *firstwin)
{
	firstwin->winx = params.winx;
	firstwin->winy = params.winy;
	firstwin->zoom = params.zoom;
	firstwin->max_iter = params.depth;
	firstwin->type = params.type;
	firstwin->constant = params.constant;
	firstwin->autoiter = !params.noauto;
}

int	fractol_init_mlx(t_fract *fw)
{
	fw->mlx = mlx_init();
	if (!fw->mlx)
		return (1);
	fw->win = mlx_new_window(fw->mlx, fw->winx,	fw->winy,
			"°º¤ø,¸¸,ø¤º°` FR4CT-0L `°º¤ø,¸,ø¤º°");
	if (!fw->win)
		return (1);
	fw->img_main.img = mlx_new_image(fw->mlx, fw->winx, fw->winy);
	if (!fw->img_main.img)
		return (1);
	fw->img_main.addr = mlx_get_data_addr(fw->img_main.img,
			&fw->img_main.bpp, &fw->img_main.llen, &fw->img_main.end);
	fw->img_temp.img = mlx_new_image(fw->mlx, fw->winx, fw->winy);
	if (!fw->img_temp.img)
		return (1);
	fw->img_temp.addr = mlx_get_data_addr(fw->img_temp.img,
			&fw->img_temp.bpp, &fw->img_temp.llen, &fw->img_temp.end);
	return (0);
}

/* --------------------------------------------------------------------- *\
|		fractol_reset_pos
|
|	Resets a fractal's step, pos.x and pos.y to default ones.
|
|	A bigger window will naturally cause a lower step (more zoomed).
|
|	Mandelbrot fractals are offset by -0.75 on the x axis to account for
|		its particular shape.
|	Julia fractals are always centered around 0.
|
|	Mandelbrot graphs are considered to be :
|		x	-2 to 0.5
|		y	-1.5 to 1.5
|	Julia graphs are considered to be :
|		x	-2 to 2
|		y	-1.5 to 1.5
\* --------------------------------------------------------------------- */
void	fractol_reset_pos(t_fract *fractal)
{
	long double	step_tmp;

	if (fractal->type == 'm')
	{
		fractal->step = 2.5 / fractal->winx;
		step_tmp = 2.5 / fractal->winy;
		if (fractal->step < step_tmp)
			fractal->step = step_tmp;
		fractal->pos.x = - fractal->winx / 2 * fractal->step - 0.75;
		fractal->pos.y = fractal->winy / 2 * fractal->step;
	}
	else
	{
		fractal->step = 4.0 / fractal->winx;
		step_tmp = 3.0 / fractal->winy;
		if (fractal->step < step_tmp)
			fractal->step = step_tmp;
		fractal->pos.x = - fractal->winx / 2 * fractal->step;
		fractal->pos.y = fractal->winy / 2 * fractal->step;
	}
}

/* --------------------------------------------------------------------- *\
|		fractol_init
|
|	Initializes program in 3 steps -
|
|	1. Checks and fills params from main
|	2. Fills color palettes with config file and picks one
|	3. Initializes mlx, one window, and two images, and writes all
|		the data in a t_fract structure
\* --------------------------------------------------------------------- */
int	fractol_init(t_fract *fw, int ac, char **av)
{
	t_params	params;

	if (fill_params(&params, ac, av))
		return (1);
	fw->colors = decode_colors(params.file);
	if (!fw->colors)
	{
		print_error(ERR_NOCOLORS, NULL);
		fw->colors = default_color();
		if (!fw->colors)
			return (1);
	}
	pick_color(fw, params.color);
	copy_params(params, fw);
	if (fractol_init_mlx(fw))
		return (1);
	fractol_reset_pos(fw);
	return (0);
}

int	main(int ac, char **av)
{
	t_fract	firstwin;

	if (fractol_init(&firstwin, ac, av))
		return (1);
	draw_fractal(firstwin);
	mlx_put_image_to_window(firstwin.mlx, firstwin.win, firstwin.img_temp.img, 0, 0);

	//mlx_hook(data.win, 2, 1L<<0, key_hook, &data);
	//mlx_hook(data.win, 4, 1L<<2, mouse_hook, &data);
	mlx_loop(firstwin.mlx);
	return (0);
}
