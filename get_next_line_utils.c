/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwei <fwei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 12:23:15 by fwei              #+#    #+#             */
/*   Updated: 2025/01/23 13:32:40 by fwei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_memcpy(char *dst, char *src, size_t n)
{
	while (n-- > 0)
		*dst++ = *src++;
	*dst = '\0';
}

int	has_newline(t_list *stash)
{
	int		v;

	while (stash)
	{
		v = 0;
		while (stash->content[v])
		{
			if (stash->content[v] == '\n')
				return (1);
			v++;
		}
		stash = stash->next;
	}
	return (0);
}

int	calculate_line_len(t_list *stash)
{
	int	v;
	int	line_len;

	if (!stash)
		return (0);
	line_len = 0;
	while (stash)
	{
		v = 0;
		while (stash->content[v] && stash->content[v] != '\n')
			v++;
		if (stash->content[v] == '\n')
			return (line_len + v + 1);
		line_len += v;
		stash = stash->next;
	}
	return (line_len);
}

void	ft_lstdel_front(t_list **stash)
{
	t_list	*temp;

	if (!stash || !*stash)
		return ;
	temp = (*stash)->next;
	free((*stash)->content);
	free(*stash);
	*stash = temp;
}

void	ft_lstadd_back(t_list **stash, t_list *new_node)
{
	t_list	*temp;

	temp = *stash;
	if (!*stash)
		*stash = new_node;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
}
