/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/30 14:03:45 by sbos          #+#    #+#                 */
/*   Updated: 2021/12/02 16:13:00 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
		len += (size_t)(nl - (lst->buf + lst->start)) + 1;
	line = malloc(len + 1);
	if (line == NULL)
		return (NULL);
	if (nl != NULL)
		line[len - 1] = '\n';
	line[len] = '\0';
	return (line);
}

// if (j != (*lst)->size && j + 1 < (*lst)->size)
// if (j < (*lst)->size && j + 1 < (*lst)->size)
static char	*gnl_create_line(t_buffer_list **lst)
{
	char			*line;
	ssize_t			i;
	ssize_t			j;

	line = gnl_malloc_line(*lst);
	if (line == NULL)
		return (gnl_lst_clear(lst));
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
	static t_buffer_list	*lst_fds[OPEN_MAX];
	t_buffer_list			**lst;
	t_buffer_list			*cur;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE < 1)
		return (NULL);
	lst = &lst_fds[fd];
	if (gnl_find_newline(*lst))
		return (gnl_create_line(lst));
	cur = gnl_lst_new_back(lst);
	if (cur == NULL)
		return (NULL);
	cur->size = read(fd, cur->buf, BUFFER_SIZE);
	while (gnl_find_newline(cur) == NULL && cur->size > 0)
	{
		cur = gnl_lst_new_back(lst);
		if (cur == NULL)
			return (gnl_lst_clear(lst));
		cur->size = read(fd, cur->buf, BUFFER_SIZE);
	}
	if (cur->size < 0)
		return (gnl_lst_clear(lst));
	return (gnl_create_line(lst));
}
