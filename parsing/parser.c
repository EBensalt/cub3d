/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aniouar <aniouar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:05:07 by aniouar           #+#    #+#             */
/*   Updated: 2023/01/26 16:11:57 by aniouar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
    struct pars
        struct for direction texture
        struct for color for floor and c 
        valid_direction
        valid_color

*/

void fill_texture(t_pars *pars,char *s)
{
    char **texture;
    char **p_valid_fill;

    // newline in texture path

    p_valid_fill = &pars->dir_texture->valid_fill;
    texture = ft_split(s,32);
    if(strcmp(texture[0],"NO") == 0)
    {
        *p_valid_fill = ft_strjoin(*p_valid_fill,"n");
        pars->dir_texture->no = ft_strdup(texture[1]);
    }
    if(strcmp(texture[0],"SO") == 0)
    {
        *p_valid_fill = ft_strjoin(*p_valid_fill,"s");
        pars->dir_texture->so = ft_strdup(texture[1]);
    }
    if(strcmp(texture[0],"WE") == 0)
    {
        *p_valid_fill = ft_strjoin(*p_valid_fill,"w");
        pars->dir_texture->we = ft_strdup(texture[1]);
    }
    if(strcmp(texture[0],"EA") == 0)
    {
        *p_valid_fill = ft_strjoin(*p_valid_fill,"e");
        pars->dir_texture->ea = ft_strdup(texture[1]);
    }

    if(strcmp(*p_valid_fill,"nswe") == 0)
        pars->valid_direction = 1;

    free(texture[0]);
    free(texture[1]);
    free(texture); 
}

void parser(char *filecub)
{
    int fd;
    char *s;
    t_pars *pars;
    
    pars = malloc(sizeof(t_pars));
    pars->valid_direction = 0;
    pars->valid_color = 0;
    pars->dir_texture = malloc(sizeof(t_dir_texture));
    pars->dir_texture->valid_fill = ft_strdup("");
    pars->dir_texture->no = 0;
    pars->dir_texture->so = 0;
    pars->dir_texture->we = 0;
    pars->dir_texture->ea = 0;
    
    fd = open(filecub, O_RDONLY);
    
    s = get_next_line(fd);
    while(1)
    {
        //printf("line:%s\n",s);
        if(!pars->valid_direction)
           fill_texture(pars,s);
        if(pars->valid_direction && !pars->valid_color)
           fill_color(pars,s);
        free(s);
        s = 0;
        s = get_next_line(fd);
        if(s == 0)
            break;
    }

    printf("no %s\n",pars->dir_texture->no);
    printf("so %s\n",pars->dir_texture->so);
    printf("we %s\n",pars->dir_texture->we);
    printf("ea %s\n",pars->dir_texture->ea);
    
    while(1);
}