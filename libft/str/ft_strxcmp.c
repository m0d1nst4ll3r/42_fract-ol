/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strxcmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:16:19 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/05 16:07:59 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* --------------------------------------------------------------------- *\
|		ft_strxcmp
|
|	Checks for partial completion.
|
|	If [partial] is a partial copy of [complete], returns 0, else 1.
|
|	Note that an empty string causes a 0 return, as it is not counted
|		as a partial copy.
|
|	Examples :
|
|	"long" + "l"		= 1
|	"long" + "lo"		= 1
|	"long" + "lon"		= 1
|	"long" + "long"		= 1
|	"long" + "longa"	= 0
|	"long" + "lol"		= 0
|	"long" + "along"	= 0
|	"long" + "o"		= 0
|	"long" + ""			= 0
\* --------------------------------------------------------------------- */
int	ft_strxcmp(const char *complete, const char *partial)
{
	if (!complete || !partial)
		return (0);
	if (!*partial)
		return (0);
	while (*complete && *partial)
	{
		if (*complete != *partial)
			break ;
		complete++;
		partial++;
	}
	if (*partial && *complete != *partial)
		return (1);
	return (0);
}
