/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 19:05:01 by ssin              #+#    #+#             */
/*   Updated: 2026/09/22 09:32:07 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	valid_first_last_rows(char *row)
{
	int	i;

	i = 0;
	while (row && row[i])
	{
		if (ft_strncmp(&row[i], "1", 1) == VALID
			|| ft_strncmp(&row[i], "	", 1) == VALID
			|| ft_strncmp(&row[i], " ", 1) == VALID)
			i++;
		else
			return (1);
	}
	return (0);
}

int valid_map_content(char *letter)
{
	if (ft_strncmp(letter, "0", 1) == VALID
		|| ft_strncmp(letter, "1", 1) == VALID
		//|| ft_strncmp(letter, " ", 1) == VALID
		|| is_player_id(*letter))
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
