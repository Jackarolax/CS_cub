/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:01:31 by anematol          #+#    #+#             */
/*   Updated: 2025/05/27 15:56:53 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, (ft_strlen(s)));
}
/*
#include <fcntl.h>
int main()
{
	int file;

	file = open("test", O_WRONLY);
	ft_putstr_fd("Hello", file);
	close(file);
}
*/
