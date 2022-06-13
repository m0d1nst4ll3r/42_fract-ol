/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 15:57:21 by rpohlen           #+#    #+#             */
/*   Updated: 2021/11/25 16:59:15 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	long unsigned int	mult;
	void				*new;

	mult = nmemb * size;
	if (mult > 0xffffffff)
		return (NULL);
	new = malloc(mult);
	if (! new)
		return (NULL);
	ft_bzero(new, mult);
	return (new);
}
