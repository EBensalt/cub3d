/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aniouar <aniouar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:35:56 by aniouar           #+#    #+#             */
/*   Updated: 2023/01/29 18:38:39 by aniouar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void fill_texture(t_pars *pars,char *s)
{
    char **texture;
    int count;
    char **p_valid_fill;

    if(s == 0)
        return;

    // newline in texture path

    //printf("fill_texture: %s\n",s);

    p_valid_fill = &pars->dir_texture->valid_fill;
    texture = ft_split(s,32,&count);
    if(count > 2)
    {
        pars->valid_map = 0;
        return;
    }
    if(strcmp(texture[0],s) == 0)
        return;
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

    if(n_powtwo(*p_valid_fill) == 1 && ft_strlen(*p_valid_fill) == 4)
        pars->valid_direction = 1;

    free(texture[0]);
    free(texture[1]);
    free(texture); 
}

void validate_texture(t_pars *pars,char *str)
{
    int fd;
    char *s;
    
     if(str != 0)
    {
        if(ft_strlen(str) >= 3)
        {
             ft_cleanline(&str[2]);
            s = &str[2];
            fd = open(s, O_RDONLY);
            if(fd == -1)
            {
               //  printf("checking texture\n");
                  pars->valid_map = 0;
            }
               
        }
        else
        {
             // printf("checking texture\n");
               pars->valid_map = 0;
        }
           
    }
}