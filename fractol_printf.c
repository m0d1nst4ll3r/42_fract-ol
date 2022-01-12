/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_printf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 10:11:46 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/12 21:35:29 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//	Errors detected during program init
static void	print_error2(int code, char *arg)
{
	if (code == ERR_BADZOOM)
		printf("Incorrect zoom value. Must be higher than 1.\n");
	else if (code == ERR_BADCOLOR)
		printf("Color '%s' not found. Defaulting to a random color.\n", arg);
	else if (code == ERR_NOCOLORS)
		printf("No valid color line found in color file. Using default \
palette.\n");
	else if (code == ERR_NOCOLOR)
		printf("Flag '-c' requires a color name.\n");
	else if (code == ERR_DUPLICATE)
		printf("Duplicate flag detected. Please use each flag only once.\n");
	else
		printf("Undefined error\n");
}

void	print_error(int code, char *arg)
{
	if (code == ERR_TYPE)
		printf("Incorrect fractal type '%s'. Valid fractal types include: \
mandelbrot, julia.\n", arg);
	else if (code == ERR_PARAM)
		printf("Incorrect flag '%s'. See usage for a list of valid flags.\n",
			arg);
	else if (code == ERR_NOFILE)
		printf("Flag '-f' requires a filename.\n");
	else if (code == ERR_NOWIN)
		printf("Flag '-w' requires two integers higher than 100. Ex: '-w 800 \
600'\n");
	else if (code == ERR_NODEPTH)
		printf("Flag '-d' requires an integer number.\n");
	else if (code == ERR_NOZOOM)
		printf("Flag '-z' requires a rational number.\n");
	else if (code == ERR_BADFILE)
		printf("Could not open color config file '%s'. Using default \
palette.\n", arg);
	else if (code == ERR_BADWIN)
		printf("Incorrect window size. Must be two integers higher than \
200x200.\n");
	else if (code == ERR_BADDEPTH)
		printf("Incorrect max iterations value. Must be higher than 0.\n");
	else
		print_error2(code, arg);
}

//	Prints out values useful for debugging, when the I key is pressed
//	More info needs to be displayed, like :
//		- current color
//		- time spent processing last frame
void	print_info(t_fract data)
{
	printf("=-._.-=Fractal Information=-._.-=\n");
	printf("- Current pos : %Le, %Le\n", data.pos.x, data.pos.y);
	printf("- Current step : %Le\n", data.step);
	printf("- Current depth : %d\n", data.max_iter);
	printf("- Current color : %s\n", data.curcol->name);
}

//	Used when program arguments are absent or wrong
void	print_usage(void)
{
	printf("\
Usage:\n\
	./fractol [SET] [OPTION]\n\
\n\
	Supported sets:\n\
	  mandelbrot\n\
	  julia [constant] (defaults to [0,-0.8])\n\
	  (more later)\n\
\n\
	OPTIONS:\n\
	  -help or -h	displays the user guide\n\
	  -c		specify a color theme (defaults to a random one)\n\
	  -w [x] [y]	window size, 200x200 minimum, defaults to 1800x1000\n\
	  -d [max_iter]	specify a starting value for max iterations (defaults to 200)\n\
	  -z [zoom]	specify a zoom value (higher than 1, defaults to 1.05)\n\
	  -f [file]	specify another config file for colors\n\
	  -noauto	disable auto-increasing max iterations (implied by -d)\n\
\n\
	Examples:\n\
	  ./fractol help\n\
	  ./fractol mandelbrot\n\
	  ./fractol m -c rainbow\n\
	  ./fractol julia 0.15 1.15 -w 800 600 -d 1000 -z 1.01\n\
");
}

//	Used when help is found in program arguments
void	print_guide(void)
{
	printf("fractol user guide:\n\n\
	- Run the program\n\
	   ./fractol mandelbrot\n\n\
	- Use the following mouse commands to explore the fractal\n\
	    RMB		hold and move the mouse to move around the fractal\n\
	    LMB		hold and move the mouse to draw an area to zoom into\n\
	    Mousewheel	zoom in and out\n\n\
	  Alternatively, you can use keyboard keys\n\
	    Shift	hold to zoom in\n\
	    Ctrl	hold to zoom out\n\
	    Arrow keys	hold to move around the fractal\n\n\
	  More useful commands\n\
	    r		go back to the beginning (reset)\n\
	    v, c	change color\n\
	    b, n	change max iterations by 1 (disables auto iterations)\n\
	    shift+b, n	change max iterations by 10\n\
	    ctrl+b, n	change max iterations by 100\n\
	    m		re-enable auto iterations\n\
	    i		displays useful information\n\
	    j		open a new window with a julia set based on cursor position\n\
	    Spacebar	hold to shift the julia set based on cursor position\n\
	    Esc		close current window\n\n\
	- Close all windows or press Shift + Esc to exit\n\n\
	- You can look at and configure colors by editing colors.fract\n");
}
