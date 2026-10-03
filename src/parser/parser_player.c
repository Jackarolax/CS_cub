/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 17:17:14 by ssin              #+#    #+#             */
/*   Updated: 2026/09/29 17:17:51 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

static char	*duplicate_player(t_mlx_data *env_p)
{
	if (env_p->map_info->player_x_start != -1
		&& env_p->map_info->player_y_start != -1)
		return ("Error\nDuplicated Player");
	return (NULL);
}

void	add_player_pos(t_mlx_data *env_p, int i, int j)
{
	char	*msg;

	msg = duplicate_player(env_p);
	if (msg)
	{
		env_p->map_info->map[i + 1] = NULL;
		call_error(env_p, msg);
	}
	env_p->map_info->player_x_start = i;
	env_p->map_info->player_y_start = j;
}

int	is_player_id(char player)
{
	if (player == 'N'
		|| player == 'S'
		|| player == 'W'
		|| player == 'E')
		return (1);
	return (0);
}

int	player_exists(t_mlx_data *env_p)
{
	if (env_p->player_x && env_p->player_y)
		return (1);
	return (0);
}
