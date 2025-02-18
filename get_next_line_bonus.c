/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwei <fwei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 02:27:57 by fwei              #+#    #+#             */
/*   Updated: 2025/02/10 05:47:46 by fwei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	free_stash(t_list **stash)
{
	t_list	*temp;

	if (!(*stash))
		return ;
	while (*stash)
	{
		temp = (*stash)->next;
		free((*stash)->content);
		free(*stash);
		*stash = temp;
	}
}

void	update_stash(t_list **stash, int line_len)
{
	t_list	*node;
	int		offset;
	int		len;

	node = *stash;
	offset = 0;
	while (node && offset < line_len)
	{
		len = 0;
		while (node->content[len] && offset + len < line_len)
			len++;
		offset += len;
		if (offset <= line_len && !node->content[len])
		{
			ft_lstdel_front(stash);
			node = *stash;
		}
		else if (node)
		{
			ft_memcpy(node->content, node->content + len, BUFFER_SIZE - len);
			break ;
		}
	}
}

int	extract_line(t_list *stash, char **line)
{
	int		v;
	int		w;
	int		line_len;
	char	*result;

	v = 0;
	line_len = calculate_line_len(stash);
	result = malloc(line_len + 1);
	if (!result)
		return (-1);
	while (stash && v < line_len)
	{
		w = 0;
		while (stash->content[w] && v + w < line_len)
		{
			result[v + w] = stash->content[w];
			w++;
		}
		v += w;
		stash = stash->next;
	}
	result[v] = '\0';
	*line = result;
	return (line_len);
}

int	read_to_stash(int fd, ssize_t *bytes_read, t_list **stash)
{
	char	*buffer;
	t_list	*new_node;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (0);
	*bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (*bytes_read <= 0)
	{
		free(buffer);
		return (*bytes_read == 0);
	}
	buffer[*bytes_read] = '\0';
	new_node = malloc(sizeof(t_list));
	if (!new_node)
	{
		free(buffer);
		return (0);
	}
	new_node->content = buffer;
	new_node->next = NULL;
	ft_lstadd_back(stash, new_node);
	return (1);
}

char	*get_next_line(int fd)
{
	char			*line;
	int				line_len;
	static t_list	*stashes[FD_MAX];
	ssize_t			bytes_read;

	line = NULL;
	line_len = 0;
	bytes_read = 1;
	if (fd < 0 || fd >= FD_MAX || BUFFER_SIZE <= 0)
		return (free_stash(&stashes[fd]), NULL);
	while (bytes_read > 0 && (!stashes[fd] || !has_newline(stashes[fd])))
	{
		if (!read_to_stash(fd, &bytes_read, &stashes[fd]) && stashes[fd])
		{
			free_stash(&stashes[fd]);
			return (NULL);
		}
	}
	if (stashes[fd] && (has_newline(stashes[fd]) || bytes_read == 0))
		line_len = extract_line(stashes[fd], &line);
	if (line_len > 0)
		update_stash(&stashes[fd], line_len);
	if (bytes_read == 0 && !line_len)
		free_stash(&stashes[fd]);
	return (line);
}
