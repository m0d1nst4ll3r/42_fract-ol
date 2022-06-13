/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 22:50:18 by rpohlen           #+#    #+#             */
/*   Updated: 2021/12/05 21:17:37 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	if (! str)
		return (NULL);
	while (*str)
		if (*(str++) == (unsigned char)c)
			return ((char *)str - 1);
	if (*str == c)
		return ((char *)str);
	return (NULL);
}
