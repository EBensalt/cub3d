/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:30:02 by aniouar           #+#    #+#             */
/*   Updated: 2023/02/20 06:30:51 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	check_set_color(t_pars *pars, char **colors, char **rgb, int typo)
{
	int		color;
	int		*tab;

	tab = malloc(sizeof(int) * 3);
	tab[0] = atoi(rgb[0]);
	tab[1] = atoi(rgb[1]);
	tab[2] = atoi(rgb[2]);
	if (check_num(tab, rgb, 3) == 0 || count_delimiter(colors[1], ',') != 2)
		throw_error("Error : Invalid Color");
	color = (tab[0] << 16) | (tab[1] << 8) | tab[2];
	if (typo == 0)
					pars->color_floor = color;
	else
					pars->color_c = color;
	free(tab);
}

void	set_color(t_pars *pars, char **colors, int typo)
{
	int		count;
	char	**rgb;

	parse_color(pars, colors[1]);
	rgb = ft_split_new(colors[1], ',', &count);
	if (count == 3)
		check_set_color(pars, colors, rgb, typo);
	free_array(rgb, count);
}

void	catch_colors(char **colors, int count, t_pars *pars)
{
	if (ft_strcmp(colors[0], "F") == 0 && count == 2)
	{
		if (pars->color_floor != -1)
			throw_error("Error : Duplicated Color");
		else
			set_color(pars, colors, 0);
	}
	if (ft_strcmp(colors[0], "C") == 0 && count == 2)
	{
		if (pars->color_c != -1)
			throw_error("Error : Duplicated Color");
		else
			set_color(pars, colors, 1);
	}
}

void	fill_color(t_pars *pars, char *s)
{
	char	**colors;
	int		count;
	int		i;

	if (pars->valid_color)
		return ;
	colors = ft_split_new(s, 32, &count);
	catch_out_head(pars, colors[0]);
	if (count == 2)
	{
		if (ft_strcmp(colors[0], s) == 0)
		{
			i = -1;
			while (++i < count)
				free(colors[i]);
			free(colors);
			return ;
		}
		catch_colors(colors, count, pars);
		if (pars->color_floor != -1 && pars->color_c != -1)
			pars->valid_color = 1;
	}
	free_array(colors, count);
}

void	catch_out_head(t_pars *pars, char *s)
{
	char	**match;
	int		i;
	int		x;

	(void)pars;
	x = 0;
	i = -1;
	match = ft_split("NO WE EA SO C F", 32);
	while (match[++i])
	{
		if (s)
		{
			if (ft_strcmp(match[i], s) == 0)
				x++;
		}
		free(match[i]);
	}
	if (s)
	{
		if (x == 0 && ft_strcmp(s, "") != 0)
			throw_error("Error : Invalid Color/Texture");
	}
	if (match)
		free (match);
}
