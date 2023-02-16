/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aniouar <aniouar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:24:59 by ebensalt          #+#    #+#             */
/*   Updated: 2023/02/16 15:32:02 by aniouar          ###   ########.fr       */
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

void	map_draw(t_mlx *mlx)
{
	double	x;
	double	y;
	int		i;
	int		j;
	double	tmp;
	int		k;
	int		l;
	int cc;
	int ll;
	//void *test;
	
	tmp = 0;
	j = -1;
	while (++j <= (mlx->i * 50))
	{
		i = 0;
		x = mlx->player_x + cos(mlx->player_an);
		y = mlx->player_y + sin(mlx->player_an);
		tmp = mlx->player_an - (M_PI / 6 - (j * (M_PI / 3) / (mlx->i * 50)));
		cc = (int)y / 50;
		ll = (int)y / 50;
		
		while (mlx->map[(int)y / 50][(int)x / 50] != '1')
		{
			x = mlx->player_x + (i * cos(tmp));
			y = mlx->player_y + (i * sin(tmp));
			i++;
		}
		
		mlx->ray = (((x - mlx->player_x) * cos(tmp) + (y - mlx->player_y) * sin(tmp)) / 2) * cos(mlx->player_an - tmp);
		mlx->hight = ((mlx->j * 50) / mlx->ray) * mlx->j;
		i = (mlx->j * 50) / 2;
		//printf("N:%f S:%f E:%df W:%f\n",(3 * M_PI) / 2,(M_PI / 2),0, M_PI);

		//printf("mlx->map[%i][%i] %c\n",(int)y / 50,(int)x / 50,mlx->map[(int)y / 50][(int)x / 50]);
		while (--i > (mlx->j * 50) / 2 - mlx->hight)
			;
		while (++i < (mlx->j * 50) / 2 + mlx->hight)
		{
			if (i <= mlx->j * 50 && i >= 0)
				if (i % 2 == 0 && j % 2 == 0)
				{
					//printf("x %i y %i\n",((int)x%50),((int)y%50));
					// if(mlx->data.use == 20)
					// {
						k = mlx->h / (mlx->hight * 2);
						// l = (int)x % 50;
						l = (int)y % 50;
						l = (mlx->w / 50) * l;
						k = (i - ((mlx->j * 50) / 2 - mlx->hight)) * k;
						// l = (j % 50) * l;
						// printf("%d\n", k);
						mlx->data.addr = mlx->data.catch;
						mlx->data.addr = mlx->data.addr + (k * mlx->data.line_length + l * (mlx->data.bits_per_pixel / 8)  );	
						mlx->data.use = 0;
					// }
					//printf("%i %i \n",*(unsigned int*)mlx->data.addr,i);
						mlx_pixel_put(mlx->init, mlx->win, j, i, *(unsigned int*)mlx->data.addr);
					// mlx->data.use++;
				}
					
		}
		
	}
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
	if (mlx->arrow == -1)
		mlx->player_an -= 10 *(M_PI / 180);
	if (mlx->arrow == 1)
		mlx->player_an += 10 *(M_PI / 180);
	i = -1;
	if (mlx->map[(int)((y + 10) / 50)][(int)((x + 10) / 50)] != '1' && mlx->map[(int)((y - 10) / 50)][(int)((x - 10) / 50)] != '1')
	{
		mlx->player_x = x;
		mlx->player_y = y;
	}
	mlx_clear_window(mlx->init, mlx->win);
	map_draw(mlx);
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

void	move_up_player(t_mlx *mlx)
{
	mlx_hook(mlx->win, 2, 0, handler, mlx);
	mlx_hook(mlx->win, 3, 0, handler_test1, mlx);
	mlx_loop_hook(mlx->init, handler_test, mlx);
}

void	t3d_map(t_mlx *mlx)
{
	t_data data;
	//void	*imgs;
	void *mlxx;

	// int w,h;

	mlxx = mlx_init();
	
	data.img  = mlx_xpm_file_to_image(mlxx, "france_shit.xpm",&mlx->w, &mlx->h);
	// printf("w %d\nh %d", w, h);
	// exit(0);
	data.addr=  mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	data.catch = data.addr;
	data.use = 0;
	mlx->data = data;

	
	mlx = init_game(mlx);
	move_up_player(mlx);
}

int	main(void)
{
	t_mlx	*mlx;
	

	mlx = malloc(sizeof(t_mlx));
	mlx->map = map_creat();
	mlx->init = mlx_init();
	mlx->i = 25;
	mlx->j = 14;
	mlx->win = mlx_new_window(mlx->init, (mlx->i * 50), (mlx->j * 50), "cub3D");
	t3d_map(mlx);
	mlx_loop(mlx->init);
}
