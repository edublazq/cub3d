/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edblazqu <edblazqu@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 15:57:35 by edblazqu          #+#    #+#             */
/*   Updated: 2026/10/13 15:57:40 by edblazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>

char				*the_rest(char *save);
char				*make_line_from(char *save);
char				*read_until_enter(int fd, char *save);
char				*get_next_line(int fd);
/*	---		utils	---	*/
unsigned long int	ft_strlen(const char *s);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_strchr(const char *save, int character);
void				*ft_calloc(unsigned long int size, unsigned long int c);

#endif
