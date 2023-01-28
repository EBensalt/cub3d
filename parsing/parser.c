/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aniouar <aniouar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:05:07 by aniouar           #+#    #+#             */
/*   Updated: 2023/01/28 21:43:21 by aniouar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"


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

    if(s == 0)
        return;

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

void parse_color(t_pars *pars,char *s)
{
    int size;

    size = ft_strlen(s);
    if(size > 1)
    {
        if(s[0] == ',' || s[size-1] == ',')
            pars->valid_map = 0;
    }
}

void set_color(t_pars *pars,char **colors,int typo)
{
    int  *tab;
    int count;
    int  color;
    char **rgb;
    
    parse_color(pars,colors[1]);
    tab = malloc(sizeof(int) * 3);
    rgb = ft_split(colors[1],',',&count);
     //printf("color %s %i\n",colors[1],count);
   // printf("colors is %s count is %i \n",colors[1],count);
     //printf("(%s) (%s) (%s)\n",rgb[0],rgb[1],rgb[2]);
    if(count == 3)
    {
        tab[0] = atoi(rgb[0]);
        tab[1] = atoi(rgb[1]);   
        tab[2] = atoi(rgb[2]);
    
        color = (tab[0] << 16) | (tab[1] << 8) | tab[2];
        if(typo == 0)
            pars->color_floor = color;
        else
            pars->color_c = color;
    }
   
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

    if(s == 0)
        return;

    
    if(pars->valid_color)
          return;
   
     colors = ft_split(s,32,&count);
     if(strcmp(colors[0],s) == 0)
        return;
     if(strcmp(colors[0],"F") == 0 && count == 2)
        set_color(pars,colors,0);
     if(strcmp(colors[0],"C") == 0  && count == 2)
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

void ft_cleanline(char *s)
{
    int i;
    int pos;
    int size;

    pos = -1;
    size = ft_strlen(s);
    i = -1;
    while(++i < size)
    {
        if(s[i] == '\n')
        {
            pos = i;
            break;
        }
    }
    if(pos != -1)
        s[pos] = '\0';
}

void parse_column(t_pars *pars,char *s)
{
    int size;

    
    size = ft_strlen(s);
    (void)pars;
}

int check_valid_column(t_pars *pars,char *s)
{
    int i;
    int size;

    if(strcmp(s,"\n") == 0)
        return (0);
    ft_cleanline(s);
    size = ft_strlen(s);
    i = 0;
    while(++i < size-2)
    {
         if(pars->vision == 0)
        {
            if(s[i] == 'N' || s[i] == 'S' || s[i] == 'W' || s[i] == 'E')
            {
                pars->vision = malloc(2);
                pars->vision[0] = s[i];
                pars->vision[1] = '\0';
            }
            else if(!(s[i] == '1' || s[i] == '0'))
            {
               //printf("legend char %c\n",s[i]);
                pars->valid_map = 0;
                return (0); 
            }
                
        }
        else if(!(s[i] == '1' || s[i] == '0'))
        {
            //printf("legend char %c\n",s[i]);
            return (0);
        }
            
    }
    if(size > 1)
    {
        if(!(s[0] == '1' && s[size-1] == '1'))
        {
            //printf("walls %s %c %c\n",s,s[0],s[size-1]);
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
    t_line *new;
    
    (void)pars;
    status = 1;
    line = ft_split(s,32,&count);
   // printf("count words per line %i:%s\n",count,s);


    i = 0;
    while(i < count)
    {
        //printf("after splited %s\n",s);
        if(check_valid_column(pars,line[i]) == 0)
        {
           // printf("right %s\n",line[i]);
            status = 0;
            break;
        }
        i++;
    }
    if(status == 0 && pars->start_map == 1)
        pars->valid_map = 0;

    if(status == 1 && pars->start_map == 0)
    {
        pars->start_map = 1;
    }

    if(pars->valid_map == 1 &&  pars->start_map == 1)
    {
         ft_cleanline(s);
        if(pars->prev_line == 0)
        {
            
            pars->lines = malloc(sizeof(t_line));
            pars->lines->line = ft_strdup(s);
            pars->lines->next = 0;
            pars->prev_line = pars->lines; 
        }
        else
        {
            new =  malloc(sizeof(t_line));
            new->line = ft_strdup(s);
            new->next = 0;
            pars->prev_line->next = new;
            pars->prev_line = new;
        }
    }
        
    /*
        if(strcmp(s,"\n") == 0 && pars->start_map == 1)
              pars->valid_map = 0;
    */
}

void view_lines(t_pars *pars)
{
    t_line *current;

    current = pars->lines;

    while(current)
    {
        printf("line %s\n",current->line);
        current = current->next;
    }
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
    pars->lines = 0;
    pars->prev_line = 0;
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
                pars->valid_map = 0;
        }
        else
            pars->valid_map = 0;
    }
}

void validate(t_pars *pars)
{
   
    validate_texture(pars,pars->dir_texture->no);
    validate_texture(pars,pars->dir_texture->we);
    validate_texture(pars,pars->dir_texture->ea);
    validate_texture(pars,pars->dir_texture->so);


    if(pars->vision == 0)
        pars->valid_map = 0;
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
        dprintf(1,"Error\n");
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
    view_lines(pars);
    validate(pars);
    if(pars->valid_map == 0)
    {
        dprintf(1,"Error");
        exit(0);
    }
     
}