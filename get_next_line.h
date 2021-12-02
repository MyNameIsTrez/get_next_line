/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/18 17:35:33 by sbos          #+#    #+#                 */
/*   Updated: 2021/11/30 14:44:49 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h> // size_t
# include <sys/types.h> // ssize_t

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 8
# endif

typedef struct s_buffer_list {
	char					buf[BUFFER_SIZE];
	ssize_t					size;
	ssize_t					start;
	struct s_buffer_list	*next;
}	t_buffer_list;

t_buffer_list	*gnl_lst_new_back(t_buffer_list **lst);
void			gnl_next(t_buffer_list **lst);
char			*gnl_find_newline(t_buffer_list *lst);
char			*gnl_lst_clear(t_buffer_list **lst);

char			*get_next_line(int fd);

#endif
