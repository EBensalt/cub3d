/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:36:51 by aniouar           #+#    #+#             */
/*   Updated: 2023/02/16 21:31:53 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char *clean_column_space(char *s)
{
    int pos;
    size_t size;
    char *tmp;

    pos = ft_strpos_flex(s); 
    size = ft_strlen(s);
    tmp = ft_substr(s,(pos),size,0);
    pos = ft_strpos_flex(tmp);
    free(s);
    return (tmp);
}

void set_sizes(t_line *line, int *sizeprev,int *sizenext)
{
    if(line->prev != 0)
        *sizeprev = ft_strlen(line->prev->line);
    else
        *sizeprev = -1;
    if(line->next != 0)
        *sizenext = ft_strlen(line->next->line);
    else
        *sizenext = -1;      
}

void check_left_right(t_line *line,int index)
{
    int sizeline;
    char c;
    
    sizeline = ft_strlen(line->line);
    c = line->line[index];

    if(c == '0')
    {
        if(line->line[index+1] == 32 || line->line[index-1] == 32)
            throw_error("Error: Invalid map");
    }
}

int *get_square(t_line *line,int index)
{
     int *square;
     int sizeline;
     
     square = malloc(sizeof(int) * 2);
     if(line->prev == 0)
        square[0] = -1;
      else
      {
          sizeline = ft_strlen(line->prev->line);
          if(index < sizeline)
              square[0] = line->prev->line[index];
          else
              square[0] = -1;
      }
      if(line->next == 0)
        square[1] = -1;
      else
      {
          sizeline = ft_strlen(line->next->line);
          if(index < sizeline)
              square[1] = line->next->line[index];
          else
              square[1] = -1;
      }
      check_left_right(line,index);
     return (square);
}

int check_point(t_pars *pars,int c,int mod)
{
    if(mod == 0)
    {
        if(pars->vision)
            if(c == pars->vision[0])
                return (1);
        if(c == '0' || c == '1')
        {
            return (1);
        }    
    }
    else
    {
        if(c == '0' || c == pars->vision[0])
            return (1);
    }
     
    return (0);
}

void check_first(t_pars *pars,t_line *line, int *square)
{
    if(line->prev == 0)
    {
        
        if(check_point(pars,square[1],0) == 0)
            throw_error("Error : Invalid Map 101");
    }
}

void check_med(t_pars *pars,t_line *line, int *square)
{

     if(line->prev != 0 && line->next != 0)
    { 
        if(check_point(pars,square[0],0) == 0)
            throw_error("Error : Invalid Map 103");
        if(check_point(pars,square[1],0) == 0)
            throw_error("Error : Invalid Map 104");
    }
}

void check_bottom(t_pars *pars,t_line *line, int *square)
{
    if (line->next == 0)
    {
        if(check_point(pars,square[0],0) == 0)
            throw_error("Error : Invalid Map 105");
    }
}


void square_box(t_pars *pars)
{
    t_line *current;
    int sizeprev;
    int sizenext;
    int i;
    int x;
    int *square;

    sizeprev = 0;
    sizenext = 0;
    current = pars->lines;
    while(current)
    {
        i = left_space(current->line);
        x = right_space(current->line);
        while(i <= x)
        {
            if(check_point(pars,current->line[i],1))
            {
                square = get_square(current,i);
                check_first(pars,current,square);
                check_med(pars,current,square);
                check_bottom(pars,current,square);
                free(square);
            }
            i++;
        }
        if(pars->valid_color == 0)
            break;
        current = current->next;
    }
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

int check_box_column(char *line)
{
    int i;
    int x;
    int size;

    size = ft_strlen(line);
    i = left_space(line);
    x = right_space(line);
    while(i < x)
    {
        if(line[i] == '1')
            i++;
        else
            break;
    }    
    
    if(i == x)
        return (1);
    return (0);
}

int check_box(t_pars *pars)
{
    t_line *current;
    int size;
    int status;
    
    status = 1;
    current = pars->lines;
    if(check_box_column(current->line) == 0)
          status = 0;           
    while(current)
    {
       
        size = ft_strlen(current->line);
        if(!check_line(current->line))
              status = 0;       
        if(current->next == 0)
        {
            if(check_box_column(current->line) == 0)
                  status = 0;        
        }
        if(status == 0)
            break;
        current = current->next;
    }
    return (status);
}

void clear_tab(t_pars *pars)
{
    t_line *current;
    
    current = pars->lines;
    while(current)
    {
        current->line = clean_column_space(current->line);
        current = current->next;
    }
}

int parse_column(char *s)
{
    int size;

    size = ft_strlen(s);
    if(size > 1)
    {
        if(s[0] !=  '1' || s[size-1] != '1')
            return (0);
    }
    else if(left_space(s) == size && size > 0)
        return (0);
    return (1);
}



void fill_lines(t_pars *pars,char *s)
{
    t_line *new;
    int size;
    
    size = ft_strlen(s);
    if(pars->valid_map == 1 &&  pars->start_map == 1 && size > 0)
    {
        if(pars->prev_line == 0)
        {
            pars->lines = malloc(sizeof(t_line));
            pars->lines->line = ft_strdup(s);
            pars->lines->next = 0;
            pars->lines->prev = 0;
            pars->prev_line = pars->lines; 
        }
        else
        {
            new =  malloc(sizeof(t_line));
            new->line = ft_strdup(s);
            new->prev = pars->prev_line;
            new->next = 0;
            pars->prev_line->next = new;
            pars->prev_line = new;
        }
    }
}

void check_errors_map(t_pars *pars,int status)
{
    if(status == 1 && pars->start_map == 0)
        pars->start_map = 1;
    if(status == 0 && pars->start_map == 1)
        throw_error("Error : Invalid Map 108");
}

void map_check(t_pars *pars,char *s)
{
    int status;
    status = 1;
  
    if(pars->start_map == 0)
    {
        if(check_walls(s) == 0)
            status = 0;
        if(status)
            pars->start_map = 1;
    }
    else
    {
        if(check_medline(pars,s) == 0)
            status = 0;
    }
    check_errors_map(pars,status);
    if(status)
        fill_lines(pars,s);
}

