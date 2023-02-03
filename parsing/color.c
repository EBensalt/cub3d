/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aniouar <aniouar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:30:02 by aniouar           #+#    #+#             */
/*   Updated: 2023/02/03 16:32:47 by aniouar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void parse_color(t_pars *pars,char *s)
{
    int size;

    size = ft_strlen(s);
    if(size > 1)
    {
        if(s[0] == ',' || s[size-1] == ',')
        {
            pars->valid_map = 0;
            
            printf("Error : Invalid Color\n");
            exit(0);
        }       
    }
}

void free_array(char **tab,int count)
{
    int i;

    i = -1;
    while(++i < count)
         free(tab[i]);
    free(tab);
}

void check_set_color(t_pars *pars, char **colors, int *tab, char **rgb, int typo)
{
    int  color;
    
    tab[0] = atoi(rgb[0]);
    tab[1] = atoi(rgb[1]);   
    tab[2] = atoi(rgb[2]);
    if(check_num(rgb, 3) == 0 || count_delimiter(colors[1],',') != 2)
    {
        pars->valid_map = 0;
        printf("Error : Invalid Color\n");
        exit(0);
    }
    if( (tab[0] < 0 || tab[0] > 255) || (tab[1] < 0 || tab[1] > 255)
            || (tab[2] < 0 || tab[2] > 255))
    {
        pars->valid_map = 0;
            printf("Error : Invalid Color\n");
        exit(0);
    }
    color = (tab[0] << 16) | (tab[1] << 8) | tab[2];
    if(typo == 0)
        pars->color_floor = color;
    else
        pars->color_c = color;
}

void set_color(t_pars *pars,char **colors,int typo)
{
    int  *tab;
    int count;
    char **rgb;
    
    parse_color(pars,colors[1]);
    tab = malloc(sizeof(int) * 3);
    rgb = ft_split_new(colors[1],',',&count);
    if(count == 3)
        check_set_color(pars,colors,tab,rgb,typo);
    free_array(rgb, count);
    free(tab);
}

void catch_colors(char **colors, int count, t_pars *pars)
{
    if(strcmp(colors[0],"F") == 0 && count == 2)
    {
        if(pars->color_floor != -1)
        {
            printf("Error : Duplicated Color\n");
            exit(0);
        }
        else
                set_color(pars,colors,0);
    }
    if(strcmp(colors[0],"C") == 0  && count == 2)
    {
        if(pars->color_c != -1)
        {
            printf("Error : Duplicated Color\n");
            exit(0);
        }
        else
            set_color(pars,colors,1);
    }
}

void fill_color(t_pars *pars,char *s)
{
     char **colors;
     int count;
     int i;

    if(pars->valid_color)
          return;
     colors = ft_split_new(s,32,&count);
     if(count == 2)
     {
        if(strcmp(colors[0],s) == 0)
        {
            i = -1;
            while(++i < count)
                free(colors[i]);
            free(colors); 
            return;
        }
        catch_colors(colors, count , pars);
        if(pars->color_floor != -1 && pars->color_c != -1)
                pars->valid_color = 1;
     }
    free_array(colors,count);
}