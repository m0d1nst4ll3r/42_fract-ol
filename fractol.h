/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 14:53:40 by rpohlen           #+#    #+#             */
/*   Updated: 2021/12/18 14:50:38 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

//	This is placeholder, I will have to code in parameters
# define WIN_X 1800
# define WIN_Y 1000
# define STEP 0.0025
# define ZOOM 4
# ifndef DEPTH
#  define DEPTH 1
# endif

# include "mlx/mlx.h"
# include <stdlib.h>
# include <math.h>
# include <stdio.h>

typedef struct s_fract
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			end;
	int			llen;
	long double		posx;
	long double		posy;
	long double		step;
	int			depth;
	int			*palette;
	int			palette_size;
}				t_fract;

#endif
