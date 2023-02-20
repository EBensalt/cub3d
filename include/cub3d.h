/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:24:36 by ebensalt          #+#    #+#             */
/*   Updated: 2023/02/20 06:17:11 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../src/get_next_line/get_next_line.h"
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
	t_dir_texture	*tex;
	int				valid_direction;
	int				color_floor;
	int				color_c;
	int				valid_color;
	char			*vision;
	int				valid_player;
	int				start_map;
	int				end_map;
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
	void	*mini_img_1;
	void	*mini_img_0;
	void	*mini_img_p;
	int		i;
	int		j;
	double	x_h;
	double	y_h;
	double	x_v;
	double	y_v;
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
}	t_mlx;

int				handler_test1(int key, t_mlx *mlx);
int				handler_test2(int x, int y, t_mlx *mlx);
int				handler_test3(t_mlx *mlx);
void			move_up_player(t_mlx *mlx);
void			t3d_map(t_mlx *mlx);
t_mlx			*init_game_utils(t_mlx *mlx, int i, int j);
t_mlx			*init_game(t_mlx *mlx);
int				handler(int key, t_mlx *mlx);
void			handler_test_utils(t_mlx *mlx, double x, double y);
int				handler_test(t_mlx *mlx);
t_mlx			*h_inter(t_mlx *mlx, double tmp);
t_mlx			*ray(t_mlx *mlx, double tmp);
void			map_draw(t_mlx *mlx);
t_mlx			*img_gen(t_mlx *mlx);
t_mlx			*init_tex(t_mlx *mlx);
void			wall_draw_utils(t_mlx *mlx, double tmp, double i, double j);
void			wall_draw(t_mlx *mlx, double j, double tmp);
t_mlx			*v_inter_utils(t_mlx *mlx, double tmp);
t_mlx			*v_inter(t_mlx *mlx, double tmp);
t_mlx			*h_inter_utils(t_mlx *mlx, double tmp);
void			my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
unsigned int	get_color(t_mlx *mlx, t_tex *t, int i);
void			player_draw(t_mlx *mlx);
void			mini_map_utils(t_mlx *mlx, int i);
void			mini_map_draw(t_mlx *mlx);
int				ft_strcmp(char *s1, char *s2);
char			*ft_strstr(char *str, char *to_find);
char			**ft_split(char const *s, char c);
void			view(t_pars *pars);
void			view_lines(t_pars *pars);
void			ft_cleanline(char *s);
int				count_char(char c, char *s);
int				n_powtwo(char *s);
void			fill_texture(t_pars *pars, char *s);
void			parse_color(t_pars *pars, char *s);
int				check_num(int *colors, char **rgb, int size);
int				count_delimiter(char *s, char lim);
int				check_map_line(char *s);
int				parse_column(char *s);
int				check_valid_column(t_pars *pars, char *s);
int				ft_strpos_flex(char *s);
int				check_walls(char *s);
char			*clean_column_space(char *s);
void			map_check(t_pars *pars, char *s);
void			init_pars(t_pars *pars);
void			validate_texture(t_pars *pars, char *str);
void			validate(t_pars *pars);
void			set_color(t_pars *pars, char **colors, int typo);
void			fill_color(t_pars *pars, char *s);
int				check_box(t_pars *pars);
char			**ft_split_new(char const *s, char c, int *count);
t_pars			*parser(char *filecub);
void			square_box(t_pars *pars);
void			clear_tab(t_pars *pars);
int				check_walls(char *s);
int				check_medline(t_pars *pars, char *s);
int				left_space(char *s);
int				right_space(char *s);
int				check_line(char *s);
void			throw_error(char *s);
void			catch_out_head(t_pars *pars, char *s);
int				check_end_map(char *s);
int				copy_check_walls(char *s);
void			parse_color(t_pars *pars, char *s);
void			free_array(char **tab, int count);
char			*clean_column_space(char *s);
void			set_sizes(t_line *line, int *sizeprev, int *sizenext);
void			check_left_right(t_line *line, int index);
int				*get_square(t_line *line, int index);
int				check_point(t_pars *pars, int c, int mod);
void			check_first(t_pars *pars, t_line *line, int *square);
void			check_med(t_pars *pars, t_line *line, int *square);
void			check_bottom(t_pars *pars, t_line *line, int *square);
void			square_box(t_pars *pars);
int				check_map_line(char *s);
int				check_box_column(char *line);
int				check_box(t_pars *pars);
void			clear_tab(t_pars *pars);
int				parse_column(char *s);
void			init_pars(t_pars *pars);
void			validate(t_pars *pars);
int				get_count(t_line *line);
void			fill_map_lines(t_pars *pars);
void			free_map_list(t_pars *pars);
#endif
