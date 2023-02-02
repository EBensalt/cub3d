/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:36:51 by aniouar           #+#    #+#             */
/*   Updated: 2023/02/02 00:29:12 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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


int *get_square(t_line *line,int index)
{
     int *square;
     int sizeline;
     
     //top bottom
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
     return (square);
}

int check_point(t_pars *pars,int c,int mod)
{
    if(pars->vision != 0)
    {
        if(c == pars->vision[0])
            return (1);
    }
    if(mod == 0)
    {
        if(c == '0' || c == '1')
             return (1);
    }
    else
    {
        if(c == '0')
            return (1);
    }
     
    return (0);
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
    x = 0;
    current = pars->lines;
    while(current)
    {
        i = 0;
        while(current->line[i])
        {
            if(check_point(pars,current->line[i],1))
            {
                square = get_square(current,i);
                if(current->prev == 0)
                {
                    
                    if(check_point(pars,square[1],0) == 0)
                    {
                        pars->valid_map = 0;
                        break;
                    }
                }
                if(current->prev != 0 && current->next != 0)
                {
                     if(check_point(pars,square[0],0) == 0)
                    {
                        pars->valid_map = 0;
                        break;
                    }

                     if(check_point(pars,square[1],0) == 0)
                    {
                        pars->valid_map = 0;
                        break;
                    }
                }
                if(current->next == 0)
                {
                    if(check_point(pars,square[0],0) == 0)
                    {
                        pars->valid_map = 0;
                        break;
                    }
                }
            }
            
            i++;
        }
        if(pars->valid_color == 0)
            break;
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
    else if(size == 1)
    {
        if(s[0] == '0')
          return (0);
    }
       
    return (1);
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
    int size;

    size = ft_strlen(line);
    i = 0;
    while(line[i] == '1')
        i++;
    if(i == size)
        return (1);
        
    return (0);
}

int check_box(t_pars *pars)
{
    t_line *current;
    int size;
    int firstsize;
    int status;
    
    status = 1;
    (void)size;
    current = pars->lines;

            firstsize = ft_strlen(current->line);
            if(check_box_column(current->line) == 0)
                 status = 0;
                     
             while(current)
            {
                size = ft_strlen(current->line);
                if(current->line[0] != '1' || current->line[size-1] != '1' )
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

int check_valid_column(t_pars *pars,char *s)
{
    int i;
    int size;
 
       
    if(parse_column(s) == 0 && pars->valid_player == 0)
    {
        pars->valid_map = 0;
        return (0);
    }
   
    size = ft_strlen(s);
    i = 0;
    while(++i < size)
    {
         if(pars->vision == 0)
        {
            
            if(s[i] == 'N' || s[i] == 'S' || s[i] == 'W' || s[i] == 'E')
            {
                pars->vision = malloc(2);
                pars->vision[0] = s[i];
                pars->vision[1] = '\0';
                pars->valid_player = 1;
            }
            else if(!(s[i] == '1' || s[i] == '0'))
            {
                pars->valid_map = 0;
                return (0); 
            }
                
        }
        else if(!(s[i] == '1' || s[i] == '0'))
            return (0);
            
    }
    if(size > 1)
    {
        if(!(s[0] == '1' && s[size-1] == '1'))
            return (0);
    }
    return (1);
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

void map_check(t_pars *pars,char *s)
{
    int count;
    int status;
    char **line;
    int size;
    int i;
    t_line *new;
    

    size = ft_strlen(s);
    status = 1;
    count = 0;
    line = ft_split_new(s,32,&count);
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
    {
           pars->valid_map = 0;
    }
      
       
        
    
    if(status == 0 && pars->start_map == 1)
    {
         pars->valid_map = 0;
    }
          
        

    

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
        
    i = -1;
    while(++i < count)
        free(line[i]);
     free(line);

    
}

