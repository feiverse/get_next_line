/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwei <fwei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 01:42:43 by fwei              #+#    #+#             */
/*   Updated: 2024/12/20 12:39:21 by fwei             ###   ########.fr       */
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
}				t_list;

void	free_stash(t_list **stash);
void	update_stash(t_list **stash, int line_len);
int		extract_line(t_list *stash, char **line);
int		read_to_stash(int fd, ssize_t *bytes_read, t_list **stash);
char	*get_next_line(int fd);
void	ft_memcpy(char *dst, char *src, size_t n);
int		has_newline(t_list *stash);
int		calculate_line_len(t_list *stash);
void	ft_lstdel_front(t_list **stash);
void	ft_lstadd_back(t_list **stash, t_list *new_node);

#endif