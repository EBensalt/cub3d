/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aniouar <aniouar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:05:07 by aniouar           #+#    #+#             */
/*   Updated: 2023/02/09 19:12:09 by aniouar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void init_pars(t_pars *pars)
{
    pars->valid_direction = 0;
    pars->valid_map = 1;
    pars->start_map = 0;
    pars->valid_color = 0;
    pars->vision = 0;
    pars->color_floor = -1;
    pars->valid_player = 0;
    pars->color_c = -1;
    pars->dir_texture = malloc(sizeof(t_dir_texture));
    pars->dir_texture->valid_fill = ft_strdup("");
    pars->dir_texture->no = 0;
    pars->dir_texture->so = 0;
    pars->dir_texture->we = 0;
    pars->dir_texture->ea = 0;
    pars->map = 0;
    pars->lines = 0;
    pars->prev_line = 0;
}

void validate(t_pars *pars)
{
    validate_texture(pars,pars->dir_texture->no);
    validate_texture(pars,pars->dir_texture->we);
    validate_texture(pars,pars->dir_texture->ea);
    validate_texture(pars,pars->dir_texture->so);

    if(pars->valid_direction == 0)
    {
        printf("Error : Invalid texture\n");
        exit(0);
    }
     if(pars->valid_color == 0)
    {
        printf("Error : Invalid Color\n");
        exit(0);
    }
    if(pars->start_map == 0)
    {
        printf("Error : Invalid Map\n");
        exit(0);
    }

     if(pars->valid_player == 0)
    {
        printf("Error : Invalid Player\n");
        exit(0);
    }
    /*
        if(pars->vision == 0)
    {
        pars->valid_map = 0;
        printf("Error : Invalid Map 110\n");
        exit(0);
    }
    */
    
}

int get_count(t_line *line)
{
    t_line *current;
    int count;

    count = 0;
    current = line;
    while(current)
    {
        count++;
        current = current->next;
    }
    return (count);
}

void fill_map_lines(t_pars *pars)
{
    int count;
    int i;
    t_line *current;
    count = get_count(pars->lines);
    pars->map= malloc(sizeof(char *) * (count+1));

    
    current = pars->lines;
    i = 0;
     while(current)
    {
        pars->map[i++] = ft_strdup(current->line);
        current = current->next;
    }
    pars->map[i] = 0;

}

void free_map_list(t_pars *pars)
{
    t_line *current;
    
    current = pars->lines;
    while(current)
    {
        free(current->line);
        current = current->next;
    }
}

void more_parser(t_pars *pars)
{
    validate(pars);
    square_box(pars);
    fill_map_lines(pars);
    //clear_tab(pars);
    
        if(pars->lines != 0)
        { 
            if(check_box(pars) == 0)
            {
                printf("Error : Invalid map 112\n");
                exit(0);
            }
        }
    free_map_list(pars);
}

void core_parser(t_pars *pars, char *s)
{
    // if(s != 0)
    //     ft_cleanline(s);
    if(!pars->valid_direction || !pars->valid_color)
    {
        fill_color(pars,s);
        fill_texture(pars,s);
    }
    else if(pars->valid_direction && pars->valid_color)
       map_check(pars,s);
}

t_pars* parser(char *filecub)
{
    int fd;
    int i;
    char *s;
    t_pars *pars;

    pars = malloc(sizeof(t_pars));
    init_pars(pars);
    fd = open(filecub, O_RDONLY);
    if(fd == -1)
    {
        printf("Error : invalid map file\n");
        exit(0);
    }
    i = 0;
    s = get_next_line(fd);
    while(s)
    {
        ft_cleanline(s);
        core_parser(pars,s);
        free(s);
        s = get_next_line(fd);
    }
    //view(pars);
    //view_lines(pars);
    more_parser(pars);
    
    return (pars);
}