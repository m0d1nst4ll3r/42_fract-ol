/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 00:14:20 by rpohlen           #+#    #+#             */
/*   Updated: 2021/12/05 21:15:04 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*ar1;
	const unsigned char	*ar2;

	if (s1 == NULL || s2 == NULL || n == 0)
		return (0);
	i = 0;
	ar1 = (const unsigned char *)s1;
	ar2 = (const unsigned char *)s2;
	while (i < n - 1 && ar1[i] == ar2[i])
		i++;
	return (ar1[i] - ar2[i]);
}
