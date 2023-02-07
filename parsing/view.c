/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aniouar <aniouar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:27:00 by aniouar           #+#    #+#             */
/*   Updated: 2023/02/07 19:06:12 by aniouar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void view(t_pars *pars)
{
    printf("no %p\n",pars->dir_texture->no);
    printf("so %p\n",pars->dir_texture->so);
    printf("we %p\n",pars->dir_texture->we);
    printf("ea %p\n",pars->dir_texture->ea);
    printf("color floor %d\n",pars->color_floor);
    printf("color c %i\n",pars->color_c);
    printf("vision %p\n",pars->vision);
    printf("valid color %d\n",pars->valid_color);
    printf("valid texture %d\n",pars->valid_direction);
    printf("valid map %d\n",pars->valid_map);
}


void view_lines(t_pars *pars)
{
    t_line *current;

    current = pars->lines;

    while(current)
    {
        printf("line %s with size %zu next:%p\n",current->line,ft_strlen(current->line),current->next);
        current = current->next;
    }
}