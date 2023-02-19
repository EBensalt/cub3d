/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aniouar <aniouar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 15:39:46 by aniouar           #+#    #+#             */
/*   Updated: 2023/02/19 16:13:07 by aniouar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	parse_color(t_pars *pars, char *s)
{
	int	size;

	(void)pars;
	size = ft_strlen(s);
	if (size > 1)
	{
		if (s[0] == ',' || s[size - 1] == ',')
			throw_error("Error : Invalid Color 103");
	}
}

void	free_array(char **tab, int count)
{
	int	i;

	i = -1;
	while (++i < count)
		free(tab[i]);
	free(tab);
}
