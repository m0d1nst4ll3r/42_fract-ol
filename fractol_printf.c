/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_printf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 10:11:46 by rpohlen           #+#    #+#             */
/*   Updated: 2021/12/23 18:25:28 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//	Prints out values useful for debugging
void	print_info(t_fract data)
{
	printf("=-._.-=Fractal Information=-._.-=\n");
	printf("- Current pos : %Le, %Le\n", data.pos.x, data.pos.y);
	printf("- Current step : %Le\n", data.step);
	printf("- Current depth : %d\n", data.max_iter);
}

//	Prints usage instructions
void	print_usage(void)
{
	printf("\
Usage:\n\
	./fractol [SET] [OPTION]\n\
\n\
	Supported sets:\n\
	  - mandelbrot\n\
	  - julia [constant] (defaults to -1,0)\n\
	  (- more later)\n\
\n\
	OPTIONS:\n\
	  -help		displays a short user guide\n\
	  -w [x] [y]	window size, defaults to 1800 x 1000\n\
	  -d [max_iter]	specify a starting value for max iterations (defaults at 200)\n\
	  -z [zoom]	specify a zoom value (starting at 1, defaults at 1.05)\n\
	  -c [file]	specify another config file for colors\n\
	  -azerty	changes bindings to azerty equivalents\n\
	  -noauto	disable auto-increasing max iterations\n\
\n\
	Example:\n\
	  ./fractol -help\n\
	  ./fractol mandelbrot -azerty\n\
	  ./fractol julia 0.15 1.15 -w 800 600 -d 1000 -z 1.01\n\
");
}

void	print_guide(void)
{
	printf("\
fractol user guide:\n\
\n\
	- Run the program\n\
	   ./fractol mandelbrot\n\
\n\
	- Use the following mouse commands to explore the fractal\n\
	    RMB		hold and move the mouse to move around the fractal\n\
	    LMB		hold and move the mouse to draw an area to zoom into\n\
	    Mousewheel	zoom in and out\n\
\n\
	  Alternatively, you can use keyboard keys\n\
	    Shift		hold to zoom in\n\
	    Ctrl		hold to zoom out\n\
	    Arrow keys	hold to move around the fractal\n\
\n\
	  More useful commands\n\
	    i		displays useful information\n\
	    j		open a new window with a julia set based on cursor position\n\
	    Spacebar	hold to shift the julia set based on cursor position\n\
	    Esc		close current window\n\
\n\
	- Close all windows or press Shift + Esc to exit\n\
");
}
