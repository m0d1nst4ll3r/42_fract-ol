/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 01:32:40 by rpohlen           #+#    #+#             */
/*   Updated: 2021/11/24 19:58:03 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//	Error cases:
//
//	Return NULL if:
//		- the string is a NULL pointer
//		- the malloc failed
//
//	Return an empty string if:
//		- the start index is not inside of s
//
//	However, if start is inside of s but len goes beyond s, len will be
//		readjusted so that it stays within s.
//	This possibly means len will be set to 0, still resulting in
//		an empty string.
char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	slen;

	if (s == NULL)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
	{
		start = 0;
		len = 0;
	}
	else if (start + len > slen)
		len = slen - start;
	new = malloc((len + 1) * sizeof(*new));
	if (new == NULL)
		return (NULL);
	ft_strlcpy(new, s + start, len + 1);
	return (new);
}
