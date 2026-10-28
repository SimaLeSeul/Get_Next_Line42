/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibaboul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 17:16:48 by mibaboul          #+#    #+#             */
/*   Updated: 2026/10/23 04:48:07 by mibaboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*clear_stash(char **stash, char *line)
{
	free(line);
	free(*stash);
	*stash = NULL;
	return (NULL);
}

size_t	my_strlen(const char *str, int line)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		if (line && str[i] == '\n')
			return (i + 1);
		i++;
	}
	return (i);
}

char	*free_join(char *stash, char *buffer)
{
	char	*res;
	size_t	len;
	size_t	i;

	len = my_strlen(stash, 0);
	res = malloc(len + my_strlen(buffer, 0) + 1);
	if (!res)
		return (clear_stash(&stash, NULL));
	i = 0;
	while (i < len)
	{
		res[i] = stash[i];
		i++;
	}
	i = 0;
	while (buffer[i])
	{
		res[len + i] = buffer[i];
		i++;
	}
	res[len + i] = '\0';
	free(stash);
	return (res);
}

char	*read_to_stash(int fd, char *stash)
{
	ssize_t	bytes_read;
	char	*buffer;

	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (clear_stash(&stash, NULL));
	while (!stash || !*stash || stash[my_strlen(stash, 1) - 1] != '\n')
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (clear_stash(&stash, buffer));
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		stash = free_join(stash, buffer);
		if (!stash)
			break ;
	}
	free(buffer);
	return (stash);
}

char	*extract_line(char **stash)
{
	size_t	len;
	size_t	i;
	char	*line;

	len = my_strlen(*stash, 1);
	line = malloc(len + 1);
	if (!line)
		return (clear_stash(stash, NULL));
	i = len;
	line[i] = '\0';
	while (i-- > 0)
		line[i] = (*stash)[i];
	i = 0;
	while ((*stash)[len + i])
	{
		(*stash)[i] = (*stash)[len + i];
		i++;
	}
	(*stash)[i] = '\0';
	if (!**stash)
		clear_stash(stash, NULL);
	return (line);
}
