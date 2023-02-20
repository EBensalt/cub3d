/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 05:16:34 by ebensalt          #+#    #+#             */
/*   Updated: 2023/02/20 05:17:12 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	wall_draw_utils(t_mlx *mlx, double tmp, double i, double j)
{
	if (mlx->ray_h < mlx->ray_v)
	{
		while (mlx->x_h > 50)
			mlx->x_h = mlx->x_h - 50;
		mlx->l = mlx->x_h;
		if (sin(tmp) > 0)
			my_mlx_pixel_put(mlx, j, i,
				get_color(mlx, mlx->pars->tex->t_so, i));
		else
			my_mlx_pixel_put(mlx, j, i,
				get_color(mlx, mlx->pars->tex->t_no, i));
	}
	else
	{
		while (mlx->y_v > 50)
			mlx->y_v = mlx->y_v - 50;
		mlx->l = mlx->y_v;
		if (cos(tmp) > 0)
			my_mlx_pixel_put(mlx, j, i,
				get_color(mlx, mlx->pars->tex->t_ea, i));
		else
			my_mlx_pixel_put(mlx, j, i,
				get_color(mlx, mlx->pars->tex->t_we, i));
	}
}

void	wall_draw(t_mlx *mlx, double j, double tmp)
{
	double	i;

	i = -1;
	while (++i < (mlx->win_y * 50))
	{
		if (i < (mlx->win_y * 50) / 2 - mlx->hight)
			my_mlx_pixel_put(mlx, j, i, mlx->pars->color_c);
		else if (i > (mlx->win_y * 50) / 2 + mlx->hight)
			my_mlx_pixel_put(mlx, j, i, mlx->pars->color_floor);
		else
			wall_draw_utils(mlx, tmp, i, j);
	}
}

t_mlx	*v_inter_utils(t_mlx *mlx, double tmp)
{
	if (cos(tmp) >= 0)
	{
		if ((int)mlx->x_v % 50 != 0)
			mlx->x_v = ((int)(mlx->player_x / 50) + 1) * 50;
		else
			mlx->x_v = mlx->x_v + 50;
		mlx->y_v = mlx->player_y
			+ (mlx->x_v - mlx->player_x) * tan(tmp);
	}
	return (mlx);
}

t_mlx	*v_inter(t_mlx *mlx, double tmp)
{
	mlx->y_v = mlx->player_y;
	mlx->x_v = mlx->player_x;
	while (mlx->x_v > 0 && mlx->x_v < (mlx->i * 50) && mlx->y_v > 0
		&& mlx->y_v < (mlx->j * 50)
		&& mlx->pars->map[(int)(mlx->y_v / 50)][(int)(mlx->x_v / 50)] != '1'
		&& mlx->pars->map[(int)(mlx->y_v / 50)][(int)((mlx->x_v - 1) / 50)]
		!= '1')
	{
		if (cos(tmp) <= 0)
		{
			if ((int)mlx->x_v % 50 != 0)
				mlx->x_v = (int)(mlx->player_x / 50) * 50;
			else
				mlx->x_v = mlx->x_v - 50;
			mlx->y_v = mlx->player_y
				+ (mlx->x_v - mlx->player_x) * tan(tmp);
		}
		mlx = v_inter_utils(mlx, tmp);
	}
	return (mlx);
}

t_mlx	*h_inter_utils(t_mlx *mlx, double tmp)
{
	if (sin(tmp) >= 0)
	{
		if ((int)mlx->y_h % 50 != 0)
			mlx->y_h = ((int)(mlx->player_y / 50) + 1) * 50;
		else
			mlx->y_h = mlx->y_h + 50;
		mlx->x_h = mlx->player_x
			+ (mlx->y_h - mlx->player_y) / tan(tmp);
	}
	return (mlx);
}
