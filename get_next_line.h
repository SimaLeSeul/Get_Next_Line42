/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibaboul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 15:52:08 by mibaboul          #+#    #+#             */
/*   Updated: 2026/10/23 04:48:07 by mibaboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
char	*clear_stash(char **stash, char *line);
size_t	my_strlen(const char *str);
char	*my_strjoin(const char *s1, const char *s2);
size_t	my_strnlen(const char *str);
void	*my_memcpy(void *dst, const void *src, size_t n);
char	*extract_line(const char *stash);
char	*extract_rest(const char *stash);
char	*append_to_stash(char *stash, char *buffer);
char	*read_to_stash(int fd, char *stash);

#endif
