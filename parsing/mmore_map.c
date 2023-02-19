/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmore_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aniouar <aniouar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 15:45:51 by aniouar           #+#    #+#             */
/*   Updated: 2023/02/19 16:11:17 by aniouar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	check_first(t_pars *pars, t_line *line, int *square)
{
	if (line->prev == 0)
	{
		if (check_point(pars, square[1], 0) == 0)
			throw_error("Error : Invalid Map 101");
	}
}

void	check_med(t_pars *pars, t_line *line, int *square)
{
	if (line->prev != 0 && line->next != 0)
	{
		if (check_point(pars, square[0], 0) == 0)
			throw_error("Error : Invalid Map 103");
		if (check_point(pars, square[1], 0) == 0)
			throw_error("Error : Invalid Map 104");
	}
}

void	check_bottom(t_pars *pars, t_line *line, int *square)
{
	if (line->next == 0)
	{
		if (check_point(pars, square[0], 0) == 0)
			throw_error("Error : Invalid Map 105");
	}
}

void	square_box(t_pars *pars)
{
	t_line			*current;
	int				i;
	int				x;
	int				*square;

	current = pars->lines;
	while (current)
	{
		i = left_space(current->line);
		x = right_space(current->line);
		while (i++ <= x)
		{
			if (check_point(pars, current->line[i], 1))
			{
				square = get_square(current, i);
				check_first(pars, current, square);
				check_med(pars, current, square);
				check_bottom(pars, current, square);
				free(square);
			}
		}
		if (pars->valid_color == 0)
			break ;
		current = current->next;
	}
}

int	check_map_line(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (!(s[i] == '0' || s[i] == '+'))
			return (0);
	}
	return (1);
}
