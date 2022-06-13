/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 13:32:15 by rpohlen           #+#    #+#             */
/*   Updated: 2021/12/05 21:15:54 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memdup(const void *s, size_t n)
{
	void	*new;

	if (! s)
		return (NULL);
	new = malloc(n * sizeof(*new));
	if (new == NULL)
		return (NULL);
	ft_memcpy(new, s, n);
	return (new);
}
