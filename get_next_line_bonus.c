/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/30 14:03:45 by sbos          #+#    #+#                 */
/*   Updated: 2021/11/30 14:03:46 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
Excerpt from "man 2 select":
The default size FD_SETSIZE (currently 1024) is somewhat smaller
than the current kernel limit to the number of open files.
However, in order to accommodate programs which might potentially use
a larger number of open files with select, it is possible to increase this size
within a program by providing a larger definition of FD_SETSIZE
before the inclusion of <sys/types.h>."
*/
#ifndef OPEN_MAX
# define OPEN_MAX FD_SETSIZE
#endif
