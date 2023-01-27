/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aniouar <aniouar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:24:59 by ebensalt          #+#    #+#             */
/*   Updated: 2023/01/27 11:15:18 by aniouar          ###   ########.fr       */
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
	int count;
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
	map = ft_split(map_line, '\n',&count);
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

void	player_draw(t_mlx *mlx)
{
	int	x;
	int	y;
	int	i;

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
		mlx->player_x += 10 * cos(mlx->player_an);
		mlx->player_y += 10 * sin(mlx->player_an);
	}
	// if (key == 0)
	// {
	// 	mlx->player_x += 5 * cos(mlx->player_an);
	// 	mlx->player_y -= 5 * sin(mlx->player_an);
	// }
	if (key == 1)
	{
		mlx->player_x -= 10 * cos(mlx->player_an);
		mlx->player_y -= 10 * sin(mlx->player_an);
	}
	// if (key == 2)
	// {
	// 	mlx->player_x -= 5 * cos(mlx->player_an);
	// 	mlx->player_y += 5 * sin(mlx->player_an);
	// }
	if (key == 123)
		mlx->player_an -= 10 *(M_PI / 180);
	if (key == 124)
		mlx->player_an += 10 *(M_PI / 180);
	mlx_clear_window(mlx->init, mlx->win);
	map_draw(mlx);
	return (0);
}

int	handler_test(t_mlx *mlx)
{
	// (void)mlx;
	// printf("ok\n");
	mlx_hook(mlx->win, 2, 0, handler, mlx);
	return (0);
}

void	move_player(t_mlx *mlx)
{
	// mlx_hook(mlx->win, 2, 0, handler, mlx);
	mlx_loop_hook(mlx->init, handler_test, mlx);
}

void	game(t_mlx *mlx)
{
	mlx = init_game(mlx);
	move_player(mlx);
}

void	td_map(t_mlx *mlx)
{
	mlx->init = mlx_init();
	mlx = map_dem(mlx);
	mlx->win = mlx_new_window(mlx->init, (mlx->i * 50), (mlx->j * 50), "cub3D");
	game(mlx);
	mlx_loop(mlx->init);
}

int	main(int ac,char **av)
{
	//t_mlx	*mlx;
	
	(void)av;
	if(ac != 2)
		return (1);
	
	parser(av[1]);
	
	/*
		mlx = malloc(sizeof(t_mlx));
		mlx->map = map_creat();
		td_map(mlx);
		
	*/
		

	
}
