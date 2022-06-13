/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pendulum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 14:07:54 by rpohlen           #+#    #+#             */
/*   Updated: 2021/12/23 14:08:09 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* --------------------------------------------------------------------- *\
|		pendulum
|	
|	For an array of length len, returns a cycling value from start to
|		end, then end to start.
|
|	Examples :
|	for val equal to
|	0 1 2 3 4 5 6 7 8 9 10
|	- if len = 4
|	0 1 2 3 3 2 1 0 0 1 2
|	- if len = 2
|	0 1 1 0 0 1 1 0 0 1 1
|
|	This can be used to cycle through an array twice easily
\* --------------------------------------------------------------------- */
int	ft_pendulum(int len, int val)
{
	int	mod;

	mod = val % ((len + 1) * 2);
	if (mod > len)
		return (len * 2 - mod + 1);
	else
		return (mod);
}
