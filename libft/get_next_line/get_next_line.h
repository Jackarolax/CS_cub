/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:35:27 by anematol          #+#    #+#             */
/*   Updated: 2025/06/17 14:57:59 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>

int		ft_strlen_lf(char *str, int with_lf);
char	*ft_add_buf(char *line_p, char *buf);
int		ft_lf_in_buf(char *buf);
char	*ft_update_buf(char *buf, int delete_up_to);
void	ft_bzero(void *s, size_t n);
char	*get_next_line(int fd);
#endif
