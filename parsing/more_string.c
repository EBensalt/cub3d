/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aniouar <aniouar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:48:13 by aniouar           #+#    #+#             */
/*   Updated: 2023/02/19 16:21:03 by aniouar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	count_delimiter(char *s, char lim)
{
	int	i;
	int	count;

	count = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == lim)
			count++;
	}
	return (count);
}

int	ft_strpos_flex(char *s)
{
	int	i;

	i = -1;
	while (s[i] == 32 || s[i] == '\t' || s[i] == '\r')
		i++;
	return (i);
}

int	left_space(char *s)
{
	int	i;
	int	size;

	size = ft_strlen(s);
	if (size == 0)
		return (-1);
	i = 0;
	while (s[i] == 32)
		i++;
	return (i);
}

int	right_space(char *s)
{
	int	x;
	int	size;

	size = ft_strlen(s);
	if (size == 0)
		return (-1);
	x = size - 1;
	while (s[x] == 32)
	{
		x--;
		if (x < 0)
			break ;
	}
	return (x);
}

void	throw_error(char *s)
{
	printf("%s\n", s);
	exit (0);
}
