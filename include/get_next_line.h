/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:30:38 by ashahbaz          #+#    #+#             */
/*   Updated: 2024/09/23 13:02:44 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

char	*get_next_line(int fd);
int		new_line(char *str);
char	*read_file(int fd, char *buffer);
char	*get_my_line(char *buffer);
char	*next_line(char *buffer);
size_t	gnl_ft_strlen( char *s);
char	*gnl_ft_strjoin(char *s1, char *s2);
char	*gnl_ft_substr(char *s, unsigned int start, size_t len);

#endif
