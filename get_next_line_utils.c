/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/18 17:35:20 by sbos          #+#    #+#                 */
/*   Updated: 2021/11/29 17:24:45 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// #include <unistd.h> // read
// #include <sys/types.h> // ssize_t
#include <stdlib.h> // malloc

void	gnl_next(t_buffer_list **buf)
{
	t_buffer_list	*next;

	next = (*buf)->next;
	free(*buf);
	*buf = next;
}

char	*gnl_find_newline(t_buffer_list *buf)
{
	ssize_t	i;

	i = buf->start;
	while (i < buf->size)
	{
		if (buf->str[i] == '\n')
			return (&buf->str[i]);
		i++;
	}
	return (NULL);
}

t_buffer_list	*gnl_lst_new_back(t_buffer_list **lst)
{
	t_buffer_list	*new;

	new = malloc(sizeof(t_buffer_list));
	if (new == NULL)
		return (NULL);
	new->start = 0;
	new->next = NULL;
	if (*lst == NULL)
		*lst = new;
	else
	{
		while ((*lst)->next != NULL)
			lst = &((*lst)->next);
		(*lst)->next = new;
	}
	return (new);
}

char	*gnl_lst_clear(t_buffer_list *buf)
{
	t_buffer_list	*next;

	while (buf != NULL)
	{
		next = buf->next;
		free(buf);
		buf = next;
	}
	return (NULL);
}
