/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibaboul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 15:51:32 by mibaboul          #+#    #+#             */
/*   Updated: 2026/10/23 04:48:07 by mibaboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*extract_line(const char *stash)
{
	size_t	len;
	char	*res;

	if (!stash)
		return (NULL);
	len = my_strnlen(stash);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	my_memcpy(res, stash, len);
	res[len] = '\0';
	return (res);
}

char	*extract_rest(const char *stash)
{
	size_t	len;
	size_t	rest_len;
	char	*res;

	if (!stash)
		return (NULL);
	len = my_strnlen(stash);
	rest_len = my_strlen(stash + len);
	if (rest_len == 0)
		return (NULL);
	res = malloc(rest_len + 1);
	if (!res)
		return (NULL);
	my_memcpy(res, stash + len, rest_len);
	res[rest_len] = '\0';
	return (res);
}

char	*append_to_stash(char *stash, char *buffer)
{
	char	*tmp;

	tmp = my_strjoin(stash, buffer);
	if (!tmp)
	{
		free(stash);
		return (NULL);
	}
	free(stash);
	return (tmp);
}

char	*read_to_stash(int fd, char *stash)
{
	ssize_t		bytes_read;
	char		*buffer;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (clear_stash(&stash, NULL));
	while (!stash || !*stash || stash[my_strnlen(stash) - 1] != '\n')
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (clear_stash(&stash, NULL));
		}
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		stash = append_to_stash(stash, buffer);
		if (!stash)
			break ;
	}
	free(buffer);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_to_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	if (!line)
		return (clear_stash(&stash, NULL));
	tmp = extract_rest(stash);
	if (!tmp && stash[my_strnlen(stash)] != '\0')
		return (clear_stash(&stash, line));
	free(stash);
	stash = tmp;
	return (line);
}
