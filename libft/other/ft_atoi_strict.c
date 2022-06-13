/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_strict.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 18:26:28 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/28 07:41:13 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* --------------------------------------------------------------------- *\
|		ft_atoi_strict
|
|	Works like regular atoi, except it only accepts numbers, and it
|		recognizes overflows.
|
|	A number is defined as an optional '-' and then only digits,
|		no spaces, no plusses, no empty strings.
|
|	When a bad format or overflow is detected, return 1.
|
|	Because of the error return, the number is passed as reference.
\* --------------------------------------------------------------------- */
int	ft_atoi_strict(const char *s, int *n)
{
	char	neg;

	if (!s || !n || !*s)
		return (1);
	neg = 1;
	*n = 0;
	if (*s == '-')
	{
		neg = -1;
		s++;
	}
	while (*s && (*s ^ '0') < 10)
	{
		if (*n != (int)((unsigned int)*n * 10) / 10)
			return (1);
		*n = *n * 10 + *s - '0';
		if (*n && (*n - (neg < 0)) < 0)
			return (1);
		s++;
	}
	if (*s)
		return (1);
	*n = neg * *n;
	return (0);
}
