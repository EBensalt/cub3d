/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aniouar <aniouar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 17:19:44 by aniouar           #+#    #+#             */
/*   Updated: 2021/12/18 15:46:29 by aniouar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strpos(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s;
	int		i;
	int		index;

	if (!s1)
		s1 = ft_strdup("");
	s = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (s != 0)
	{
		index = 0;
		if (s1)
		{
			i = 0;
			while (s1[i])
				s[index++] = s1[i++];
			i = 0;
			while (s2[i])
				s[index++] = s2[i++];
		}
		s[index] = '\0';
		free(s1);
		return (s);
	}
	return (0);
}

char	*ft_strdup(char *s)
{
	int		i;
	char	*ns;

	i = 0;
	while (s[i])
		i++;
	ns = (char *)malloc(i + 1);
	if (!ns)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ns[i] = s[i];
		i++;
	}
	ns[i] = '\0';
	return (ns);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_substr(char *s, unsigned int start, size_t len, int mod)
{
	int		x;
	char	*dst;

	if (!s)
		return (0);
	dst = malloc(len + 1);
	if (!dst)
		return (0);
	len += start;
	x = 0;
	while (start < len && s[start] != '\0')
	{
		dst[x] = s[start];
		x++;
		start++;
	}
	dst[x] = '\0';
	if (mod)
	{
		free(s);
		s = 0;
	}
	return (dst);
}
