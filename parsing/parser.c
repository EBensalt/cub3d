/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aniouar <aniouar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:05:07 by aniouar           #+#    #+#             */
/*   Updated: 2023/01/27 13:13:33 by aniouar          ###   ########.fr       */
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

int count_char(char c,char *s)
{
    int i;
    int count;

    count = 0;
    i = -1;
    while(s[++i])
    {
        if(s[i] == c)
            count++;
    }
    return (count);
}

int n_powtwo(char *s)
{
     int i;

     i = -1;
     while(s[++i])
     {
         if(count_char(s[i],s) != 1)
             return (0);
     }
     return (1); 
}

void fill_texture(t_pars *pars,char *s)
{
    char **texture;
    int count;
    char **p_valid_fill;

    // newline in texture path

    //printf("fill_texture: %s\n",s);

    p_valid_fill = &pars->dir_texture->valid_fill;
    texture = ft_split(s,32,&count);
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

void set_color(t_pars *pars,char **colors,int typo)
{
    int  *tab;
    int count;
    int  color;
    char **rgb;
    
    tab = malloc(sizeof(int) * 3);
    rgb = ft_split(colors[1],',',&count);
    tab[0] = atoi(rgb[0]);
    tab[1] = atoi(rgb[1]);
    tab[2] = atoi(rgb[2]);
    color = (tab[0] << 16) | (tab[1] << 8) | tab[2];
    if(typo == 0)
        pars->color_floor = color;
    else
        pars->color_c = color;
    free(rgb[0]);
    free(rgb[1]);
    free(rgb[2]);
    free(rgb);
    free(tab);
}

void fill_color(t_pars *pars,char *s)
{
     char **colors;
     int count;
          
     if(pars->valid_color)
          return;
     colors = ft_split(s,32,&count);
     if(strcmp(colors[0],s) == 0)
        return;
     if(strcmp(colors[0],"F") == 0)
        set_color(pars,colors,0);
     if(strcmp(colors[0],"C") == 0)
        set_color(pars,colors,1);
     
     if(pars->color_floor != -1 && pars->color_c != -1)
            pars->valid_color = 1;
    free(colors[0]);
    free(colors[1]);
    free(colors); 
}

int check_map_line(char *s)
{
    int i;

    i = -1;
    while(s[++i])
    {
        if(!(s[i] == '0' || s[i] == '+'))
            return (0);
    }
    return(1);
}

int check_valid_column(t_pars *pars,char *s)
{
    int i;
    int size;

    size = ft_strlen(s);
   
    i = 0;
    while(++i < size-1)
    {
        if(pars->vision == 0)
        {
            if(s[i] == 'N' || s[i] == 'S' || s[i] == 'W' || s[i] == 'E')
                pars->vision = ft_strdup("N");
        }
        
        else if(!(s[i] == '1' || s[i] == '0'))
            return (0);
    }
    if(size > 1)
    {
        
        if(!(s[0] == '1' && s[size-1] == '1'))
        {
            printf("walls %s\n",s);
            return (0);
        }
            
    }
    return (1);
}

void map_check(t_pars *pars,char *s)
{
    int count;
    int status;
    char **line;
    int i;
    
    (void)pars;
    status = 1;
    line = ft_split(s,32,&count);
    //printf("count words per line %i\n",count);

        

    i = 0;
    while(i < count)
    {
        if(check_valid_column(pars,line[i]) == 0)
        {
            status = 0;
            break;
        }
        i++;
    }

    if(status == 1 && pars->start_map == 0)
        pars->start_map = 1;

    if(status == 0 && pars->start_map == 1)
        pars->valid_map = 0;
    
    /*
        if(strcmp(s,"\n") == 0 && pars->start_map == 1)
              pars->valid_map = 0;
    */
}

void view(t_pars *pars)
{
    printf("no %s\n",pars->dir_texture->no);
    printf("so %s\n",pars->dir_texture->so);
    printf("we %s\n",pars->dir_texture->we);
    printf("ea %s\n",pars->dir_texture->ea);
    printf("color floor %d\n",pars->color_floor);
    printf("color c %i\n",pars->color_c);
    printf("vision %s\n",pars->vision);
    printf("valid color %d\n",pars->valid_color);
    printf("valid texture %d\n",pars->valid_direction);
    printf("valid map %d\n",pars->valid_map);
    
}

void init_pars(t_pars *pars)
{
    pars->valid_direction = 0;
    pars->valid_map = 1;
    pars->start_map = 0;
    pars->valid_color = 0;
    pars->vision = 0;
    pars->color_floor = -1;
    pars->color_c = -1;
    pars->dir_texture = malloc(sizeof(t_dir_texture));
    pars->dir_texture->valid_fill = ft_strdup("");
    pars->dir_texture->no = 0;
    pars->dir_texture->so = 0;
    pars->dir_texture->we = 0;
    pars->dir_texture->ea = 0;
}

void parser(char *filecub)
{
    int fd;
    char *s;
    t_pars *pars;
    
    pars = malloc(sizeof(t_pars));
    
    init_pars(pars);
   
    
    fd = open(filecub, O_RDONLY);
    
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
        s = get_next_line(fd);
        if(s == 0)
            break;
    }

    view(pars);
    while(1);
}