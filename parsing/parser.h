/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aniouar <aniouar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:06:06 by aniouar           #+#    #+#             */
/*   Updated: 2023/01/27 12:55:45 by aniouar          ###   ########.fr       */
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



typedef struct s_pars
{
    t_dir_texture *dir_texture;
    int valid_direction;
    int color_floor;
    int color_c;
    int valid_color;
    char *vision;
    int start_map;
    int valid_map;
} t_pars;

char    **ft_split(char const *s, char c,int *count);
void parser(char *filecub);
#endif