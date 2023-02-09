/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aniouar <aniouar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 10:05:28 by aniouar           #+#    #+#             */
/*   Updated: 2021/12/21 09:11:44 by aniouar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*make_line(char **saved, int pos, char **buffer)
{
	char	*line;

	line = ft_substr(*saved, 0, (pos + 1), 0);
	*saved = ft_substr(*saved, (pos + 1), ft_strlen(*saved), 1);
	free(*buffer);
	return (line);
}

char	*more_of_gnl(char **saved, char **buffer, int status)
{
	char	*line;

	line = 0;
	if (*saved && ft_strlen(*saved) > 0)
	{
		line = ft_strjoin(*saved, *buffer);
		*saved = 0;
	}
	if (status != -1 && *saved)
	{
		free(*saved);
		*saved = 0;
	}
	if (*buffer != 0)
	{
		free(*buffer);
		*buffer = 0;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*saved;
	int			pos;
	char		*buffer;
	int			len;

	len = 1;
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (more_of_gnl(&saved, &buffer, -1));
	while (len > 0)
	{
		len = read(fd, buffer, BUFFER_SIZE);
		if (len == -1 || (len == 0 && ft_strlen(saved) == 0))
			break ;
		buffer[len] = '\0';
		saved = ft_strjoin(saved, buffer);
		pos = ft_strpos(saved, '\n');
		if (pos >= 0)
			return (make_line(&saved, pos, &buffer));
	}
	return (more_of_gnl(&saved, &buffer, len));
}
