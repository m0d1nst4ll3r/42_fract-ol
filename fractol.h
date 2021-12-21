/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 14:53:40 by rpohlen           #+#    #+#             */
/*   Updated: 2021/12/21 19:34:51 by rpohlen          ###   ########.fr       */
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
# ifndef DEPTH
#  define DEPTH 200
# endif

# include "libft.h"
# include "mlx.h"
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct s_color
{
	int				*palette;
	int				palette_size;
	char			*name;
	struct s_color	*next;
}					t_color;

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

//	fractol_utils_color.c
int		get_rgb(int r, int g, int b);
int		get_r(int rgb);
int		get_g(int rgb);
int		get_b(int rgb);

//	fractol_utils_color2.c
int		get_gradient(int color1, int color2, float ratio);

//	fractol_colors_check.c
int		is_valid_line(char *line);

//	fractol_colors_decode.c
t_color	*decode_colors(char *file);

//	fractol_utils.c
int		pendulum(int len, int val);
void	print_info(t_fract data);

//	fractol_utils_list.c
void	fractol_lstadd(t_color **lst, t_color *new);

#endif
