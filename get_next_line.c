/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/18 17:35:17 by sbos          #+#    #+#                 */
/*   Updated: 2021/11/29 18:12:36 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <unistd.h> // read
// #include <sys/types.h> // ssize_t
#include <stdlib.h> // malloc

static char	*gnl_create_line_str(t_buffer_list *buf)
{
	size_t	len;
	char	*line;
	char	*nl;

	if (buf->size == 0)
		return (NULL);
	len = 0;
	while (buf->next != NULL)
	{
		len += (size_t)(buf->size - buf->start);
		buf = buf->next;
	}
	nl = gnl_find_newline(buf);
	if (nl == NULL)
		len += (size_t)buf->size;
	else
		len += (size_t)(nl - buf->str) + 1;
	line = malloc(len + 1);
	if (line == NULL)
		return (NULL);
	if (nl != NULL)
		line[len - 1] = '\n';
	line[len] = '\0';
	return (line);
}

// if (j != (*buf)->size && j + 1 < (*buf)->size)
static char	*gnl_join_all(t_buffer_list **buf)
{
	char			*line;
	ssize_t			i;
	ssize_t			j;

	line = gnl_create_line_str(*buf);
	if (line == NULL)
		return (NULL);
	i = 0;
	while (*buf != NULL)
	{
		j = (*buf)->start;
		while (j < (*buf)->size && (*buf)->str[j] != '\n')
		{
			line[i] = (*buf)->str[j];
			i++;
			j++;
		}
		if (j + 1 < (*buf)->size)
		{
			(*buf)->start = j + 1;
			return (line);
		}
		gnl_next(buf);
	}
	return (line);
}

/**
 * @brief Get the next line, including the newline character at the end.
 * @param fd
 * @return
 */
char	*get_next_line(int fd)
{
	static t_buffer_list	*buf = NULL;
	t_buffer_list			*cur;

	cur = gnl_lst_new_back(&buf);
	if (cur == NULL)
		return (gnl_lst_clear(buf));
	cur->size = read(fd, cur->str, BUFFER_SIZE);
	while (gnl_find_newline(cur) == NULL && cur->size != 0)
	{
		cur = gnl_lst_new_back(&buf);
		if (cur == NULL)
			return (gnl_lst_clear(buf));
		cur->size = read(fd, cur->str, BUFFER_SIZE);
	}
	return (gnl_join_all(&buf));
}
