/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/18 17:35:17 by sbos          #+#    #+#                 */
/*   Updated: 2021/11/30 14:46:53 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <unistd.h> // read
#include <stdlib.h> // malloc

static char	*gnl_malloc_line(t_buffer_list *lst)
{
	size_t	len;
	char	*line;
	char	*nl;

	if (lst->size == 0)
		return (NULL);
	len = 0;
	while (lst->next != NULL)
	{
		len += (size_t)(lst->size - lst->start);
		lst = lst->next;
	}
	nl = gnl_find_newline(lst);
	if (nl == NULL)
		len += (size_t)lst->size;
	else
		len += (size_t)(nl - lst->buf) + 1;
	line = malloc(len + 1);
	if (line == NULL)
		return (NULL);
	if (nl != NULL)
		line[len - 1] = '\n';
	line[len] = '\0';
	return (line);
}

// if (j != (*lst)->size && j + 1 < (*lst)->size)
static char	*gnl_join_buffers(t_buffer_list **lst)
{
	char			*line;
	ssize_t			i;
	ssize_t			j;

	line = gnl_malloc_line(*lst);
	if (line == NULL)
		return (NULL);
	i = 0;
	while (*lst != NULL)
	{
		j = (*lst)->start;
		while (j < (*lst)->size && (*lst)->buf[j] != '\n')
		{
			line[i] = (*lst)->buf[j];
			i++;
			j++;
		}
		if (j + 1 < (*lst)->size)
		{
			(*lst)->start = j + 1;
			return (line);
		}
		gnl_next(lst);
	}
	return (line);
}

/**
 * @brief Gets the next line from @p fd, including the newline.
 * @param fd The file descriptor to read from.
 * @return The next line from @p fd.
 */
char	*get_next_line(int fd)
{
	static t_buffer_list	*lst = NULL;
	t_buffer_list			*cur;

	cur = gnl_lst_new_back(&lst);
	if (cur == NULL)
		return (gnl_lst_clear(lst));
	cur->size = read(fd, cur->buf, BUFFER_SIZE);
	while (gnl_find_newline(cur) == NULL && cur->size != 0)
	{
		cur = gnl_lst_new_back(&lst);
		if (cur == NULL)
			return (gnl_lst_clear(lst));
		cur->size = read(fd, cur->buf, BUFFER_SIZE);
	}
	return (gnl_join_buffers(&lst));
}
