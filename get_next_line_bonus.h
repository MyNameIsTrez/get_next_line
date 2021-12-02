/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.h                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/30 14:03:48 by sbos          #+#    #+#                 */
/*   Updated: 2021/12/02 16:05:35 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stddef.h> // size_t
# include <sys/types.h> // ssize_t
# include <limits.h> // OPEN_MAX

# ifndef OPEN_MAX
#  define OPEN_MAX FD_SETSIZE
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
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
