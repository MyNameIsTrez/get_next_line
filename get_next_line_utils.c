/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/18 17:35:20 by sbos          #+#    #+#                 */
/*   Updated: 2022/06/21 16:43:40 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdlib.h> // malloc

static t_buffer_list	*gnl_lst_new(void)
{
	t_buffer_list	*new;

	new = malloc(sizeof(t_buffer_list));
	if (new == NULL)
		return (NULL);
	new->start = 0;
	new->next = NULL;
	return (new);
}

t_buffer_list	*gnl_lst_new_back(t_buffer_list **lst)
{
	t_buffer_list	*new;

	new = gnl_lst_new();
	if (new == NULL)
		return (NULL);
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

void	gnl_next(t_buffer_list **lst)
{
	t_buffer_list	*next;

	next = (*lst)->next;
	free(*lst);
	*lst = next;
}

char	*gnl_find_newline(t_buffer_list *lst)
{
	ssize_t	i;

	if (lst == NULL)
		return (NULL);
	i = lst->start;
	while (i < lst->size)
	{
		if (lst->buf[i] == '\n')
			return (&lst->buf[i]);
		i++;
	}
	return (NULL);
}

char	*gnl_lst_clear(t_buffer_list **lst)
{
	while (*lst != NULL)
		gnl_next(lst);
	return (NULL);
}
