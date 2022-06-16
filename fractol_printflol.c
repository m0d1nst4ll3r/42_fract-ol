/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_printflol.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:13:57 by rpohlen           #+#    #+#             */
/*   Updated: 2022/06/13 14:01:38 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* --------------------------------------------------------------------- *\
|		print_float print_double print_ld
|
|	Fuck 42 and their ninja subject edits.
|
|	I used printf to print floats etc... cause it was allowed.
|
|	Now suddenly it's not and I have to use my own printf but I never
|		accounted for this and my printf doesn't print floats.
|
|	So I have to resort to dirty tricks cause I need to turn this in now.
|
|	I'm sorry to anyone who has to see this.
|
|	Btw these functions don't print the exact value of the float/ld.
\* --------------------------------------------------------------------- */
void	print_float(float f, int length)
{
	f += 0.005;
	ft_printf("%d", (int)f);
	if (f < 0)
		f *= -1;
	if (length > 0)
		ft_printf(".");
	while (length-- > 0)
	{
		f *= 10;
		f -= (int)f / 10 * 10;
		ft_printf("%d", (int)f % 10);
	}
}

void	print_ld(long double ld, int length)
{
	ft_printf("%d", (int)ld);
	if (ld < 0)
		ld *= -1;
	if (length > 0)
		ft_printf(".");
	while (length-- > 0)
	{
		ld *= 10;
		ld -= (int)ld / 10 * 10;
		ft_printf("%d", (int)ld % 10);
	}
}
