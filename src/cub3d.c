/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:24:59 by ebensalt          #+#    #+#             */
/*   Updated: 2023/02/20 06:25:05 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_mlx	*map_dem(t_mlx *mlx)
{
	int	x;
	int	y;
	int	i;

	x = -1;
	i = 0;
	while (mlx->pars->map[++x])
	{
		i = -1;
		while (mlx->pars->map[x][++i])
			;
		if (i > y)
			y = i;
	}
	mlx->i = y;
	mlx->j = x;
	mlx->win_x = 34;
	mlx->win_y = 19;
	return (mlx);
}

int	main(int ac, char **av)
{
	t_mlx	*mlx;

	if (ac != 2)
		throw_error("wrong number of arguments");
	mlx = malloc(sizeof(t_mlx));
	mlx->pars = parser(av[1]);
	mlx->init = mlx_init();
	mlx = map_dem(mlx);
	mlx->win = mlx_new_window(mlx->init, (mlx->win_x * 50),
			(mlx->win_y * 50), "cub3D");
	t3d_map(mlx);
	mlx_loop(mlx->init);
}
