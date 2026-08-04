/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:58:58 by ssin              #+#    #+#             */
/*   Updated: 2026/08/04 18:50:55 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	validate_extension(char *map_name)
{
	(void)map_name;
	// the file must have a .cub extension
	// read the string until the '.' char:
		// if there's none, error/exit
	// if the content after '.':
		// match cub -> continue
		// is something else -> error/exit
	return (1);
}

void	parser(char *map_name)
{
	int		map_fd;
	char	buf[SIZE + 1];

	validate_extension(map_name);
	map_fd = open(map_name, O_RDONLY);
	if (read(map_fd, buf, SIZE) > 0)
	{
		buf[SIZE] = '\0';
		printf("%s\n", buf); // remove
	}
}
