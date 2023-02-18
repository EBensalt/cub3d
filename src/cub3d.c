/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:24:59 by ebensalt          #+#    #+#             */
/*   Updated: 2023/02/18 19:31:09 by ebensalt         ###   ########.fr       */
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
	t->addr = t->addr + ((int)mlx->k * t->line_length + (int)mlx->l * (t->bits_per_pixel / 8));
	return (*(unsigned int *)t->addr);
}

void	player_draw(t_mlx *mlx)
{
	double	x;
	double	y;
	int		i;

	i = -1;
	mlx->mini_img_p = mlx_xpm_file_to_image(mlx->init, "textures/p.xpm", &mlx->w, &mlx->h);
	mlx_put_image_to_window(mlx->init, mlx->win, mlx->mini_img_p, ((mlx->player_x) / 50) * 10 - 2.5, ((mlx->player_y) / 50) * 10 - 2.5);
	mlx_destroy_image(mlx->init, mlx->mini_img_p);
	while (++i < 20)
	{
		x = (mlx->player_x / 50) * 10 + (i * cos(mlx->player_an));
		y = (mlx->player_y / 50) * 10 + (i * sin(mlx->player_an));
		// my_mlx_pixel_put(mlx, x, y, 0x00FF0000);
		mlx_pixel_put(mlx->init, mlx->win, x, y, 0x00FF0000);
	}
	// rays_draw(mlx);
}

void	mini_map_draw(t_mlx *mlx)
{
	int	i;
	int	j;

	i = -1;
	mlx->mini_img_1 = mlx_xpm_file_to_image(mlx->init, "textures/b.xpm", &mlx->w, &mlx->h);
	mlx->mini_img_0 = mlx_xpm_file_to_image(mlx->init, "textures/w.xpm", &mlx->w, &mlx->h);
	while (mlx->pars->map[++i])
	{
		j = -1;
		while (mlx->pars->map[i][++j])
		{
			while (mlx->pars->map[i][j] == ' ')
				j++;
			if (mlx->pars->map[i][j] == '1')
				mlx_put_image_to_window(mlx->init, mlx->win, mlx->mini_img_1, (j * 10), (i * 10));
				// mlx->mini_img = mlx_xpm_file_to_image(mlx->init, "b.xpm", &mlx->w, &mlx->h);
			else
				mlx_put_image_to_window(mlx->init, mlx->win, mlx->mini_img_0, (j * 10), (i * 10));
				// mlx->mini_img = mlx_xpm_file_to_image(mlx->init, "w.xpm", &mlx->w, &mlx->h);
		}
	}
	mlx_destroy_image(mlx->init, mlx->mini_img_1);
	mlx_destroy_image(mlx->init, mlx->mini_img_0);
	player_draw(mlx);
	// int	i;

	// i = -1;
	// while (++i <= (mlx->i * 50))
	// {
	// 	mlx_pixel_put(mlx->init, mlx->win, i, ((mlx->j * 50) / 2), 0x00FF0000);
	// }
	// player_draw(mlx);
}

void	map_draw(t_mlx *mlx)
{
	double	x_h;
	double	y_h;
	double	x_v;
	double	y_v;
	double	i;
	double	j;
	double	tmp;

	tmp = 0;
	j = -1;
	// mlx = init_tex(mlx);
	mlx->img = mlx_new_image(mlx->init, (mlx->win_x * 50), (mlx->win_y * 50));
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
	while (++j <= (mlx->win_x * 50))
	{
		i = 0;
		x_h = mlx->player_x;
		y_h = mlx->player_y;
		tmp = mlx->player_an - (M_PI / 6 - (j * (M_PI / 3) / (mlx->i * 50)));
		while (x_h > 0 && x_h < (mlx->i * 50) && y_h > 0 && y_h < (mlx->j * 50) && mlx->pars->map[(int)((y_h - 1) / 50)][(int)(x_h / 50)] != '1' && mlx->pars->map[(int)(y_h / 50)][(int)(x_h / 50)] != '1')
		{
			if (sin(tmp) <= 0)
			{
				if ((int)y_h % 50 != 0)
					y_h = (int)(mlx->player_y / 50) * 50;
				else
					y_h = y_h - 50;
				x_h = mlx->player_x + (y_h - mlx->player_y) / tan(mlx->player_an - (M_PI / 6 - (j * (M_PI / 3) / (mlx->i * 50))));
			}
			if (sin(tmp) >= 0)
			{
				if ((int)y_h % 50 !=0)
					y_h = ((int)(mlx->player_y / 50) + 1) * 50;
				else
					y_h = y_h + 50;
				x_h = mlx->player_x + (y_h - mlx->player_y) / tan(mlx->player_an - (M_PI / 6 - (j * (M_PI / 3) / (mlx->i * 50))));
			}
		}
		y_v = mlx->player_y;
		x_v = mlx->player_x;
		while (x_v > 0 && x_v < (mlx->i * 50) && y_v > 0 && y_v < (mlx->j * 50) && mlx->pars->map[(int)(y_v / 50)][(int)(x_v / 50)] != '1' && mlx->pars->map[(int)(y_v / 50)][(int)((x_v - 1) / 50)] != '1')
		{
			if (cos(tmp) <= 0)
			{
				if ((int)x_v % 50 != 0)
					x_v = (int)(mlx->player_x / 50) * 50;
				else
					x_v = x_v - 50;
				y_v = mlx->player_y + (x_v - mlx->player_x) * tan(mlx->player_an - (M_PI / 6 - (j * (M_PI / 3) / (mlx->i * 50))));
			}
			if (cos(tmp) >= 0)
			{
				if ((int)x_v % 50 !=0)
					x_v = ((int)(mlx->player_x / 50) + 1) * 50;
				else
					x_v = x_v + 50;
				y_v = mlx->player_y + (x_v - mlx->player_x) * tan(mlx->player_an - (M_PI / 6 - (j * (M_PI / 3) / (mlx->i * 50))));
			}
		}
		mlx->ray_h = sqrt((pow(x_h - mlx->player_x, 2) + pow(y_h - mlx->player_y, 2)));
		mlx->ray_v = sqrt((pow(x_v - mlx->player_x, 2) + pow(y_v - mlx->player_y, 2)));
		if (mlx->ray_h < mlx->ray_v)
			mlx->ray = mlx->ray_h * cos(tmp - mlx->player_an);
		else
			mlx->ray = mlx->ray_v * cos(tmp - mlx->player_an);
		mlx->hight = ((mlx->win_y * 50) / mlx->ray) * mlx->win_y * 2.2;
		i = -1;
		while (++i < (mlx->win_y * 50))
		{
			if (i < (mlx->win_y * 50) / 2 - mlx->hight)
				my_mlx_pixel_put(mlx, j, i, mlx->pars->color_c);
			else if (i > (mlx->win_y * 50) / 2 + mlx->hight)
				my_mlx_pixel_put(mlx, j, i, mlx->pars->color_floor);
			else
			{
				if (mlx->ray_h < mlx->ray_v)
				{
					while (x_h > 50)
						x_h = x_h - 50;
					mlx->l = x_h;
					if (sin(tmp) > 0)
						my_mlx_pixel_put(mlx, j, i, get_color(mlx, mlx->pars->dir_texture->t_so, i));
					else
						my_mlx_pixel_put(mlx, j, i, get_color(mlx, mlx->pars->dir_texture->t_no, i));
				}
				else
				{
					while (y_v > 50)
						y_v = y_v - 50;
					mlx->l = y_v;
					if (cos(tmp) > 0)
						my_mlx_pixel_put(mlx, j, i, get_color(mlx, mlx->pars->dir_texture->t_ea, i));
					else
						my_mlx_pixel_put(mlx, j, i, get_color(mlx, mlx->pars->dir_texture->t_we, i));
				}
			}
		}
	}
	mlx_put_image_to_window(mlx, mlx->win, mlx->img, 0, 0);
	mini_map_draw(mlx);
	mlx_destroy_image(mlx->init, mlx->img);
	// mlx_destroy_image(mlx->init, mlx->pars->dir_texture->t_no->img);
	// mlx_destroy_image(mlx->init, mlx->pars->dir_texture->t_so->img);
	// mlx_destroy_image(mlx->init, mlx->pars->dir_texture->t_w->img);
	// mlx_destroy_image(mlx->init, mlx->pars->dir_texture->t_no->img);
}

t_mlx	*init_tex(t_mlx *mlx)
{
	mlx->pars->dir_texture->t_no = malloc(sizeof(t_tex));
	mlx->pars->dir_texture->t_no->img = mlx_xpm_file_to_image(mlx->init, "./textures/wall_no.xpm", &mlx->pars->dir_texture->t_no->w, &mlx->pars->dir_texture->t_no->h);
	mlx->pars->dir_texture->t_no->addr = mlx_get_data_addr(mlx->pars->dir_texture->t_no->img, &mlx->pars->dir_texture->t_no->bits_per_pixel, &mlx->pars->dir_texture->t_no->line_length, &mlx->pars->dir_texture->t_no->endian);
	mlx->pars->dir_texture->t_no->in = mlx->pars->dir_texture->t_no->addr;
	mlx->pars->dir_texture->t_so = malloc(sizeof(t_tex));
	mlx->pars->dir_texture->t_so->img = mlx_xpm_file_to_image(mlx->init, "./textures/wall_so.xpm", &mlx->pars->dir_texture->t_so->w, &mlx->pars->dir_texture->t_so->h);
	mlx->pars->dir_texture->t_so->addr = mlx_get_data_addr(mlx->pars->dir_texture->t_so->img, &mlx->pars->dir_texture->t_so->bits_per_pixel, &mlx->pars->dir_texture->t_so->line_length, &mlx->pars->dir_texture->t_so->endian);
	mlx->pars->dir_texture->t_so->in = mlx->pars->dir_texture->t_so->addr;
	mlx->pars->dir_texture->t_we = malloc(sizeof(t_tex));
	mlx->pars->dir_texture->t_we->img = mlx_xpm_file_to_image(mlx->init, "./textures/wall_we.xpm", &mlx->pars->dir_texture->t_we->w, &mlx->pars->dir_texture->t_we->h);
	mlx->pars->dir_texture->t_we->addr = mlx_get_data_addr(mlx->pars->dir_texture->t_we->img, &mlx->pars->dir_texture->t_we->bits_per_pixel, &mlx->pars->dir_texture->t_we->line_length, &mlx->pars->dir_texture->t_we->endian);
	mlx->pars->dir_texture->t_we->in = mlx->pars->dir_texture->t_we->addr;
	mlx->pars->dir_texture->t_ea = malloc(sizeof(t_tex));
	mlx->pars->dir_texture->t_ea->img = mlx_xpm_file_to_image(mlx->init, "./textures/wall_ea.xpm", &mlx->pars->dir_texture->t_ea->w, &mlx->pars->dir_texture->t_ea->h);
	mlx->pars->dir_texture->t_ea->addr = mlx_get_data_addr(mlx->pars->dir_texture->t_ea->img, &mlx->pars->dir_texture->t_ea->bits_per_pixel, &mlx->pars->dir_texture->t_ea->line_length, &mlx->pars->dir_texture->t_ea->endian);
	mlx->pars->dir_texture->t_ea->in = mlx->pars->dir_texture->t_ea->addr;
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
			if (mlx->pars->map[i][j] == ' ' || mlx->pars->map[i][j] == '1' || mlx->pars->map[i][j] == '0')
				j++;
			else
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
				break ;
			}
		}
	}
	mlx->mouse = 0;
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
	return (0);
}

int	handler_test(t_mlx *mlx)
{
	double	x;
	double	y;
	int		i;

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
	if (mlx->move_side == -1)
	{
		x += 10 * cos(mlx->player_an + (M_PI / 2));
		y += 10 * sin(mlx->player_an + (M_PI / 2));
	}
	if (mlx->arrow < 0)
	{
		mlx->player_an -= 10 *(M_PI / 180);
		// if (mlx->arrow == -2)
		// 	mlx->arrow = 0;
	}
	if (mlx->arrow > 0)
	{
		mlx->player_an += 10 *(M_PI / 180);
		// if (mlx->arrow == 2)
		// 	mlx->arrow = 0;
	}
	i = -1;
	if (mlx->pars->map[(int)((y + 10) / 50)][(int)((x) / 50)] != '1' && mlx->pars->map[(int)((y - 10) / 50)][(int)((x) / 50)] != '1' && mlx->pars->map[(int)((y) / 50)][(int)((x + 10) / 50)] != '1' && mlx->pars->map[(int)((y) / 50)][(int)((x - 10) / 50)] != '1')
	{
		mlx->player_x = x;
		mlx->player_y = y;
	}
	if (mlx->move_up != 0 || mlx->move_side != 0 || mlx->arrow != 0)
	{
		// if (mlx->arrow == -2 || mlx->arrow == 2)
		// 	mlx->arrow = 0;
		mlx_clear_window(mlx->init, mlx->win);
		map_draw(mlx);
	}
	return (0);
}

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
	// (void)y;
	// (void)mlx;
	// printf("x = %d\n", x);
	// printf("mouse = %d\n", mlx->mouse);
	// if (!mlx->mouse)
	// 	mlx->mouse = x;
	// if (mlx->mouse == x)
	// 	mlx->arrow = 0;
	if (x < (mlx->win_x * 50) / 4 && x > 0 && y < (mlx->win_y * 50) && y > 0)
		mlx->arrow = -2;
	else if (x < (mlx->win_x * 50) && x > 3 * (mlx->win_x * 50) / 4 && y < (mlx->win_y * 50) && y > 0)
		mlx->arrow = 2;
	else
		mlx->arrow = 0;
	// mlx->mouse = x;
	return (0);
}

void	move_up_player(t_mlx *mlx)
{
	mlx_hook(mlx->win, 6, 0, handler_test2, mlx);
	mlx_hook(mlx->win, 2, 0, handler, mlx);
	mlx_hook(mlx->win, 3, 0, handler_test1, mlx);
	mlx_loop_hook(mlx->init, handler_test, mlx);
	// printf("ok\n");
}

void	t3d_map(t_mlx *mlx)
{
	mlx = init_game(mlx);
	move_up_player(mlx);
}

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

	(void)ac;
	mlx = malloc(sizeof(t_mlx));
	mlx->pars = parser(av[1]);
	mlx->init = mlx_init();
	mlx = map_dem(mlx);
	mlx->win = mlx_new_window(mlx->init, (mlx->win_x * 50), (mlx->win_y * 50), "cub3D");
	t3d_map(mlx);
	// printf("ok\n");
	mlx_loop(mlx->init);
}
