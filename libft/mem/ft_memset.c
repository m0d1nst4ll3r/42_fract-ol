/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 23:14:27 by rpohlen           #+#    #+#             */
/*   Updated: 2021/12/05 21:16:30 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t		i;
	char		*array;

	if (! s)
		return (NULL);
	i = 0;
	array = (char *)s;
	while (i < n)
	{
		array[i] = (const char)c;
		i++;
	}
	return (s);
}
