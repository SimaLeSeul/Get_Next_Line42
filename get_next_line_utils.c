/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibaboul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 17:16:48 by mibaboul          #+#    #+#             */
/*   Updated: 2026/10/23 03:57:44 by mibaboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	nlchr(char *str)
{
	size_t	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i] == '\n')
				return (1);
			i++;
		}
	}
	return (0);
}

size_t	my_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*my_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*tmpdst;
	const unsigned char	*tmpsrc;

	if (!dst && !src)
		return (dst);
	i = 0;
	tmpsrc = (const unsigned char *)src;
	tmpdst = (unsigned char *)dst;
	while (i < n)
	{
		tmpdst[i] = tmpsrc[i];
		i++;
	}
	return (dst);
}

char	*my_strjoin(const char *s1, const char *s2)
{
	char	*res;
	size_t	len1;
	size_t	len2;

	len1 = 0;
	if (!s1 && !s2)
		return (NULL);
	if (s1)
		len1 = my_strlen(s1);
	len2 = my_strlen(s2);
	res = malloc((len1 + len2 + 1) * sizeof(char));
	if (!res)
		return (NULL);
	my_memcpy(res, s1, len1);
	my_memcpy(res + len1, s2, len2);
	res[len1 + len2] = '\0';
	return (res);
}

size_t	my_strnlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	return (i);
}

char	*extract_line(const char *stash)
{
	size_t	len;
	char	*res;

	if (!stash)
		return (NULL);
	if (stash)
	{
		len = my_strnlen(stash);
		res = malloc(len + 1);
		if (!res)
			return (NULL);
		my_memcpy(res, stash, len);
		res[len] = '\0';
	}
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
	{
		res = malloc(1);
		res[0] = '\0';
		return (res);
	}
	res = malloc(rest_len + 1);
	if (!res)
		return (NULL);
	my_memcpy(res, stash + len, rest_len);
	res[rest_len] = '\0';
	return (res);
}

char	*read_to_stash(int fd, char *stash)
{
	ssize_t		bytes_read;
	char		*buffer;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
	{
		free(stash);
		return (NULL);
	}
	while (!nlchr(stash))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(stash);
			free(buffer);
			return (NULL);
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

char *append_to_stash(char *stash, char *buffer)
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
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	tmp = extract_rest(stash);
	if (!tmp)
	{
		free(stash);
		return (NULL);
	}
	free(stash);
	stash = tmp;
	return (line);
}
