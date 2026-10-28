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

char	*get_next_line(int fd)
{
	static char	*stash;
	char		buffer;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &buffer, 0) < 0)
		return (clear_stash(&stash, NULL));
	stash = read_to_stash(fd, stash);
	if (!stash || !*stash)
		return (clear_stash(&stash, NULL));
	return (extract_line(&stash));
}
