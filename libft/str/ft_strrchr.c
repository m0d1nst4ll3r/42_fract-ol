/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 22:50:50 by rpohlen           #+#    #+#             */
/*   Updated: 2021/12/05 21:37:55 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t	i;

	if (! str)
		return (NULL);
	i = ft_strlen(str) + 1;
	while (i > 0)
	{
		i--;
		if (str[i] == (unsigned char)c)
			return ((char *)str + i);
	}
	return (NULL);
}
