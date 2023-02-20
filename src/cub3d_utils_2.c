/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 06:03:49 by ebensalt          #+#    #+#             */
/*   Updated: 2023/02/20 06:04:06 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_mlx	*h_inter(t_mlx *mlx, double tmp)
{
	mlx->x_h = mlx->player_x;
	mlx->y_h = mlx->player_y;
	while (mlx->x_h > 0 && mlx->x_h < (mlx->i * 50) && mlx->y_h > 0
		&& mlx->y_h < (mlx->j * 50)
		&& mlx->pars->map[(int)((mlx->y_h - 1) / 50)][(int)(mlx->x_h / 50)]
		!= '1'
		&& mlx->pars->map[(int)(mlx->y_h / 50)][(int)(mlx->x_h / 50)]
		!= '1')
	{
		if (sin(tmp) <= 0)
		{
			if ((int)mlx->y_h % 50 != 0)
				mlx->y_h = (int)(mlx->player_y / 50) * 50;
			else
				mlx->y_h = mlx->y_h - 50;
			mlx->x_h = mlx->player_x
				+ (mlx->y_h - mlx->player_y) / tan(tmp);
		}
		mlx = h_inter_utils(mlx, tmp);
	}
	return (mlx);
}

t_mlx	*ray(t_mlx *mlx, double tmp)
{
	mlx->ray_h = sqrt((pow(mlx->x_h - mlx->player_x, 2)
				+ pow(mlx->y_h - mlx->player_y, 2)));
	mlx->ray_v = sqrt((pow(mlx->x_v - mlx->player_x, 2)
				+ pow(mlx->y_v - mlx->player_y, 2)));
	if (mlx->ray_h < mlx->ray_v)
		mlx->ray = mlx->ray_h * cos(tmp - mlx->player_an);
	else
		mlx->ray = mlx->ray_v * cos(tmp - mlx->player_an);
	return (mlx);
}

void	map_draw(t_mlx *mlx)
{
	double	j;
	double	tmp;

	tmp = 0;
	j = -1;
	mlx->img = mlx_new_image(mlx->init, (mlx->win_x * 50), (mlx->win_y * 50));
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
	while (++j <= (mlx->win_x * 50))
	{
		tmp = mlx->player_an
			- (M_PI / 6 - (j * (M_PI / 3) / (mlx->win_x * 50)));
		mlx = h_inter(mlx, tmp);
		mlx = v_inter(mlx, tmp);
		mlx = ray(mlx, tmp);
		mlx->hight = ((mlx->win_y * 50) / mlx->ray) * (mlx->win_y * 2.2);
		wall_draw(mlx, j, tmp);
	}
	mlx_put_image_to_window(mlx, mlx->win, mlx->img, 0, 0);
	mini_map_draw(mlx);
	mlx_destroy_image(mlx->init, mlx->img);
}

t_mlx	*img_gen(t_mlx *mlx)
{
	mlx->pars->tex->t_no->img = mlx_xpm_file_to_image(mlx->init,
			mlx->pars->tex->no, &mlx->pars->tex->t_no->w,
			&mlx->pars->tex->t_no->h);
	mlx->pars->tex->t_so->img = mlx_xpm_file_to_image(mlx->init,
			mlx->pars->tex->so, &mlx->pars->tex->t_so->w,
			&mlx->pars->tex->t_so->h);
	mlx->pars->tex->t_we->img = mlx_xpm_file_to_image(mlx->init,
			mlx->pars->tex->we, &mlx->pars->tex->t_we->w,
			&mlx->pars->tex->t_we->h);
	mlx->pars->tex->t_ea->img = mlx_xpm_file_to_image(mlx->init,
			mlx->pars->tex->ea, &mlx->pars->tex->t_ea->w,
			&mlx->pars->tex->t_ea->h);
	if (!mlx->pars->tex->t_no->img || !mlx->pars->tex->t_so->img
		|| !mlx->pars->tex->t_we->img || !mlx->pars->tex->t_ea->img)
		throw_error("Error :Invalide texters");
	return (mlx);
}

t_mlx	*init_tex(t_mlx *mlx)
{
	mlx->pars->tex->t_no = malloc(sizeof(t_tex));
	mlx->pars->tex->t_so = malloc(sizeof(t_tex));
	mlx->pars->tex->t_we = malloc(sizeof(t_tex));
	mlx->pars->tex->t_ea = malloc(sizeof(t_tex));
	mlx = img_gen(mlx);
	mlx->pars->tex->t_no->addr = mlx_get_data_addr(mlx->pars->tex->t_no->img,
			&mlx->pars->tex->t_no->bits_per_pixel,
			&mlx->pars->tex->t_no->line_length, &mlx->pars->tex->t_no->endian);
	mlx->pars->tex->t_we->addr = mlx_get_data_addr(mlx->pars->tex->t_we->img,
			&mlx->pars->tex->t_we->bits_per_pixel,
			&mlx->pars->tex->t_we->line_length, &mlx->pars->tex->t_we->endian);
	mlx->pars->tex->t_so->addr = mlx_get_data_addr(mlx->pars->tex->t_so->img,
			&mlx->pars->tex->t_so->bits_per_pixel,
			&mlx->pars->tex->t_so->line_length, &mlx->pars->tex->t_so->endian);
	mlx->pars->tex->t_ea->addr = mlx_get_data_addr(mlx->pars->tex->t_ea->img,
			&mlx->pars->tex->t_ea->bits_per_pixel,
			&mlx->pars->tex->t_ea->line_length, &mlx->pars->tex->t_ea->endian);
	mlx->pars->tex->t_no->in = mlx->pars->tex->t_no->addr;
	mlx->pars->tex->t_so->in = mlx->pars->tex->t_so->addr;
	mlx->pars->tex->t_we->in = mlx->pars->tex->t_we->addr;
	mlx->pars->tex->t_ea->in = mlx->pars->tex->t_ea->addr;
	return (mlx);
}
