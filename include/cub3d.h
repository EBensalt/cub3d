/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aniouar <aniouar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:24:36 by ebensalt          #+#    #+#             */
/*   Updated: 2023/01/26 12:25:50 by aniouar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../src/get_next_line/get_next_line.h"
#include "../parsing/parser.h"
# include <mlx.h>
# include <fcntl.h>
# include <math.h> 

typedef struct s_mlx
{
	void	*init;
	void	*win;
	void	*img;
	int		w;
	int		h;
	int		i;
	int		j;
	double	player_x;
	double	player_y;
	double	player_an;
	char	**map;
}	t_mlx;

//char	**ft_split(char const *s, char c);
#endif