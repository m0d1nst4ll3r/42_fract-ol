/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 02:41:33 by rpohlen           #+#    #+#             */
/*   Updated: 2021/11/25 14:00:08 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//	If s only contains characters inside set
//	The new string will be empty
char	*ft_strtrim(const char *s, const char *set)
{
	size_t	end;
	size_t	start;

	if (s == NULL || set == NULL)
		return (NULL);
	start = 0;
	while (s[start] && ft_strchr(set, s[start]))
		start++;
	if (! s[start])
		return (ft_strdup(""));
	end = ft_strlen(s);
	while (end > 0 && ft_strchr(set, s[end]))
		end--;
	return (ft_substr(s, start, end - start + 1));
}
