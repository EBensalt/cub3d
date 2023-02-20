/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 15:39:06 by ebensalt          #+#    #+#             */
/*   Updated: 2023/02/20 06:27:08 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strrrchr(const char *s, int c)
{
	char	a;
	int		b;
	char	*d;
	int		i;

	if (!s)
		return (0);
	a = (char)c;
	b = 0;
	d = ft_strdup(s);
	i = ft_strlen(s);
	while (b <= i)
	{
		if (s[b] == a)
		{
			d[b + 1] = '\0';
			return (d);
		}
		b++;
	}
	free(d);
	return (0);
}

char	*ft_stchr(const char *s, int c)
{
	char	a;
	int		b;
	char	*d;

	if (!s)
		return (0);
	a = (char)c;
	b = 0;
	while (s[b] != '\0')
	{
		if (s[b] == a)
		{
			d = ft_strdup(s + b + 1);
			free((char *)s);
			return (d);
		}
		b++;
	}
	free((char *)s);
	return (0);
}

char	*ft_end(char *line, char *buf, int i, int j)
{
	if (((i == 0 && j == 0) || i == -1) && (!line || line[0] == '\0'))
	{
		free(line);
		return (0);
	}
	if (i == 0 && j != 0)
		return (line);
	else
	{	
		if (!line)
			line = ft_strdup(buf);
		else
			line = ft_strjoin(line, buf);
	}
	return (line);
}

char	*get_next_line_resum(char *line, int fd, char *buf, int j)
{
	int	i;

	while (ft_strchr(line, '\n') == 0)
	{
		i = read(fd, buf, 1);
		buf[i] = '\0';
		if (i < 1)
		{
			line = ft_end(line, buf, i, j);
			break ;
		}
		if (!line)
			line = ft_strdup(buf);
		else
			line = ft_strjoin(line, buf);
		j++;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*buf;
	char		*result;
	int			j;

	buf = (char *)malloc((1 + 1) * sizeof(char));
	if (buf == NULL)
		return (0);
	j = 0;
	line = get_next_line_resum(line, fd, buf, j);
	if (ft_strchr(line, '\n') == 0)
		result = ft_strrrchr(line, '\0');
	else
		result = ft_strrrchr(line, '\n');
	line = ft_stchr(line, '\n');
	free(buf);
	return (result);
}
