/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:35:56 by aniouar           #+#    #+#             */
/*   Updated: 2023/02/16 21:31:44 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void check_valid_dir(char **p_valid_fill, t_pars *pars)
{
    if(n_powtwo(*p_valid_fill) == 1 && ft_strlen(*p_valid_fill) == 4)
        pars->valid_direction = 1;
}

void checking_texture(t_pars *pars,char **texture)
{
    char **p_valid_fill;
    int size;

    size = ft_strlen(texture[0]);
    p_valid_fill = &pars->dir_texture->valid_fill;
    if(strcmp(texture[0],"NO") == 0 && size == 2)
    {
        *p_valid_fill = ft_strjoin(*p_valid_fill,"n");
        pars->dir_texture->no = ft_strdup(texture[1]);
    }
    if(strcmp(texture[0],"SO") == 0  && size == 2)
    {
        *p_valid_fill = ft_strjoin(*p_valid_fill,"s");
        pars->dir_texture->so = ft_strdup(texture[1]);
    }
    if(strcmp(texture[0],"WE") == 0  && size == 2)
    {
        *p_valid_fill = ft_strjoin(*p_valid_fill,"w");
        pars->dir_texture->we = ft_strdup(texture[1]);
    }
    if(strcmp(texture[0],"EA") == 0  && size == 2)
    {
        *p_valid_fill = ft_strjoin(*p_valid_fill,"e");
        pars->dir_texture->ea = ft_strdup(texture[1]);
    }
    check_valid_dir(p_valid_fill, pars);
}

void free_tab(char **tab)
{
    int i;

    i = -1;
    while(tab[++i])
        free(tab[i]);
    free(tab);
}

void fill_texture(t_pars *pars,char *s)
{
    char **texture;
    int count;
    int i;

    i = 0;
    if(s == 0)
        return;
    count = 0;
    texture = ft_split_new(s,32,&count);
    if(count > 2)
        throw_error("Error : Invalid texture");
    if(count == 2)
    {   
        if(strcmp(texture[0],s) == 0)
        {
            i = -1;
            while(++i < count)
                free(texture[i]);
            free(texture);
            return;
        }
        checking_texture(pars,texture);
    }
    free_tab(texture);
}

void validate_texture(t_pars *pars,char *str)
{
    int fd;
    char *s;
    (void)pars;
    if(str)
    {
        if(ft_strlen(str) >= 3)
        {
            ft_cleanline(&str[2]);
            s = &str[2];
            fd = open(s, O_RDONLY);
            if(fd == -1)
                throw_error("Error : Invalid texture");
            else
                close(fd);       
        }
        else
            throw_error("Error : Invalid texture");
    }
    else
        throw_error("Error : Invalid texture");
}