/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 19:05:01 by ssin              #+#    #+#             */
/*   Updated: 2026/09/10 17:40:30 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int valid_map_content(char *letter)
{
	if (ft_strncmp(letter, "0", 1) == VALID
		|| ft_strncmp(letter, "1", 1) == VALID
		|| ft_strncmp(letter, " ", 1) == VALID
		|| ft_strncmp(letter, "N", 1) == VALID
		|| ft_strncmp(letter, "S", 1) == VALID
		|| ft_strncmp(letter, "W", 1) == VALID
		|| ft_strncmp(letter, "E", 1) == VALID)
		return (1);
	return (0);
}

/*static int	check_map(char *line)
{
	while (*line)
	{
		printf("%c", line[0]);
		line++;
	}
	return (0);
}
*/
