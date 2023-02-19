/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aniouar <aniouar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 15:51:24 by aniouar           #+#    #+#             */
/*   Updated: 2023/02/19 16:20:36 by aniouar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_pars(t_pars *pars)
{
	pars->valid_direction = 0;
	pars->valid_map = 1;
	pars->end_map = 0;
	pars->start_map = 0;
	pars->valid_color = 0;
	pars->vision = 0;
	pars->color_floor = -1;
	pars->valid_player = 0;
	pars->color_c = -1;
	pars->dir_texture = malloc(sizeof(t_dir_texture));
	pars->dir_texture->valid_fill = ft_strdup("");
	pars->dir_texture->no = 0;
	pars->dir_texture->so = 0;
	pars->dir_texture->we = 0;
	pars->dir_texture->ea = 0;
	pars->map = 0;
	pars->lines = 0;
	pars->prev_line = 0;
}

void	validate(t_pars *pars)
{
	validate_texture(pars, pars->dir_texture->no);
	validate_texture(pars, pars->dir_texture->we);
	validate_texture(pars, pars->dir_texture->ea);
	validate_texture(pars, pars->dir_texture->so);
	if (pars->valid_direction == 0)
		throw_error("Error : Invalid texture");
	if (pars->valid_color == 0)
		throw_error("Error : Invalid Color");
	if (pars->start_map == 0)
		throw_error("Error : Invalid Map");
	if (pars->valid_player == 0)
		throw_error("Error : Invalid Player");
}

int	get_count(t_line *line)
{
	t_line	*current;
	int		count;

	count = 0;
	current = line;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

void	fill_map_lines(t_pars *pars)
{
	int				count;
	int				i;
	t_line			*current;

	count = get_count(pars->lines);
	pars->map = malloc(sizeof(char *) * (count + 1));
	current = pars->lines;
	i = 0;
	while (current)
	{
					pars->map[i++] = ft_strdup(current->line);
					current = current->next;
	}
	pars->map[i] = 0;
}

void	free_map_list(t_pars *pars)
{
	t_line	*current;

	current = pars->lines;
	while (current)
	{
		free(current->line);
		current = current->next;
	}
}
