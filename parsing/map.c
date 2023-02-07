/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aniouar <aniouar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:36:51 by aniouar           #+#    #+#             */
/*   Updated: 2023/02/07 19:08:37 by aniouar          ###   ########.fr       */
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
        if(c == '0' || c == '1' || c == pars->vision[0])
             return (1);
    }
    else
    {
        if(c == '0')
            return (1);
    }
     
    return (0);
}

void check_first(t_pars *pars,t_line *line, int *square)
{
    if(line->prev == 0)
    {
        if(check_point(pars,square[1],0) == 0)
        {
            pars->valid_map = 0;
           
            printf("Error : Invalid Map 101\n");
            exit(0);
        }
    }
}

void check_med(t_pars *pars,t_line *line, int *square,char c)
{

     if(line->prev != 0 && line->next != 0)
    {
        if(check_point(pars,square[0],0) == 0)
        {
            pars->valid_map = 0;
            printf("Error : Invalid Map 103\n");
            exit(0);
        }
        if(check_point(pars,square[1],0) == 0)
        {
            pars->valid_map = 0;
            printf("line : %s\n",line->line);
            printf("what means %i and im %c\n",square[1],c);
            printf("Error : Invalid Map 104\n");
            exit(0);
        }
    }
}

void check_bottom(t_pars *pars,t_line *line, int *square)
{
    if (line->next == 0)
    {
        if(check_point(pars,square[0],0) == 0)
        {
            pars->valid_map = 0;
            printf("Error : Invalid Map 105 \n");
            exit(0);
        }
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
                check_med(pars,current,square,current->line[i]);
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
    //printf("from check_box_column %s start:%i end:%i\n",line,i,x);
    while(i < x)
    {
        if(line[i] == '1')
            i++;
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
    {
         printf("line %s 312\n",current->line);
          status = 0;
    }
           
    while(current)
    {
        size = ft_strlen(current->line);
        if(!check_walls(current->line))
        {
            printf("line %s 313\n",current->line);
              status = 0;
        }
        if(current->next == 0)
        {
            if(check_box_column(current->line) == 0)
            {
                 printf("line %s 314\n",current->line);
                  status = 0;        
            }
                   
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


void set_player(t_pars *pars,char *s,int i)
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
        printf("Error :  106\n");
        exit(0);
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
    {
        //printf("line %s with left space is %i and size of %i \n",s,left_space(s),size);
        return (0);
    }
        
    
    return (1);
}

int check_valid_column(t_pars *pars,char *s)
{
    int i;
    int size;

    if(parse_column(s) == 0 || ft_strlen(s) == 0)
        return (0);
    size = ft_strlen(s);
    i = 0;
    while(++i < size)
    {
        if(pars->vision == 0)
            set_player(pars,s,i);
        else if(!(s[i] == '1' || s[i] == '0'))
            return (0);
    }
    if(size > 1)
    {
        if(check_walls(s))
            return (0);
    }
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
    {
           pars->valid_map = 0;
           printf("Error : Invalid Map 108\n");
           exit(0);
    }
}

void map_check(t_pars *pars,char *s)
{
    int status;
    
    status = 1;
  
    if(pars->start_map == 0)
    {
        if(check_walls(s) == 0)
            status = 0;
    }
    else
    {
        if(check_medline(pars,s) == 0)
            status = 0;
    }
    
    printf("line %s with status of %i and size %zu\n",s,status,ft_strlen(s));
    check_errors_map(pars,status);
    if(status)
        fill_lines(pars,s);
}

