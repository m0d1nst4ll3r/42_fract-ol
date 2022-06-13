/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 13:54:34 by rpohlen           #+#    #+#             */
/*   Updated: 2021/12/22 13:54:22 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Checks if c is present in base str
// If it is, will return its position
// If it isn't, will return -1
static int	ft_is_in_base(char c, const char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (c == base[i])
			return (i);
		i++;
	}
	return (-1);
}

// Checks if string str is valid
// Validity requires :
// - length higher than 1
// - no non-printable character, or +, or -
// - no same character twice
// If string is not valid, it will return 0
// If string is of length 1, it will return 1
// If string is valid and length > 1, it will return length
static int	ft_check_base(const char *base)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (base[i])
	{
		if (base[i] <= 32 || base[i] == 127 || base[i] == '-' || base[i] == '+')
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
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	return (len);
}

int	ft_atoi_base(char *str, const char *base)
{
	int	i;
	int	neg;
	int	res;
	int	baselen;

	baselen = ft_check_base(base);
	if (baselen <= 1)
		return (0);
	neg = 1;
	i = 0;
	res = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg = -neg;
		i++;
	}
	while (ft_is_in_base(str[i], base) >= 0)
	{
		res = res * baselen + ft_is_in_base(str[i], base);
		i++;
	}
	return (res * neg);
}
