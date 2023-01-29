/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aniouar <aniouar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:05:07 by aniouar           #+#    #+#             */
/*   Updated: 2023/01/29 18:50:12 by aniouar          ###   ########.fr       */
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
    pars->lines = 0;
    pars->prev_line = 0;
}



void validate(t_pars *pars)
{
   
    validate_texture(pars,pars->dir_texture->no);
    validate_texture(pars,pars->dir_texture->we);
    validate_texture(pars,pars->dir_texture->ea);
    validate_texture(pars,pars->dir_texture->so);

    /*
    
    */
    if(pars->vision == 0)
    {
         //  printf("checking player\n");
           pars->valid_map = 0;
    }
        
}

void parser(char *filecub)
{
    int fd;
    char *s;
    t_pars *pars;

    
    
    pars = malloc(sizeof(t_pars));
    
    init_pars(pars);
   
    
    fd = open(filecub, O_RDONLY);
    if(fd == -1)
    {
        //dprintf(1,"Error\n");
        exit(0);
    }
    s = get_next_line(fd);
    while(1)
    {
        if(!pars->valid_direction || !pars->valid_color)
        {
             fill_color(pars,s);
             fill_texture(pars,s);
        }
        else if(pars->valid_direction && pars->valid_color)
        {
            //printf("map check: %s\n",s);
            map_check(pars,s);
        }
            
        free(s);
        s = 0;
        if(!pars->valid_map)
            break;
        s = get_next_line(fd);
        if(s == 0)
            break;
    }
    // more validation
    //view(pars);
    //while(1);
   //view_lines(pars);
   
    validate(pars);
    if(pars->valid_map == 0)
    {
        dprintf(1,"Error");
        exit(0);
    }
     
}