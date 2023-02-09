/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aniouar <aniouar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:06:06 by aniouar           #+#    #+#             */
/*   Updated: 2023/02/09 17:46:24 by aniouar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "../include/cub3d.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_dir_texture
{
    char *no;
    char *so;
    char *we;
    char *ea;
    char *valid_fill;
} t_dir_texture;


typedef struct s_line
{
    char *line;
    struct s_line *prev;
    struct s_line *next;
} t_line;


typedef struct s_pars
{
    t_dir_texture *dir_texture;
    int valid_direction;
    int color_floor;
    int color_c;
    int valid_color;//
    char *vision;
    int valid_player;//
    int start_map;
    int valid_map;
    char **map;
    t_line *lines;
    t_line *prev_line;
} t_pars;

// view
void view(t_pars *pars);
void view_lines(t_pars *pars);

// color

// extra
void ft_cleanline(char *s);
int count_char(char c,char *s);
int n_powtwo(char *s);
void fill_texture(t_pars *pars,char *s);
void parse_color(t_pars *pars,char *s);
int check_num(int *colors, char **rgb, int size);
int count_delimiter(char *s,char lim);
int check_map_line(char *s);
int parse_column(char *s);
int check_valid_column(t_pars *pars,char *s);
int ft_strpos_flex(char *s);
int check_walls(char *s);
char *clean_column_space(char *s);
void map_check(t_pars *pars,char *s);
void init_pars(t_pars *pars);
void validate_texture(t_pars *pars,char *str);
void validate(t_pars *pars);
void set_color(t_pars *pars,char **colors,int typo);
void fill_color(t_pars *pars,char *s);
int check_box(t_pars *pars);
char    **ft_split_new(char const *s, char c,int *count);
char	**ft_flex_split(char const *s,int *count_flex);
t_pars* parser(char *filecub);
void square_box(t_pars *pars);
void clear_tab(t_pars *pars);
int check_walls(char *s);
int check_medline(t_pars *pars,char *s);
int left_space(char *s);
int right_space(char *s);
int check_line(char *s);
#endif