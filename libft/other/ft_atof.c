/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 17:01:45 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/07 22:32:45 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static float	ft_atof_integer(const char *s, size_t *i)
{
	float	integer;

	integer = 0;
	while (ft_isdigit(s[*i]))
	{
		integer = integer * 10 + s[*i] - '0';
		(*i)++;
	}
	return (integer);
}

static float	ft_atof_rational(const char *s, size_t *i)
{
	size_t	j;
	float	rational;

	j = *i;
	rational = 0;
	while (ft_isdigit(s[*i]))
	{
		rational = rational * 10 + s[*i] - '0';
		(*i)++;
	}
	return (rational / ft_fpow(10, *i - j));
}

//	'.5' will be considered valid and cause a return of '0.5'
//	The number returned is the best possible representation in float
//		of the number represented in the string. It may not be the exact
//		same due to floating point limitations.
float	ft_atof(const char *s)
{
	size_t	i;
	float	rational;
	float	integer;
	int		neg;

	if (!s || !ft_isfloat(s))
		return (0);
	neg = 0;
	i = 0;
	if (s[i] == '-')
	{
		neg = 1;
		i++;
	}
	integer = ft_atof_integer(s, &i);
	rational = 0;
	if (s[i])
	{
		i++;
		rational = ft_atof_rational(s, &i);
	}
	if (neg)
		return (-1 * (integer + rational));
	return (integer + rational);
}
