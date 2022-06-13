/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 01:08:16 by rpohlen           #+#    #+#             */
/*   Updated: 2021/11/22 18:27:56 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	size_t	i;
	char	*new;

	new = malloc((size + 1) * sizeof(*new));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (i < size + 1)
	{
		new[i] = 0;
		i++;
	}
	return (new);
}
