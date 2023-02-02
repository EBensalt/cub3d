/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aniouar <aniouar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:24:59 by ebensalt          #+#    #+#             */
/*   Updated: 2023/02/03 00:09:06 by aniouar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static char	*f1(char *a, const char *s)
{
	int	b;

	b = 0;
	while (s[b] != '\0')
	{
		a[b] = s[b];
		b++;
	}
	return (a);
}

char	*ft_strjoin_1(char const *s1, char const *s2)
{
	char	*a;
	int		c;
	int		b;

	if (!s1)
		return (0);
	if (!s2)
		return ((char *)s1);
	c = 0;
	while (s1[c] != '\0')
		c++;
	b = 0;
	while (s2[b] != '\0')
		b++;
	a = malloc(((c + b) + 1) * sizeof(char));
	if (a == NULL)
		return (0);
	f1(a, s1);
	f1((a + c), s2);
	a[c + b] = '\0';
	free((char *)s1);
	return (a);
}

char	**map_creat(void)
{
	int		fd;
	char	**map;
	char	*map_part;
	char	*map_line;

	fd = open("map.cub", O_RDONLY);
	map_part = ft_strdup(get_next_line(fd));
	map_line = ft_strdup(map_part);
	while (map_part)
	{
		map_part = ft_strdup(get_next_line(fd));
		map_line = ft_strjoin_1(map_line, map_part);
	}
	map = ft_split(map_line, '\n');
	return (map);
}

t_mlx	*map_dem(t_mlx *mlx)
{
	int	x;
	int	y;
	int	i;

	x = -1;
	i = 0;
	while (mlx->map[++x])
	{
		i = -1;
		while (mlx->map[x][++i])
			;
		if (i > y)
			y = i;
	}
	mlx->i = y;
	mlx->j = x;
	return (mlx);
}

// void	draw_walls(t_mlx *mlx)
// {
// 	int	i;

// 	while (++i)
// 	{
// 		mlx_pixel_put(mlx->init, mlx->win, i, (((mlx->j * 50) / 2) - (i * ((mlx->i * 50) - ))), 0x00FF0000);
// 	}
// }

void	rays_draw(t_mlx *mlx)
{
	double	x;
	double	y;
	int		i;
	int		j;
	int		tmp;

	tmp = 0;
	j = -1;
	while (++j < (mlx->i * 50))
	{
		i = 0;
		x = mlx->player_x + cos(mlx->player_an);
		y = mlx->player_y + sin(mlx->player_an);
		while (mlx->map[(int)y / 50][(int)x / 50] != '1')
		{
			x = mlx->player_x + (i * cos(mlx->player_an + (M_PI / 6 - (j * (M_PI / 3) / (mlx->i * 50)))));
			y = mlx->player_y + (i * sin(mlx->player_an + (M_PI / 6 - (j * (M_PI / 3) / (mlx->i * 50)))));
			// if (((int)x % 50 == 0 || (int)y % 50 == 0) && tmp == 0)
			// {
			// 	if ((int)x % 50 == 0)
			// 		tmp = 1;
			// 	if ((int)y % 50 == 0)
			// 		tmp = 2;
			// }
			// if ((int)x % 50 == 0 && tmp == 1)
				// mlx_pixel_put(mlx->init, mlx->win, x, y, 0x00FF0000);
			// if ((int)y % 50 == 0 && tmp == 2)
			// 	mlx_pixel_put(mlx->init, mlx->win, x, y, 0x00FF0000);
			i++;
		}
		mlx_pixel_put(mlx->init, mlx->win, x - 1, y - 1, 0x00FF0000);
		mlx_pixel_put(mlx->init, mlx->win, x, y, 0x00FF0000);
		mlx_pixel_put(mlx->init, mlx->win, x + 1, y + 1, 0x00FF0000);
		// printf("x %f\ny %f\n", x, y);
	}
}

void	player_draw(t_mlx *mlx)
{
	double	x;
	double	y;
	int		i;

	i = -1;
	mlx->img = mlx_xpm_file_to_image(mlx->init, "p.xpm", &mlx->w, &mlx->h);
	mlx_put_image_to_window(mlx->init, mlx->win, mlx->img, (mlx->player_x - 5), (mlx->player_y - 5));
	mlx_destroy_image(mlx->init, mlx->img);
	while (++i < 50)
	{
		x = mlx->player_x + (i * cos(mlx->player_an));
		y = mlx->player_y + (i * sin(mlx->player_an));
		mlx_pixel_put(mlx->init, mlx->win, x, y, 0x00FF0000);
	}
	rays_draw(mlx);
}

void	map_draw(t_mlx *mlx)
{
	int	i;
	int	j;

	i = -1;
	while (mlx->map[++i])
	{
		j = -1;
		while (mlx->map[i][++j])
		{
			while (mlx->map[i][j] == ' ')
				j++;
			if (mlx->map[i][j] == '1')
				mlx->img = mlx_xpm_file_to_image(mlx->init, "b.xpm", &mlx->w, &mlx->h);
			else
				mlx->img = mlx_xpm_file_to_image(mlx->init, "w.xpm", &mlx->w, &mlx->h);
			mlx_put_image_to_window(mlx->init, mlx->win, mlx->img, (j * 50), (i * 50));
			mlx_destroy_image(mlx->init, mlx->img);
		}
	}
	player_draw(mlx);
	// int	i;

	// i = -1;
	// while (++i <= (mlx->i * 50))
	// {
	// 	mlx_pixel_put(mlx->init, mlx->win, i, ((mlx->j * 50) / 2), 0x00FF0000);
	// }
	// player_draw(mlx);
}

t_mlx	*init_game(t_mlx *mlx)
{
	int	i;
	int	j;

	i = -1;
	while (mlx->map[++i])
	{
		j = 0;
		while (mlx->map[i][j])
		{
			if (mlx->map[i][j] == ' ' || mlx->map[i][j] == '1' || mlx->map[i][j] == '0')
				j++;
			else
			{
				mlx->player_x = (j * 50) + 25;
				mlx->player_y = (i * 50) + 25;
				if (mlx->map[i][j] == 'N')
					mlx->player_an = (3 * M_PI) / 2;
				if (mlx->map[i][j] == 'S')
					mlx->player_an = M_PI / 2;
				if (mlx->map[i][j] == 'E')
					mlx->player_an = 0;
				if (mlx->map[i][j] == 'W')
					mlx->player_an = M_PI;
				break ;
			}
		}
	}
	map_draw(mlx);
	return (mlx);
}

int	handler(int key, t_mlx *mlx)
{
	if (key == 13)
	{
		mlx->move_up = 1;
		// mlx->player_x += 10 * cos(mlx->player_an);
		// mlx->player_y += 10 * sin(mlx->player_an);
	}
	if (key == 0)
	{
		mlx->move_side = 1;
		// mlx->player_x -= 10 * cos(mlx->player_an + (M_PI / 2));
		// mlx->player_y -= 10 * sin(mlx->player_an + (M_PI / 2));
	}
	if (key == 1)
	{
		mlx->move_up = -1;
		// mlx->player_x -= 10 * cos(mlx->player_an);
		// mlx->player_y -= 10 * sin(mlx->player_an);
	}
	if (key == 2)
	{
		mlx->move_side = -1;
		// mlx->player_x += 10 * cos(mlx->player_an + (M_PI / 2));
		// mlx->player_y += 10 * sin(mlx->player_an + (M_PI / 2));
	}
	if (key == 123)
	{
		mlx->arrow = -1;
		// mlx->player_an -= 10 *(M_PI / 180);
	}
	if (key == 124)
	{
		mlx->arrow = 1;
		// mlx->player_an += 10 *(M_PI / 180);
	}
	// mlx_clear_window(mlx->init, mlx->win);
	// map_draw(mlx);
	return (0);
}

int	handler_test(t_mlx *mlx)
{
	double	x;
	double	y;
	int		i;
	// int		j;

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
		// mlx->move_side = 1;
		x -= 10 * cos(mlx->player_an + (M_PI / 2));
		y -= 10 * sin(mlx->player_an + (M_PI / 2));
	}
	if (mlx->move_side == -1)
	{
		// mlx->move_side = -1;
		x += 10 * cos(mlx->player_an + (M_PI / 2));
		y += 10 * sin(mlx->player_an + (M_PI / 2));
	}
	if (mlx->arrow == -1)
	{
		mlx->player_an -= 10 *(M_PI / 180);
		// mlx->arrow = 0;
	}
	if (mlx->arrow == 1)
	{
		mlx->player_an += 10 *(M_PI / 180);
		// mlx->arrow = 0;
	}
	// j = x / 50;
	i = -1;
	if (mlx->map[(int)(y / 50)][(int)(x / 50)] != '1')
	{
		mlx->player_x = x;
		mlx->player_y = y;
	}
	else if (mlx->map[(int)(y / 50)][(int)(x / 50)] == '1')
	{
		x = mlx->player_x;
		y = mlx->player_y;
		while (mlx->map[(int)(y / 50)][(int)(x / 50)] != '1' && ++i < 10)
		{
			mlx->player_x = x;
			mlx->player_y = y;
			if (mlx->move_up == 1)
			{
				x += cos(mlx->player_an);
				y += sin(mlx->player_an);
			}
			if (mlx->move_up == -1)
			{
				x -= cos(mlx->player_an);
				y -= sin(mlx->player_an);
			}
			if (mlx->move_side == 1)
			{
				x -= cos(mlx->player_an + (M_PI / 2));
				y -= sin(mlx->player_an + (M_PI / 2));
			}
			if (mlx->move_side == -1)
			{
				x += cos(mlx->player_an + (M_PI / 2));
				y += sin(mlx->player_an + (M_PI / 2));
			}
		}
	}
	mlx_clear_window(mlx->init, mlx->win);
	map_draw(mlx);
	// printf("player x %f\n", mlx->player_x);
	return (0);
}

int	handler_test1(int key, t_mlx *mlx)
{
	// (void)mlx;
	// printf("ok\n");
	// mlx_hook(mlx->win, 2, 0, handler, mlx);
	if (key == 13)
	{
		mlx->move_up = 0;
		// mlx->player_x += 10 * cos(mlx->player_an);
		// mlx->player_y += 10 * sin(mlx->player_an);
	}
	if (key == 0)
	{
		mlx->move_side = 0;
		// mlx->player_x += 5 * cos(mlx->player_an);
		// mlx->player_y -= 5 * sin(mlx->player_an);
	}
	if (key == 1)
	{
		mlx->move_up = 0;
		// mlx->player_x -= 10 * cos(mlx->player_an);
		// mlx->player_y -= 10 * sin(mlx->player_an);
	}
	if (key == 2)
	{
		mlx->move_side = 0;
		// mlx->player_x += 5 * cos(mlx->player_an);
		// mlx->player_y -= 5 * sin(mlx->player_an);
	}
	if (key == 123)
		mlx->arrow = 0;
		// mlx->player_an -= 10 *(M_PI / 180);
	if (key == 124)
		mlx->arrow = 0;
		// mlx->player_an += 10 *(M_PI / 180);
	// mlx->arrow = 0;
	return (0);
}

void	move_up_player(t_mlx *mlx)
{
	mlx_hook(mlx->win, 2, 0, handler, mlx);
	mlx_hook(mlx->win, 3, 0, handler_test1, mlx);
	mlx_loop_hook(mlx->init, handler_test, mlx);
}

void	game(t_mlx *mlx)
{
	mlx = init_game(mlx);
	move_up_player(mlx);
}

void	td_map(t_mlx *mlx)
{
	game(mlx);
}

int	main(int ac,char **av)
{
	t_mlx	*mlx;
	t_pars *pars;
	// int	i;

	// i = -1;
	(void)ac;
	(void)av;
	(void)mlx;
	pars = parser(av[1]);
	// while (pars->map[++i])
	// 	printf("%s\n", pars->map[i]);
	mlx = malloc(sizeof(t_mlx));
	mlx->map = pars->map;
	// mlx->map = map_creat();
	// i = -1;
	// while (mlx->map[++i])
	// 	printf("%s\n", mlx->map[i]);
	mlx->init = mlx_init();
	mlx = map_dem(mlx);
	mlx->win = mlx_new_window(mlx->init, (mlx->i * 50), (mlx->j * 50), "cub3D");
	td_map(mlx);
	mlx_loop(mlx->init);
}
