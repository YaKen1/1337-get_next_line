/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykenzaou <ykenzaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 21:39:14 by ykenzaou          #+#    #+#             */
/*   Updated: 2023/04/01 21:39:18 by ykenzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"	

static char	*read_and_join_lines(int fd, char *buf, char *rest)
{
	int		bytes_read_num;
	char	*temp_string;

	bytes_read_num = 1;
	while (bytes_read_num != 0)
	{
		bytes_read_num = read(fd, buf, BUFFER_SIZE);
		if (bytes_read_num == -1)
			return (0);
		else if (bytes_read_num == 0)
			break ;
		buf[bytes_read_num] = '\0';
		if (!rest)
			rest = ft_strdup("");
		temp_string = rest;
		rest = ft_strjoin(temp_string, buf);
		free(temp_string);
		temp_string = NULL;
		if (ft_strchr (buf, '\n'))
			break ;
	}
	return (rest);
}

static char	*extract_next_line(char *line)
{
	size_t	newline_index;
	char	*remaining_line;

	newline_index = 0;
	while (line[newline_index] != '\n' && line[newline_index] != '\0')
		newline_index++;
	if (line[newline_index] == '\0' || line[1] == '\0')
		return (0);
	remaining_line = ft_substr(line, newline_index + 1, \
	ft_strlen(line) - newline_index);
	if (*remaining_line == '\0')
	{
		free(remaining_line);
		remaining_line = NULL;
	}
	line[newline_index + 1] = '\0';
	return (remaining_line);
}

char	*get_next_line(int fd)
{
	char		*next_line;
	char		*buf;
	static char	*rest;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (0);
	next_line = read_and_join_lines(fd, buf, rest);
	free(buf);
	buf = NULL;
	if (!next_line)
		return (NULL);
	rest = extract_next_line(next_line);
	return (next_line);
}
