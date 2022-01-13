/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 14:53:40 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/13 23:46:17 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define DEFAULT_WINX 1800
# define DEFAULT_WINY 1000
# define DEFAULT_ZOOM 1.05
# define DEFAULT_DEPTH 200
# define DEFAULT_FILE "colors.fract"
# define MOVE_MOD 4

# define BASE_16 "0123456789abcdef"

# define ERR_TYPE		1
# define ERR_PARAM		2
# define ERR_NOWIN		3
# define ERR_BADWIN		31
# define ERR_NOFILE		4
# define ERR_BADFILE	41
# define ERR_BADCOLOR	42
# define ERR_NOCOLORS	43
# define ERR_NOCOLOR	44
# define ERR_NODEPTH	5
# define ERR_BADDEPTH	51
# define ERR_NOZOOM		6
# define ERR_BADZOOM	61
# define ERR_DUPLICATE	7

# define RENDER_RECOLOR	1
# define RENDER_REITER	2

# include "libft.h"
# include "mlx.h"
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>

//	Used to describe complex points for escape time calculations
typedef struct s_complex
{
	long double	x;
	long double	y;
}				t_complex;

/* -------------------------------------------------------------------- *\
|		t_params
|
|	See fractol_params.c
|
|	Used to hold parameters during their decoding before using them
|		to create our first t_fract structure.
|
|	- winx		horizontal size of the window
|	- winy		vertical size of the window
|	- zoom		zoom modifier (higher than 1)
|	- depth		starting depth (higher than 0)
|	- type		fractal type
|	- constant	complex point we use as our constant (for julia params)
|	- noauto	whether or not to disable auto-increasing max iterations
|	- file		filename to use when building color palettes
|	- color		name of the color palette to use
\* -------------------------------------------------------------------- */
typedef struct s_params
{
	int			winx;
	int			winy;
	float		zoom;
	int			depth;
	char		type;
	t_complex	constant;
	char		noauto;
	char		*file;
	char		*color;
}			t_params;

/* -------------------------------------------------------------------- *\
|		t_color
|
|	See fractol_colors_decode2.c
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
|		t_img
|
|	See fractol_mlx.c
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
|	Main program structure.
|
|	Used to memorize information relevant to the drawing of a fractal.
|
|	Only one instance of this structure ever exists at once in the
|		program, but more could be used later on when Julia-Mandelbrot
|		linking is implemented.
|
|	- mlx			mlx address to use when updating window
|	- win			window address pertaining to this particular fractal
|						both are used in every window pixel writing function call
|	- winx			horizontal size of the window
|	- winy			vertical size of the window
|						both are used to create new julia windows
|	- img_main		the two images used in tandem to avoid screen tearing
|	- img_temp			the images are swapped so that img_main, the image
|						displayed on screen, is never written on directly
|	- colors		chained list containing all available colors
|						used when changing colors
|	- curcol		current color palette being used
|	- type			type of fractal (m for mandelbrot, j for julia)
|						used in drawing to decide which algorithm to use
|	- pos			fractal x, y complex position of current area
|	- constant		mandel/julia value that will never change
|					(either starting point or c that we add every iteration)
|	- step			fractal step value (describes level of zoom)
|	- max_iter		max iterations of our fractal calculations (or depth)
|						all four are used for escape time and drawing
|	- zoom			by how much to zoom in or out (higher than 1)
|	- autoiter		whether to dynamically change max_iter based on zoom level
\* -------------------------------------------------------------------- */
typedef struct s_fract
{
	void		*mlx;
	void		*win;
	int			winx;
	int			winy;
	float		**map;
	t_img		img_main;
	t_img		img_temp;
	t_color		*colors;
	t_color		*curcol;
	char		type;
	t_complex	pos;
	t_complex	constant;
	long double	step;
	int			max_iter;
	int			highest_iter;
	float		zoom;
	char		autoiter;
}				t_fract;

//// List functions to add, free, seek
// fractol_list.c
void	fractol_lstadd(t_color **lst, t_color *new);
void	fractol_lstclear(t_color *lst);
t_color	*fractol_lstseek(t_color *lst, char *name);
t_color	*fractol_lstprev(t_color *lst, t_color *elem);
t_color	*fractol_lstnext(t_color *lst, t_color *elem);

//// Functions that print info, usage, errors
// fractol_printf.c
void	print_error(int code, char *arg);
void	print_info(t_fract data);
void	print_usage(void);
void	print_guide(void);

//// Parses colors.fract file and fills palettes
//// Used once during program init
// fractol_colors_check.c
// fractol_colors_decode.c
// fractol_colors_decode2.c
int		is_valid_line(char *line);
int		*create_palette(char *line, int size);
t_color	*decode_colors(char *file);
t_color	*default_color(void);

//// Contains useful color functions
// fractol_colors.c
void	fractol_assign_color(t_fract *data, char *name);

//// Parses program arguments, fills program data
//// Or prints a user guide
//// Used once during program init
// fractol_params.c
// fractol_params2.c
// fractol_params3.c
int		params_color(t_params *params, int *i, int ac, char **av);
int		params_window(t_params *params, int *i, int ac, char **av);
int		params_depth(t_params *params, int *i, int ac, char **av);
int		params_zoom(t_params *params, int *i, int ac, char **av);
int		params_file(t_params *params, int *i, int ac, char **av);
int		params_type(t_params *params, int *i, int ac, char **av);
int		params_noauto(t_params *params, int *i);
void	params_error(int code, char *param);
int		params_duplicate(int ac, char **av);
int		fill_params(t_params *params, int ac, char **av);

//// Init functions to boot up the program
// fractol_init.c
int		fractol_init(t_fract *fract, int ac, char **av);

//// Exit functions to free everything and close mlx cleanly
// fractol_exit.c
//int		fractol_exit();
void	free_map(float **map, int len);

//// Functions related to manipulating the minilibx
// fractol_mlx.c
void	pixel_put(t_img img, int x, int y, int color);
int		fractol_init_mlx(t_fract *fw);

//// Functions to calculate and draw different fractals
// fractol_draw.c
// fractol_draw2.c
// fractol_draw3.c
// fractol_draw4.c
float	escape_time(t_complex s, t_complex c, int depth);
void	calculate_map(t_fract data, int iterskip);
void	fill_map_d(t_fract data, int n);
void	fill_map_u(t_fract data, int n);
void	fill_map_r(t_fract data, int n);
void	fill_map_l(t_fract data, int n);
void	calculate_map_partial(t_fract data, char direction, int n);
void	draw_fractal(t_fract data);
void	render_fractal(t_fract *fract, int flag);
void	reset_pos(t_fract *fractal);
void	reset_view(t_fract *fractal);

//// Key and mouse hook functions and the small functions they use
// fractol_keys.c
int		key_hook(int key, t_fract *data);
int		mouse_hook(int key, int x, int y, t_fract *data);
void	next_color(t_fract *fract);
void	prev_color(t_fract *fract);
void	more_iter(t_fract *fract, int n);
void	less_iter(t_fract *fract, int n);
void	zoom_in(t_fract *fract, int x, int y);
void	zoom_out(t_fract *fract, int x, int y);
void	move_view(t_fract *fract, char direction, int n);

#endif
