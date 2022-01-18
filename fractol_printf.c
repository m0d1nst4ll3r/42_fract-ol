/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_printf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 10:11:46 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/18 04:15:54 by rpohlen          ###   ########.fr       */
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
	printf("\e[0;31m=-._.-=Fractal Information=-._.-=\e[0m\n");
	printf("\e[0;33m- Position :\e[0m\t\t%Le, %Le\n", data.pos.x, data.pos.y);
	printf("\e[0;33m- Step :\e[0m\t\t%Le\n", data.step);
	printf("\e[0;33m- Max iter :\e[0m\t\t%d\n", data.max_iter);
	if (data.autoiter)
		printf("\e[0;33m- Iterations :\e[0m\t\tauto\n");
	else
		printf("\e[0;33m- Iterations :\e[0m\t\tmanual\n");
	printf("\e[0;33m- Zoom strength:\e[0m\t%.2f\n", data.zoom);
	printf("\e[0;33m- Color :\e[0m\t\t%s\n", data.curcol->name);
}

//	Used when program arguments are absent or wrong
void	print_usage(void)
{
	printf("\n\e[4;31mFractol usage:\e[0m\n\n\
	  \e[0;32m./fractol [SET] [OPTION]\e[0m\n\
\n\
	\e[0;31mSupported sets:\e[0m\n\
	  \e[0;33mmandelbrot\e[0m\n\
	  \e[0;33mmandel3\e[0m\n\
	  \e[0;33mmandel4\e[0m\n\
	  \e[0;33mmandel5\e[0m\n\
	  \e[0;33mjulia [constant]\e[0m (defaults to [0,-0.8])\n\
\n\
	\e[0;31mOptions:\e[0m\n\
	  \e[0;33m-help or -h\e[0m	displays the user guide\n\
	  \e[0;33m-c\e[0m		specify a color theme (defaults to a random one)\n\
	  \e[0;33m-w [x] [y]\e[0m	window size, 200x200 minimum, defaults to 1800x1000\n\
	  \e[0;33m-d [max_iter]\e[0m	specify a starting value for max iterations (defaults to ~200)\n\
	  \e[0;33m-z [zoom]\e[0m	specify a zoom value (higher than 1, defaults to 1.05)\n\
	  \e[0;33m-f [file]\e[0m	specify another config file for colors\n\
	  \e[0;33m-noauto\e[0m	disable auto-increasing max iterations (implied by -d)\n\
\n\
	\e[0;31mExamples:\e[0m\n\
	  ./fractol help\n\
	  ./fractol mandelbrot\n\
	  ./fractol m -c rainbow\n\
	  ./fractol julia 0.15 1.15 -w 800 600 -d 1000 -z 1.01\n\n");
}

//	Used when help is found in program arguments
void	print_guide(void)
{
	printf("\n\e[4;31mFractol user guide:\e[0m\n\n\
	\e[0;31mRun the program\e[0m\n\
	   \e[0;32m./fractol mandelbrot\e[0m\n\n\
	\e[0;31mUse the following commands to explore the fractal\e[0m\n\
	    \e[0;33mLMB / Shift / =\e[0m	hold to zoom in\n\
	    \e[0;33mRMB / Ctrl  / -\e[0m	hold to zoom out\n\
	    \e[0;33mWASD / Arrow keys\e[0m	hold to move around the fractal\n\n\
	\e[0;31mMore useful commands\n\
	    \e[0;33mr\e[0m			go back to the beginning (reset)\n\
	    \e[0;33mSpacebar\e[0m		run SSAA filter on current image\n\
		\e[0;33mc\e[0m			toggle color smoothing\n\
	    \e[0;33mq, e\e[0m		change color\n\
	    \e[0;33mz, x\e[0m		change zoom strength\n\
	    \e[0;33m7, 8\e[0m		change max iterations by 1 (disables auto iterations)\n\
	    \e[0;33m5, 6\e[0m		change max iterations by 10\n\
	    \e[0;33m3, 4\e[0m		change max iterations by 100\n\
	    \e[0;33m1, 2\e[0m		change max iterations by 1000\n\
	    \e[0;33mTab\e[0m			re-enable auto iterations\n\
	    \e[0;33mi\e[0m			displays useful information\n\
	    \e[0;33mEsc\e[0m			exit the program\n\n\
	\e[0;31mYou can look at and configure colors by editing colors.fract\n\n");
}
