/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils_0.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 04:08:26 by ebensalt          #+#    #+#             */
/*   Updated: 2023/02/20 04:10:41 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned int	get_color(t_mlx *mlx, t_tex *t, int i)
{
	t->addr = t->in;
	mlx->k = t->h / (mlx->hight * 2);
	mlx->k = (i - ((mlx->win_y * 50) / 2 - mlx->hight)) * mlx->k;
	mlx->l = (t->w / 50) * mlx->l;
	t->addr = t->addr + ((int)mlx->k * t->line_length
			+ (int)mlx->l * (t->bits_per_pixel / 8));
	return (*(unsigned int *)t->addr);
}

void	player_draw(t_mlx *mlx)
{
	double	x;
	double	y;
	int		i;

	i = -1;
	mlx->mini_img_p = mlx_xpm_file_to_image(mlx->init, "textures/p.xpm",
			&mlx->w, &mlx->h);
	mlx_put_image_to_window(mlx->init, mlx->win, mlx->mini_img_p,
		((mlx->player_x) / 50) * 10 - 2.5, ((mlx->player_y) / 50) * 10 - 2.5);
	mlx_destroy_image(mlx->init, mlx->mini_img_p);
	while (++i < 10)
	{
		x = (mlx->player_x / 50) * 10 + (i * cos(mlx->player_an));
		y = (mlx->player_y / 50) * 10 + (i * sin(mlx->player_an));
		mlx_pixel_put(mlx->init, mlx->win, x, y, 0x00FF0000);
	}
}

void	mini_map_utils(t_mlx *mlx, int i)
{
	int	j;

	j = -1;
	while (mlx->pars->map[i][++j])
	{
		while (mlx->pars->map[i][j] == ' ')
			j++;
		if (mlx->pars->map[i][j] == '1')
			mlx_put_image_to_window(mlx->init, mlx->win,
				mlx->mini_img_1, (j * 10), (i * 10));
		else if (mlx->pars->map[i][j] == '0' || mlx->pars->map[i][j] == 'E'
			|| mlx->pars->map[i][j] == 'W' || mlx->pars->map[i][j] == 'S'
			|| mlx->pars->map[i][j] == 'N')
			mlx_put_image_to_window(mlx->init, mlx->win,
				mlx->mini_img_0, (j * 10), (i * 10));
	}
}

void	mini_map_draw(t_mlx *mlx)
{
	int	i;

	i = -1;
	mlx->mini_img_1 = mlx_xpm_file_to_image(mlx->init, "textures/w.xpm",
			&mlx->w, &mlx->h);
	mlx->mini_img_0 = mlx_xpm_file_to_image(mlx->init, "textures/b.xpm",
			&mlx->w, &mlx->h);
	while (mlx->pars->map[++i])
		mini_map_utils(mlx, i);
	mlx_destroy_image(mlx->init, mlx->mini_img_1);
	mlx_destroy_image(mlx->init, mlx->mini_img_0);
	player_draw(mlx);
}
