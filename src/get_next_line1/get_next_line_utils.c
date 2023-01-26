/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 15:41:20 by ebensalt          #+#    #+#             */
/*   Updated: 2023/01/18 03:28:17 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	char	a;
	int		b;

	if (!s)
		return (0);
	a = (char)c;
	b = 0;
	while (s[b] != '\0')
	{
		if (s[b] == a)
			return ((char *)s + b);
		b++;
	}
	if (s[b] == a)
		return ((char *)s + b);
	return (0);
}

static char	*f1(char *a, const char *s)
{
	int	b;

	b = 0;
	while (s[b] != '\0')
	{
		a[b] = s[b];
		b++;
	}
	return (a);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*a;
	int		c;
	int		b;

	if (!s1 || !s2)
		return (0);
	c = 0;
	while (s1[c] != '\0')
		c++;
	b = 0;
	while (s2[b] != '\0')
		b++;
	a = malloc(((c + b) + 1) * sizeof(char));
	if (a == NULL)
		return (0);
	f1(a, s1);
	f1((a + c), s2);
	a[c + b] = '\0';
	free((char *)s1);
	return (a);
}

char	*ft_strdup(const char *s1)
{
	int		a;
	char	*b;

	if (!s1)
		return (0);
	a = 0;
	while (s1[a] != '\0')
		a++;
	b = malloc(a + 1 * sizeof(char));
	if (b == NULL)
		return (0);
	a = 0;
	while (s1[a] != '\0')
	{
		b[a] = s1[a];
		a++;
	}
	b[a] = '\0';
	return (b);
}

size_t	ft_strlen(const char *s)
{
	size_t	a;

	a = 0;
	while (s[a] != '\0')
		a++;
	return (a);
}
