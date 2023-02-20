/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 06:10:41 by ebensalt          #+#    #+#             */
/*   Updated: 2023/02/20 06:11:22 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_mlx	*init_game_utils(t_mlx *mlx, int i, int j)
{
	mlx->player_x = (j * 50) + 25;
	mlx->player_y = (i * 50) + 25;
	if (mlx->pars->map[i][j] == 'N')
		mlx->player_an = (3 * M_PI) / 2;
	if (mlx->pars->map[i][j] == 'S')
		mlx->player_an = M_PI / 2;
	if (mlx->pars->map[i][j] == 'E')
		mlx->player_an = 0;
	if (mlx->pars->map[i][j] == 'W')
		mlx->player_an = M_PI;
	return (mlx);
}

t_mlx	*init_game(t_mlx *mlx)
{
	int	i;
	int	j;

	i = -1;
	while (mlx->pars->map[++i])
	{
		j = 0;
		while (mlx->pars->map[i][j])
		{
			if (mlx->pars->map[i][j] == ' ' || mlx->pars->map[i][j] == '1'
				|| mlx->pars->map[i][j] == '0')
				j++;
			else
			{
				mlx = init_game_utils(mlx, i, j);
				break ;
			}
		}
	}
	mlx = init_tex(mlx);
	map_draw(mlx);
	return (mlx);
}

int	handler(int key, t_mlx *mlx)
{
	if (key == 13)
		mlx->move_up = 1;
	if (key == 0)
		mlx->move_side = 1;
	if (key == 1)
		mlx->move_up = -1;
	if (key == 2)
		mlx->move_side = -1;
	if (key == 123)
		mlx->arrow = -1;
	if (key == 124)
		mlx->arrow = 1;
	if (key == 53)
		exit(0);
	return (0);
}

void	handler_test_utils(t_mlx *mlx, double x, double y)
{
	if (mlx->move_side == -1)
	{
		x += 10 * cos(mlx->player_an + (M_PI / 2));
		y += 10 * sin(mlx->player_an + (M_PI / 2));
	}
	if (mlx->arrow < 0)
		mlx->player_an -= 10 *(M_PI / 180);
	if (mlx->arrow > 0)
		mlx->player_an += 10 *(M_PI / 180);
	if (mlx->pars->map[(int)((y + 10) / 50)][(int)((x) / 50)] != '1'
		&& mlx->pars->map[(int)((y - 10) / 50)][(int)((x) / 50)] != '1'
		&& mlx->pars->map[(int)((y) / 50)][(int)((x + 10) / 50)] != '1'
		&& mlx->pars->map[(int)((y) / 50)][(int)((x - 10) / 50)] != '1')
	{
		mlx->player_x = x;
		mlx->player_y = y;
	}
	if (mlx->move_up != 0 || mlx->move_side != 0 || mlx->arrow != 0)
	{
		mlx_clear_window(mlx->init, mlx->win);
		map_draw(mlx);
	}
}

int	handler_test(t_mlx *mlx)
{
	double	x;
	double	y;

	x = mlx->player_x;
	y = mlx->player_y;
	if (mlx->move_up == 1)
	{
		x += 10 * cos(mlx->player_an);
		y += 10 * sin(mlx->player_an);
	}
	if (mlx->move_up == -1)
	{
		x -= 10 * cos(mlx->player_an);
		y -= 10 * sin(mlx->player_an);
	}
	if (mlx->move_side == 1)
	{
		x -= 10 * cos(mlx->player_an + (M_PI / 2));
		y -= 10 * sin(mlx->player_an + (M_PI / 2));
	}
	handler_test_utils(mlx, x, y);
	return (0);
}
