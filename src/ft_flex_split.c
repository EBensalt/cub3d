/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flex_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aniouar <aniouar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 12:21:20 by aniouar           #+#    #+#             */
/*   Updated: 2023/01/29 15:52:28 by aniouar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char     *nice_alloc(char const *s, unsigned int start, size_t len)
{
        size_t  slen;
        size_t  size;
        char    *dst;

        size = len + 1;
        slen = ft_strlen(s);
        if (slen < len && start < slen)
                size = (slen - start) + 1;
        dst = (char *)malloc(size);
        if (!dst)
                return (0);
        return (dst);
}

char    *ft_substr_flex(char const *s, unsigned int start, size_t len)
{
        int             x;
        char    *dst;

        if (!s)
                return (0);
        dst = nice_alloc(s, start, len);
        if (!dst)
                return (0);
        if (start >= (unsigned int)ft_strlen(s))
        {
                free(dst);
                return (ft_strdup(""));
        }
        len += start;
        x = 0;
        while (start < len && s[start] != '\0')
        {
                dst[x] = s[start];
                x++;
                start++;
        }
        dst[x] = '\0';
        return (dst);
}

int check_space(char c)
{
	if(c == '\t' || c == '\r' || c == 32)
		return (1);
	return (0);
}


int	count_words(const char *s)
{
	int	i;
	int	start;
	int	count;

	count = 0;
	start = -1;
	i = 0;
	while (s[i])
	{
		if (!check_space(s[i]) && start == -1)
			start = i;
		if (check_space(s[i]) && start != -1)
		{
			count++;
			start = -1;
		}
		i++;
	}
	if ((check_space(s[i]) && ft_strlen(s) > 0) || start != -1)
		count++;
	return (count);
}

int	fill_split(char **t, char const *s)
{
	int	i;
	int	start;
	int	x;

	x = 0;
	start = -1;
	i = 0;
	while (s[i])
	{
		if (!check_space(s[i])&& start == -1)
			start = i;
		if (check_space(s[i]) && start != -1)
		{
			t[x++] = ft_substr_flex(s, start, (i - start));
			start = -1;
		}
		i++;
	}
	if ((check_space(s[i]) && ft_strlen(s) > 0) || start != -1)
		t[x++] = ft_substr_flex(s, start, (ft_strlen(s) - start));
	return (x);
}

char	**ft_flex_split(char const *s, int *count_flex)
{
	int		count;
	char	**t;
	int		x;

	if (!s)
		return (NULL);
	count = count_words(s);
	*count_flex = count;
	t = (char **)malloc(sizeof(char *) * (count + 1));
	if (!t)
		return (NULL);
	x = fill_split(t, s);
	t[x] = 0;
	return (t);
}
