/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aniouar <aniouar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:34:52 by aniouar           #+#    #+#             */
/*   Updated: 2023/02/19 16:23:04 by aniouar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_walls(char *s)
{
	int	i;
	int	size;
	int	x;

	size = ft_strlen(s);
	if (size == 0)
		return (0);
	x = right_space(s);
	i = left_space(s);
	if (i != -1 && x != -1)
	{
		while (i <= x)
		{
			if (s[i] != '1' && s[i] != 32)
				throw_error("Error : map wall with spaces");
			i++;
		}
		return (1);
	}
	return (0);
}

int	copy_check_walls(char *s)
{
	int	i;
	int	size;
	int	x;

	size = ft_strlen(s);
	if (size == 0)
		return (0);
	x = right_space(s);
	i = left_space(s);
	if (i != -1 && x != -1)
	{
		while (i <= x)
		{
			if (s[i] != '1' && s[i] != 32)
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

int	check_line(char *s)
{
	int	i;
	int	size;
	int	x;

	size = ft_strlen(s);
	x = right_space(s);
	i = left_space(s);
	if (x != -1 && i != -1)
	{
		if ((x - i) == 0 && s[i] == '1')
			return (1);
		if (s[x] == '1' && s[i] == '1')
			return (1);
	}
	return (0);
}

void	checking_player(t_pars *pars, char c)
{
	if (pars->valid_player == 0)
	{
		pars->vision = malloc(2);
		pars->vision[0] = c;
		pars->vision[1] = '\0';
		pars->valid_player = 1;
	}
	else
		throw_error("Error : duplicated player");
}

int	check_medline(t_pars *pars, char *s)
{
	int	i;
	int	size;
	int	x;

	size = ft_strlen(s);
	x = right_space(s) + 1;
	i = left_space(s);
	if (check_line(s) == 0)
		return (0);
	while (i < x)
	{
		if (s[i] == 'N' || s[i] == 'S' || s[i] == 'W' || s[i] == 'E')
			checking_player(pars, s[i]);
		else if (s[i] == 32)
			;
		else if (!(s[i] == '0' || s[i] == '1'))
			return (0);
		i++;
	}
	return (1);
}
