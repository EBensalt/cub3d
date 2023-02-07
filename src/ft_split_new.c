/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_new_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 01:33:47 by ebensalt          #+#    #+#             */
/*   Updated: 2023/02/02 00:27:47 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	fword(char const *s, char c)
{
	int	a;
	int	b;

	a = 0;
	b = 0;
	while (s[a] != '\0')
	{
		while (s[a] == c && s[a] != '\0')
			a++;
		while (s[a] != c && s[a] != '\0')
		{
			a++;
			if (s[a] == c || s[a] == '\0')
				b++;
		}
	}
	return (b);
}

static int	fchr(char const *s, char c)
{
	int	a;
	int	b;

	a = 0;
	b = 0;
	while (s[a] == c && s[a] != '\0')
		a++;
	while (s[a] != c && s[a] != '\0')
	{
		b++;
		a++;
	}
	return (b);
}

static char	*fcpy(char const *s, char c, char *b)
{
	int		a;
	int		d;

	a = 0;
	while (s[a] == c && s[a] != '\0')
		a++;
	d = 0;
	while (s[a] != c && s[a] != '\0')
	{
		b[d] = s[a];
		d++;
		a++;
	}
	b[d] = '\0';
	return (b);
}

static char	**falloc(char const *s, char c, int a, int f)
{
	char	**b;
	int		d;
	int		e;

	d = 0;
	e = 0;
	b = (char **)malloc((a + 1) * sizeof(char *));
	if (b == NULL)
		return (0);
	while (d < a && s[e] != '\0')
	{
		while (s[e] == c && s[e] != '\0')
			e++;
		f = fchr(&s[e], c);
		b[d] = (char *)malloc((f + 1) * sizeof(char));
		if (b[d] == NULL)
			return (0);
		b[d] = fcpy(&s[e], c, b[d]);
		while (s[e] != c && s[e] != '\0')
			e++;
		d++;
	}
	return (b);
}

char	**ft_split_new(char const *s, char c,int *count)
{
	int		a;
	char	**b;

	if (!s)
		return (0);
	a = fword(s, c);
	if(count)
		*count = a;
	b = falloc(s, c, a, a);
	if (b == NULL)
		return (0);
	b[a] = NULL;
	return (b);
}
