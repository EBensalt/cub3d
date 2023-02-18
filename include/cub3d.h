/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:24:36 by ebensalt          #+#    #+#             */
/*   Updated: 2023/02/18 18:53:26 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../src/get_next_line/get_next_line.h"
# include "../parsing/parser.h"
# include <mlx.h>
# include <fcntl.h>
# include <math.h> 
# include <string.h>

typedef struct s_tex
{
	void	*img;
	char	*addr;
	char	*in;
	int		w;
	int		h;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_tex;

typedef struct s_dir_texture
{
	t_tex	*t_no;
	t_tex	*t_so;
	t_tex	*t_we;
	t_tex	*t_ea;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*valid_fill;
}	t_dir_texture;

typedef struct s_line
{
	char			*line;
	struct s_line	*prev;
	struct s_line	*next;
}	t_line;

typedef struct s_pars
{
	t_dir_texture	*dir_texture;
	int				valid_direction;
	int				color_floor;
	int				color_c;
	int				valid_color;
	char			*vision;
	int				valid_player;
	int				start_map;
	int				valid_map;
	char			**map;
	t_line			*lines;
	t_line			*prev_line;
}	t_pars;

typedef struct s_mlx
{
	void	*init;
	void	*win;
	void	*img;
	// void	*mini_img;
	void	*mini_img_1;
	void	*mini_img_0;
	void	*mini_img_p;
	int		i;
	int		j;
	double	k;
	double	l;
	int		w;
	int		h;
	int		win_x;
	int		win_y;
	double	player_x;
	double	player_y;
	double	player_an;
	double	hight;
	double	ray_h;
	double	ray_v;
	double	ray;
	int		move_up;
	int		move_side;
	int		arrow;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_pars	*pars;
	int		mouse;
}	t_mlx;

char	**ft_split(char const *s, char c);
void	view(t_pars *pars);
void	view_lines(t_pars *pars);
void	ft_cleanline(char *s);
int		count_char(char c, char *s);
int		n_powtwo(char *s);
void	fill_texture(t_pars *pars, char *s);
void	parse_color(t_pars *pars, char *s);
int		check_num(int *colors, char **rgb, int size);
int		count_delimiter(char *s, char lim);
int		check_map_line(char *s);
int		parse_column(char *s);
int		check_valid_column(t_pars *pars, char *s);
int		ft_strpos_flex(char *s);
int		check_walls(char *s);
char	*clean_column_space(char *s);
void	map_check(t_pars *pars, char *s);
void	init_pars(t_pars *pars);
void	validate_texture(t_pars *pars, char *str);
void	validate(t_pars *pars);
void	set_color(t_pars *pars, char **colors, int typo);
void	fill_color(t_pars *pars, char *s);
int		check_box(t_pars *pars);
char	**ft_split_new(char const *s, char c, int *count);
char	**ft_flex_split(char const *s, int *count_flex);
t_pars	*parser(char *filecub);
void	square_box(t_pars *pars);
void	clear_tab(t_pars *pars);
int		check_walls(char *s);
int		check_medline(t_pars *pars, char *s);
int		left_space(char *s);
int		right_space(char *s);
int		check_line(char *s);
void	throw_error(char *s);
#endif
