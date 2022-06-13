/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_byte.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 21:22:34 by rpohlen           #+#    #+#             */
/*   Updated: 2021/11/24 19:01:49 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc_byte(char *old, char c)
{
	size_t	len;
	char	*new;

	len = 0;
	if (old != NULL)
		len = ft_strlen(old);
	new = ft_strnew(len + 2);
	if (new == NULL)
		return (NULL);
	if (old != NULL)
	{
		ft_strcpy(new, old);
		free(old);
	}
	new[len] = c;
	new[len + 1] = 0;
	return (new);
}
