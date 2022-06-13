/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 21:33:30 by rpohlen           #+#    #+#             */
/*   Updated: 2021/12/05 21:10:04 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	itoa_recursive(char **new, long int n)
{
	if (n < 0)
	{
		*new = ft_realloc_byte(*new, '-');
		n = -n;
	}
	if (n > 9)
		itoa_recursive(new, n / 10);
	*new = ft_realloc_byte(*new, n % 10 + '0');
}

char	*ft_itoa(int n)
{
	char	*new;

	new = NULL;
	itoa_recursive(&new, n);
	return (new);
}
