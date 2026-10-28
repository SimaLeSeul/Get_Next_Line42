/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibaboul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 15:52:08 by mibaboul          #+#    #+#             */
/*   Updated: 2026/10/23 04:48:07 by mibaboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef FD_LIMIT
#  define FD_LIMIT 10240
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*clear_stash(char **stash, char *line);
size_t	my_strlen(const char *str, int line);
char	*extract_line(char **stash);
char	*free_join(char *stash, char *buffer);
char	*read_to_stash(int fd, char *stash);

#endif
