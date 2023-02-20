/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 11:42:46 by aniouar           #+#    #+#             */
/*   Updated: 2023/02/20 06:19:48 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	if (s1[i] > 127 || s2[i] > 127)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (s1[i] - s2[i]);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char	*ft_strstr(char *str, char *to_find)
{
	int	i;

	if (ft_strlen(to_find) > 0)
	{
		i = 0;
		while (str[i] != '\0')
		{
			if (ft_strncmp(str + i, to_find, ft_strlen(to_find)) == 0)
			{
				str = str + i;
				return (str);
			}
			i++;
		}
	}
	else if (ft_strlen(to_find) == 0)
		return (str);
	return (0);
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
