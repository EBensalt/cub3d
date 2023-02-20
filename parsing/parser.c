/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:05:07 by aniouar           #+#    #+#             */
/*   Updated: 2023/02/20 06:30:22 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	more_parser(t_pars *pars)
{
	validate(pars);
	square_box(pars);
	if (pars->lines != 0)
	{
		if (check_box(pars) == 0)
			throw_error("Error : Invalid map");
	}
	fill_map_lines(pars);
	free_map_list(pars);
}

void	core_parser(t_pars *pars, char *s)
{
	if (!pars->valid_direction || !pars->valid_color)
	{
		fill_color(pars, s);
		fill_texture(pars, s);
	}
	else if (pars->valid_direction && pars->valid_color)
		map_check(pars, s);
}

t_pars	*parser(char *filecub)
{
	int				fd;
	int				i;
	char			*search;
	char			*s;
	t_pars			*pars;

	pars = malloc(sizeof(t_pars));
	init_pars(pars);
	fd = open(filecub, O_RDONLY);
	search = ft_strstr(filecub, ".cub");
	if (fd == -1 || search == 0)
		throw_error("Error : invalid map file");
	i = 0;
	s = get_next_line(fd);
	while (s)
	{
		ft_cleanline(s);
		core_parser(pars, s);
		free(s);
		s = get_next_line(fd);
	}
	more_parser(pars);
	return (pars);
}
