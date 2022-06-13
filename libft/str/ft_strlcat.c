/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 22:35:01 by rpohlen           #+#    #+#             */
/*   Updated: 2021/12/05 21:21:51 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	i;

	if (dest == NULL || src == NULL)
		return (0);
	srclen = ft_strlen(src);
	dstlen = 0;
	while (dstlen < n && dest[dstlen])
		dstlen++;
	if (dstlen + 2 > n)
		return (dstlen + srclen);
	i = 0;
	while (dstlen + i < n - 1 && src[i])
	{
		dest[dstlen + i] = src[i];
		i++;
	}
	dest[dstlen + i] = 0;
	return (dstlen + srclen);
}
