/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_again.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aniouar <aniouar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 15:48:41 by aniouar           #+#    #+#             */
/*   Updated: 2023/02/19 15:57:07 by aniouar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_box_column(char *line)
{
	int	i;
	int	x;
	int	size;

	size = ft_strlen(line);
	i = left_space(line);
	x = right_space(line);
	while (i < x)
	{
		if (line[i] == '1' || line[i] == 32)
			i++;
	}
	if (i == x)
		return (1);
	return (0);
}

int	check_box(t_pars *pars)
{
	t_line		*current;
	int			size;
	int			status;

	status = 1;
	current = pars->lines;
	if (check_box_column(current->line) == 0)
		status = 0;
	while (current)
	{
		size = ft_strlen(current->line);
		if (!check_line(current->line))
			status = 0;
		if (current->next == 0)
		{
			if (check_box_column(current->line) == 0)
				status = 0;
		}
		if (status == 0)
			break ;
		current = current->next;
	}
	return (status);
}

void	clear_tab(t_pars *pars)
{
	t_line	*current;

	current = pars->lines;
	while (current)
	{
					current->line = clean_column_space(current->line);
					current = current->next;
	}
}

int	parse_column(char *s)
{
	int	size;

	size = ft_strlen(s);
	if (size > 1)
	{
		if (s[0] != '1' || s[size - 1] != '1')
			return (0);
	}
	else if (left_space(s) == size && size > 0)
		return (0);
	return (1);
}
