/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 01:01:22 by rpohlen           #+#    #+#             */
/*   Updated: 2021/11/24 15:46:29 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	size_t	i;
	void	*new;

	new = malloc(size);
	if (new == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		((char *)new)[i] = 0;
		i++;
	}
	return (new);
}
