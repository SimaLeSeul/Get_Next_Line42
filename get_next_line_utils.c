/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibaboul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 17:16:48 by mibaboul          #+#    #+#             */
/*   Updated: 2026/10/23 04:33:15 by mibaboul         ###   ########.fr       */
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

