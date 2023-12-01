/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymenyoub <ymenyoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 04:01:39 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/11/11 02:13:38 by ymenyoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>

int		ft_strchrr(char *s);
char	*ft_strjooin(char *s1, char *s2);
char	*ft_strdupp(char *s1);
size_t	ft_strlenn(char *s);
char	*get_next_line(int fd);
char	*ft_rest(char *save);
char	*ft_line(char *string);
char	*ft_add_join(int fd, char *saved);

#endif
