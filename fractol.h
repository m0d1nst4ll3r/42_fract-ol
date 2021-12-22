/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 14:53:40 by rpohlen           #+#    #+#             */
/*   Updated: 2021/12/22 18:21:36 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

//	This is placeholder, I will have to code in parameters
# define WIN_X 1800
# define WIN_Y 1000
# define STEP 0.0025
# define ZOOM 4
# define DEPTH_MOD 200
# define MOVE_MOD 50
# define COLORS_FILE "colors.fract"
# ifndef DEPTH
#  define DEPTH 200
# endif
# define BASE_16 "0123456789abcdef"

# include "libft.h"
# include "mlx.h"
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>

/* -------------------------------------------------------------------- *\
|		t_color
|
|	Structure used to create a chained list of available colors
|	Colors are defined in colors.fract, decoded in the program, and
|		added to the chained list.
|
|	- palette		array of ints describing the palette's colors in hexa
|	- palette_size	size of the array
|	- name			name to describe the palette
\* -------------------------------------------------------------------- */
typedef struct s_color
{
	int				*palette;
	int				palette_size;
	char			*name;
	struct s_color	*next;
}					t_color;

/* -------------------------------------------------------------------- *\
|		t_fract
|
|	Structure used to memorize information relevant to the drawing of a
|		fractal.
|
|	Only one instance of this structure ever exists at once in the
|		program, but more could be used later on when Julia-Mandelbrot
|		linking is implemented.
|	
|	- mlx			minilibx required address to use its functions
|	- win			minilibx address of current window
|	- img			minilibx address of image
|	- addr			minilibx address of the image's contents
|	- bpp			minilibx bits per pixel value for image calculations
|	- end			minilibx endian value, unused but needed for mlx funcs
|	- llen			minilibx line length needed for image calculations
|	- posx			fractal x, y complex position of current area
|	- posy			.
|	- step			fractal step value (describes level of zoom)
|	- depth			fractal depth value (max iterations)
|	- palette		current palette being used
|	- palette_size	current palette's size
|	- colors		chained list containing all available colors
\* -------------------------------------------------------------------- */
typedef struct s_fract
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bpp;
	int				end;
	int				llen;
	long double		posx;
	long double		posy;
	long double		step;
	int				depth;
	int				*palette;
	int				palette_size;
	t_color			*colors;
}					t_fract;

//// All the functions related to color manipulation
//	 fractol_utils_color.c
//	 fractol_utils_color2.c
int		get_rgb(int r, int g, int b);
int		get_r(int rgb);
int		get_g(int rgb);
int		get_b(int rgb);
int		get_gradient(int color1, int color2, float ratio);
int		*get_gradient_palette(int *colors, int color_count, int size);

//// Parses colors.fract file and fills palettes
//// Used once during program init
//	 fractol_colors_check.c
//	 fractol_colors_decode.c
//	 fractol_colors_decode2.c
int		is_valid_line(char *line);
int		*create_palette(char *line, int size);
t_color	*decode_colors(char *file);

//// Utility functions
//	 fractol_utils.c
//	 fractol_utils_list.c
int		pendulum(int len, int val);
void	print_info(t_fract data);
void	fractol_lstadd(t_color **lst, t_color *new);
void	fractol_lstclear(t_color *lst);

#endif
