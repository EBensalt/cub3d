/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aniouar <aniouar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:48:13 by aniouar           #+#    #+#             */
/*   Updated: 2023/02/07 18:48:13 by aniouar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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





int check_num(char **colors, int size)
{
    int i;
    int x;
    
    i = -1;
    while(++i < size)
    {

        x = -1;
        while(colors[i][++x])
        {
            if(!(colors[i][x] >= '0' && colors[i][x] <= '9'))
                return (0);
        }    
    }
    return (1);
}

int count_delimiter(char *s,char lim)
{
    int i;
    int count;

    count = 0;
    i = -1;
    while(s[++i])
    {
        if(s[i] == lim)
            count++;
    }
    return (count);
}

int ft_strpos_flex(char *s)
{
    int i;

    i = -1;
    while(s[++i] == 32 || s[i] == '\t' || s[i] == '\r');

    return (i);
}

int left_space(char *s)
{
    int i;
     int size;

    size = ft_strlen(s);

    if(size == 0)
        return (-1);

    i = -1;
    while(s[++i] == 32);
    return (i);
}

int right_space(char *s)
{
    int x;
    int size;

    size = ft_strlen(s);

    if(size == 0)
        return (-1);
    x = size;
    while(s[--x] == 32);
    return (x);
}



int check_walls(char *s)
{
    int i;
    int size;
    int x;

    size = ft_strlen(s);
    x = right_space(s);
    i = left_space(s);


    if(i != -1 && x != -1)
    {
        if(s[i] == '1' && s[x] == '1')
            return (1);
    }
    return (0);
}

int check_medline(t_pars *pars,char *s)
{
    int i;
    int size;
    int x;

    size = ft_strlen(s);
    x = right_space(s) + 1;
    i = left_space(s);

    if(check_walls(s) == 0)
        return (0);

    while(++i < x)
    {
        if(s[i] >= 'A' && s[i] <= 'Z')
        {
            if(pars->valid_player == 0)
            {
                pars->vision = malloc(2);
                pars->vision[0] = s[i];
                pars->vision[1] = '\0';
                pars->valid_player = 1;
            }
            else
                printf("Error : duplicated player\n");
        }
        else if(s[i] == 32)
            ;
        else if(!(s[i] == '0' || s[i] == '1'))
        {
            printf("here\n");
            return (0);
        }
        i++;
    }
    return (1);
}



