/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aniouar <aniouar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:47:15 by aniouar           #+#    #+#             */
/*   Updated: 2023/02/19 16:08:28 by aniouar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	fill_lines(t_pars *pars, char *s)
{
	int						size;
	t_line					*new;

	size = ft_strlen(s);
	if (pars->valid_map == 1 && pars->start_map == 1 && size > 0)
	{
		if (pars->prev_line == 0)
		{
						pars->lines = malloc(sizeof(t_line));
						pars->lines->line = ft_strdup(s);
						pars->lines->next = 0;
						pars->lines->prev = 0;
						pars->prev_line = pars->lines;
		}
		else
		{
						new = malloc(sizeof(t_line));
						new->line = ft_strdup(s);
						new->prev = pars->prev_line;
						new->next = 0;
						pars->prev_line->next = new;
						pars->prev_line = new;
		}
	}
}

int	check_last(t_pars *pars)
{
	t_line	*current;

	current = pars->lines;
	while (current->next != 0)
		current = current->next;
	if (current)
	{
		if (copy_check_walls(current->line))
			return (1);
	}
	return (0);
}

int	check_after_valid(char *s)
{
	int	i;
	int	size;

	size = ft_strlen(s);
	i = -1;
	while (s[++i] == 32)
		;
	if (i == size)
		return (1);
	return (0);
}

void	check_errors_map(t_pars *pars, int status, char *s)
{
	(void)s;
	if (status == 1 && pars->start_map == 0)
					pars->start_map = 1;
	if (status == 0 && pars->start_map == 1)
	{
		if (!(check_after_valid(s) && check_last(pars)))
			throw_error("Error : Invalid Map 108");
		else
			pars->end_map = 1;
	}
	if (status && pars->end_map)
		throw_error("Error : Invalid Map 108");
}

void	map_check(t_pars *pars, char *s)
{
	int	status;

	status = 1;
	if (pars->start_map == 0)
	{
		if (check_walls(s) == 0)
			status = 0;
		if (status)
			pars->start_map = 1;
	}
	else
	{
		if (check_medline(pars, s) == 0)
			status = 0;
	}
	check_errors_map(pars, status, s);
	if (status)
		fill_lines(pars, s);
}
