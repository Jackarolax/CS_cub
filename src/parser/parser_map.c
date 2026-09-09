/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 19:05:01 by ssin              #+#    #+#             */
/*   Updated: 2026/09/03 19:13:37 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int valid_map_content(char **tokens)
{
	if (ft_strncmp(tokens[0], "0", 1) == VALID
		|| ft_strncmp(tokens[0], "1", 1) == VALID)
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
