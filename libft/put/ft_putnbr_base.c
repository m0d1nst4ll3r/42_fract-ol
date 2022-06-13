/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 13:03:36 by rpohlen           #+#    #+#             */
/*   Updated: 2021/12/22 13:53:59 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

// Returns n to the power of e
static int	ft_power(int n, int e)
{
	int	r;

	if (e <= 0)
		return (1);
	r = n;
	while (e > 1)
	{
		r = r * n;
		e--;
	}
	return (r);
}

// Get number of digits of int n in base b
static int	ft_count_digits(int n, int b)
{
	int	size;

	if (b <= 1)
		return (0);
	size = 0;
	if (n == 0)
		size = 1;
	while (n != 0)
	{
		n = n / b;
		size++;
	}
	return (size);
}

// Checks if string str is valid
// Validity requires :
// - length higher than 1
// - no non-printable character, or +, or -
// - no same character twice
// If string is not valid, it will return 0
// If string is of length 1, it will return 1
// If string is valid and length > 1, it will return length
static int	ft_check_base(const char *str)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	while (str[i])
	{
		if (str[i] <= 32 || str[i] == 127 || str[i] == '-' || str[i] == '+')
			return (0);
		i++;
	}
	len = i;
	i = 0;
	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if (str[i] == str[j])
				return (0);
			j++;
		}
		i++;
	}
	return (len);
}

// Displays int nbr in base base
void	ft_putnbr_base(int nbr, const char *base)
{
	int	digit;
	int	neg;
	int	size;
	int	len;

	len = ft_check_base(base);
	if (len <= 1)
		return ;
	size = ft_count_digits(nbr, len);
	neg = 1;
	if (nbr < 0)
	{
		neg = -1;
		write(1, "-", 1);
	}
	while (size > 0)
	{
		digit = nbr / ft_power(len, size - 1);
		write(1, base + (neg * digit), 1);
		nbr = nbr - digit * ft_power(len, size - 1);
		size--;
	}
}
