/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aniouar <aniouar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 15:44:25 by aniouar           #+#    #+#             */
/*   Updated: 2023/02/19 16:17:02 by aniouar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*clean_column_space(char *s)
{
	int				pos;
	size_t			size;
	char			*tmp;

	pos = ft_strpos_flex(s);
	size = ft_strlen(s);
	tmp = ft_substr(s, (pos), size, 0);
	pos = ft_strpos_flex(tmp);
	free(s);
	return (tmp);
}

void	set_sizes(t_line *line, int *sizeprev, int *sizenext)
{
	if (line->prev != 0)
		*sizeprev = ft_strlen(line->prev->line);
	else
		*sizeprev = -1;
	if (line->next != 0)
		*sizenext = ft_strlen(line->next->line);
	else
		*sizenext = -1;
}

void	check_left_right(t_line *line, int index)
{
	int		sizeline;
	char	c;

	sizeline = ft_strlen(line->line);
	c = line->line[index];
	if (c == '0')
	{
		if (line->line[index + 1] == 32 || line->line[index - 1] == 32)
			throw_error("Error: Invalid map");
	}
}

int	*get_square(t_line *line, int index)
{
	int	*square;
	int	sizeline;

	square = malloc(sizeof(int) * 2);
	if (line->prev == 0)
				square[0] = -1;
	else
	{
		sizeline = ft_strlen(line->prev->line);
		if (index < sizeline)
			square[0] = line->prev->line[index];
		else
			square[0] = -1;
	}
	if (line->next == 0)
				square[1] = -1;
	else
	{
		if (index < (int)ft_strlen(line->next->line))
						square[1] = line->next->line[index];
		else
						square[1] = -1;
	}
	check_left_right(line, index);
	return (square);
}

int	check_point(t_pars *pars, int c, int mod)
{
	if (mod == 0)
	{
		if (pars->vision)
			if (c == pars->vision[0])
				return (1);
		if (c == '0' || c == '1')
			return (1);
	}
	else
		if (c == '0' || c == pars->vision[0])
			return (1);
	return (0);
}
