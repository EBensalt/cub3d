/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aniouar <aniouar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:36:51 by aniouar           #+#    #+#             */
/*   Updated: 2023/01/29 18:45:02 by aniouar          ###   ########.fr       */
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
    return (tmp);
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

int check_valid_column(t_pars *pars,char *s)
{
    int i;
    int size;

    ft_cleanline(s);
    if(strcmp(s,"\n") == 0)
    {
        //printf("new line\n");
         return (0);
    }
       
    
    if(parse_column(s) == 0 && pars->valid_player == 0)
    {
       // printf("parse column %s\n",s);
        pars->valid_map = 0;
        return (0);
    }
    //
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
               //printf("parsing line map 1\n");
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
 
    //(void)newline;
    line = ft_split(s,32,&count);
   //printf("count words per line %i:%s\n",count,s);

    //printf("line with count %i :\n",count);
    i = 0;
    while(i < count)
    {
        //printf("after splited %s\n",s);
        line[i] = clean_column_space(line[i]);
       // printf(" %s ",line[i]);
        if(check_valid_column(pars,line[i]) == 0)
        {
            
            //
          // printf("wired line[%i]:%s with size %zu\n",i,line[i],ft_strlen(line[i]));
           // printf("right %s\n",line[i]);
            status = 0;
            break;
        }
        i++;
    }
    ///printf("\n");
    if(status == 0 && pars->start_map == 1)
    {
        //printf("parsing line map 2\n");
        //printf("which line %s\n",s);
        pars->valid_map = 0;
    }
       

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

