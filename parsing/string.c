/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aniouar <aniouar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:31:48 by aniouar           #+#    #+#             */
/*   Updated: 2023/02/19 16:23:47 by aniouar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_cleanline(char *s)
{
	int	i;
	int	pos;
	int	size;

	pos = -1;
	size = ft_strlen(s);
	i = -1;
	while (++i < size)
	{
		if (s[i] == '\n')
		{
			pos = i;
			break ;
		}
	}
	if (pos != -1)
		s[pos] = '\0';
}

int	count_char(char c, char *s)
{
	int	i;
	int	count;

	count = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == c)
			count++;
	}
	return (count);
}

int	n_powtwo(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (count_char(s[i], s) != 1)
			return (0);
	}
	return (1);
}

int	valid_number(char *rgb)
{
	int	i;
	int	size;

	size = ft_strlen(rgb);
	i = 0;
	while (rgb[i] >= '0' && rgb[i] <= '9')
		i++;
	if (i == size)
		return (1);
	return (0);
}

int	check_num(int *colors, char **rgb, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		if (valid_number(rgb[i]) == 0)
			return (0);
		if (!(colors[i] >= 0 && colors[i] <= 255))
			return (0);
	}
	return (1);
}
