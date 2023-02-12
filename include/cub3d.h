/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:24:36 by ebensalt          #+#    #+#             */
/*   Updated: 2023/02/09 22:36:40 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../src/get_next_line/get_next_line.h"
# include "../parsing/parser.h"
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
	double	hight;
	double	ray;
	int		move_up;
	int		move_side;
	int		arrow;
	char	**map;
}	t_mlx;

char	**ft_split(char const *s, char c);
#endif