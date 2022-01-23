/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_colors_check.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 15:10:24 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/22 23:01:06 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* -------------------------------------------------------------------- *\
|		is_valid_hex
|
|	Checks whether the string starting at the first hexadecimal digit
|		is composed of 6 hexadecimal digits followed by a whitespace or 0
|
|	If not, returns 0
|
|	Examples of valid hex: 7f7f7f 8901e2 000000 05e1a8
|
|	Used to check validity of hex color values in the colors config file
\* -------------------------------------------------------------------- */
static int	is_valid_hex(char *line)
{
	int	count;

	count = 0;
	while (ft_ishex(*line))
	{
		count++;
		line++;
	}
	if (count == 6 && (ft_isspace(*line) || *line == 0))
		return (1);
	return (0);
}

/* -------------------------------------------------------------------- *\
|		step_check
|
|	Checks validity of string step by step according to a set of rules.
|
|	Steps :
|	0	Skipping whitespaces, looking for a printable character
|	1	Skipping printables, looking for whitespace
|	2	Skipping whitespaces and 0's, looking for a 0 or digit
|	3	Skipping 0's, looking for a non-0 digit
|	4	Skipping numbers, looking for whitespace
|	5	Skipping whitespaces, looking for a hexadecimal
|	6	Check validity of hex number (exactly 6 digits)
|	7	Skipping whitespaces, looking for a hexadecimal
|	8	Check validity of hex number (exactly 6 digits)
|	9	Skipping whitespaces, looking for a hexadecimal
|		-> back to 8
|
|	A step less than 8 means the line is incomplete.
|	The index has to be incremented by 6 after steps 6 and 8.
|
|	Note that this could be done much more efficiently if we would
|		program a function that can dynamically check syntax based
|		on a set of rules.
|
|	Such a function could, for example, take as input something like :
|
|	(space)[non-space printable][space](0 digit)[non-0 digit][space] \
|		<6hex>[space]<6hex>(space)(6hex)-repeatlast2
|
|	[] being at least one, () being any amount, <> being a set amount
|	(yes this is a very rough first draft)
|
|	Such a program would make it effortless to check for syntax and
|		avoid if forests.
|
|	BUT... someone needs to code it. NOT IT!
\* -------------------------------------------------------------------- */
static int	step_check2(char c, int *step)
{
	if (*step == 5 && ft_ishex(c))
		*step = 6;
	else if (*step == 5 && !ft_isspace(c))
		return (0);
	else if (*step == 7 && ft_ishex(c))
		*step = 8;
	else if (*step == 7 && !ft_isspace(c))
		return (0);
	else if (*step == 9 && ft_ishex(c))
		*step = 8;
	else if (*step == 9 && !ft_isspace(c))
		return (0);
	return (1);
}

//	I am become the god of ifs
static int	step_check(char c, int *step)
{
	if (*step == 0 && c != ' ' && c != '#' && ft_isprint(c))
		*step = 1;
	else if (*step == 0 && !ft_isspace(c))
		return (0);
	else if (*step == 1 && ft_isspace(c))
		*step = 2;
	else if (*step == 1 && !ft_isprint(c))
		return (0);
	else if (*step == 2 && c == '0')
		*step = 3;
	else if (*step == 2 && ft_isdigit(c))
		*step = 4;
	else if (*step == 2 && !ft_isspace(c))
		return (0);
	else if (*step == 3 && c != '0' && ft_isdigit(c))
		*step = 4;
	else if (*step == 3 && c != '0')
		return (0);
	else if (*step == 4 && ft_isspace(c))
		*step = 5;
	else if (*step == 4 && !ft_isdigit(c))
		return (0);
	else
		return (step_check2(c, step));
	return (1);
}

/* -------------------------------------------------------------------- *\
|		is_valid_line
|
|	With the help of our 9 steps program, YOU TOO can figure out
|		whether a line from your colors config file is utter rubbish!
|
|	You will only have to skip whitespaces, make sure there's at least
|		1 character to describe the palette's name and its size (which
|		can't only be zeroes, of course!), and that there are at least
|		2 valid hexadecimal values to describe the start and end colors
|
|	(We deny any responsibility in case of horrible and catastrophic
|		failure resulting in the possible crash of your program,
|		destruction of your PC, house, and/or slow agonizing death
|		of everyone you hold dear)
|
|	(Used in fract_colors_decode2.c)
\* -------------------------------------------------------------------- */
int	is_valid_line(char *line)
{
	int	step;

	step = 0;
	while (*line)
	{
		if (step != 6 && step != 8 && !step_check(*line, &step))
			return (0);
		else if (step == 6 || step == 8)
		{
			if (is_valid_hex(line))
			{
				if (step == 6)
					step = 7;
				else
					step = 9;
				line += 5;
			}
			else
				return (0);
		}
		line++;
	}
	if (step >= 8)
		return (1);
	return (0);
}
