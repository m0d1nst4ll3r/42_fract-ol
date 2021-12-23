/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 14:53:40 by rpohlen           #+#    #+#             */
/*   Updated: 2021/12/23 18:51:32 by rpohlen          ###   ########.fr       */
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

typedef struct s_complex
{
	long double	x;
	long double	y;
}				t_complex;

/* -------------------------------------------------------------------- *\
|		t_img
|
|	Holds all information pertaining to an image.
|	Typically used in pairs to avoid writing on an image being displayed.
|
|	- img		img address to be used when displaying the image
|	- addr		address of the image's pixels to be used when updating them
|	- bpp		bits per pixel
|	- end		endian
|	- llen		line length
|				the 3 above values are used to update pixels using addr
\* -------------------------------------------------------------------- */
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		end;
	int		llen;
}			t_img;

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
|	- type			type of fractal (m for mandelbrot, j for julia...)
|	- mlx			mlx address to use when updating window
|	- win			window address pertaining to this particular fractal
|	- img_main
|	- img_temp		the two images used in tandem to avoid screen tearing
|						the images are swapped so that img_main, the image
|						displayed on screen, is never written on directly
|	- pos			fractal x, y complex position of current area
|	- step			fractal step value (describes level of zoom)
|	- max_iter		max iterations of our fractal calculations
|	- palette		current palette being used
|	- palette_size	current palette's size
|	- colors		chained list containing all available colors
\* -------------------------------------------------------------------- */
typedef struct s_fract
{
	char		type;
	void		*mlx;
	void		*win;
	t_img		img_main;
	t_img		img_temp;
	t_complex	pos;
	t_complex	constant;
	long double	step;
	int			max_iter;
	int			*palette;
	int			palette_size;
	t_color		*colors;
}				t_fract;

//// Functions to calculate and draw different fractals
// fractol_draw.c
void	draw_mandelbrot(t_fract data);
void	draw_julia(t_fract data);

//// Functions related to manipulating the minilibx
// fractol_mlx.c
void	pixel_put(t_img img, int x, int y, int color);

//// Parses colors.fract file and fills palettes
//// Used once during program init
// fractol_colors_check.c
// fractol_colors_decode.c
// fractol_colors_decode2.c
int		is_valid_line(char *line);
int		*create_palette(char *line, int size);
t_color	*decode_colors(char *file);

//// Functions that print stuff
// fractol_printf.c
void	print_info(t_fract data);
void	print_usage(void);
void	print_guide(void);

//// List functions
// fractol_list.c
void	fractol_lstadd(t_color **lst, t_color *new);
void	fractol_lstclear(t_color *lst);

//// Key and mouse functions
// fractol_keys.c
int		key_hook(int key, t_fract *data);
int		mouse_hook(int key, int x, int y, t_fract *data);

#endif
