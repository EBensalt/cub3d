/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aniouar <aniouar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:30:02 by aniouar           #+#    #+#             */
/*   Updated: 2023/01/29 18:35:16 by aniouar          ###   ########.fr       */
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
           // printf("parsing color\n");
            pars->valid_map = 0;
        }
            
    }
}

void set_color(t_pars *pars,char **colors,int typo)
{
    int  *tab;
    int count;
    int  color;
    char **rgb;
    
    ft_cleanline(colors[1]);
    parse_color(pars,colors[1]);
    tab = malloc(sizeof(int) * 3);
    //printf("color %s\n",colors[1]);
    rgb = ft_split(colors[1],',',&count);
     //printf("color %s %i\n",colors[1],count);
  // printf("colors is %s count is %i and count lim %i\n",colors[1],count,count_delimiter(colors[1],','));
     //printf("(%s) (%s) (%s)\n",rgb[0],rgb[1],rgb[2]);
    if(count == 3)
    {
        tab[0] = atoi(rgb[0]);
        tab[1] = atoi(rgb[1]);   
        tab[2] = atoi(rgb[2]);
        
       if(check_num(rgb, 3) == 0 || count_delimiter(colors[1],',') != 2)
       {
            //printf("in colors part\n");
            
            pars->valid_map = 0;
            //exit(0);
       }

       if( (tab[0] < 0 || tab[0] > 255) || (tab[1] < 0 || tab[1] > 255)
             || (tab[2] < 0 || tab[2] > 255))
        {
            //printf("rgb colors \n");
            pars->valid_map = 0;
        }
           
            
            
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