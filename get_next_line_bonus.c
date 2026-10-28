/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibaboul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 15:51:32 by mibaboul          #+#    #+#             */
/*   Updated: 2026/10/23 04:48:07 by mibaboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	*stash[FD_LIMIT];
	char		buffer;

	if (fd < 0 || fd >= FD_LIMIT)
		return (NULL);
	if (BUFFER_SIZE <= 0 || read(fd, &buffer, 0) < 0)
		return (clear_stash(&stash[fd], NULL));
	stash[fd] = read_to_stash(fd, stash[fd]);
	if (!stash[fd] || !*stash[fd])
		return (clear_stash(&stash[fd], NULL));
	return (extract_line(&stash[fd]));
}
