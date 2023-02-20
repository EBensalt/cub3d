/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 06:13:14 by ebensalt          #+#    #+#             */
/*   Updated: 2023/02/20 06:13:57 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	handler_test1(int key, t_mlx *mlx)
{
	if (key == 13)
		mlx->move_up = 0;
	if (key == 0)
		mlx->move_side = 0;
	if (key == 1)
		mlx->move_up = 0;
	if (key == 2)
		mlx->move_side = 0;
	if (key == 123)
		mlx->arrow = 0;
	if (key == 124)
		mlx->arrow = 0;
	return (0);
}

int	handler_test2(int x, int y, t_mlx *mlx)
{
	if (x < (mlx->win_x * 50) / 3 && x > 0 && y < (mlx->win_y * 50) && y > 0)
		mlx->arrow = -2;
	else if (x < (mlx->win_x * 50) && x > 2 * (mlx->win_x * 50) / 3
		&& y < (mlx->win_y * 50) && y > 0)
		mlx->arrow = 2;
	else
		mlx->arrow = 0;
	return (0);
}

int	handler_test3(t_mlx *mlx)
{
	(void)mlx;
	exit(0);
}

void	move_up_player(t_mlx *mlx)
{
	mlx_hook(mlx->win, 17, 0, handler_test3, mlx);
	mlx_hook(mlx->win, 6, 0, handler_test2, mlx);
	mlx_hook(mlx->win, 2, 0, handler, mlx);
	mlx_hook(mlx->win, 3, 0, handler_test1, mlx);
	mlx_loop_hook(mlx->init, handler_test, mlx);
}

void	t3d_map(t_mlx *mlx)
{
	mlx = init_game(mlx);
	move_up_player(mlx);
}
