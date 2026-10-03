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
	if (env_p->map_info->player_x != 0.0
		&& env_p->map_info->player_y != 0.0)
		return ("Error\nDuplicated Player");
	return (NULL);
}

static void	set_player_position_from_i_j(t_mlx_data *env_p, int i, int j)
{
	env_p->map_info->player_x = j * BLOCK_SIZE
		+ (BLOCK_SIZE / 2) - MINI_PLAYER_CENTER_POINT;
	env_p->map_info->player_y = i * BLOCK_SIZE
		+ (BLOCK_SIZE / 2) - MINI_PLAYER_CENTER_POINT;
	if (env_p->map_info->map[i][j] == 'E')
		env_p->map_info->player_direction = 0 * M_PI / 2;
	else if (env_p->map_info->map[i][j] == 'S')
		env_p->map_info->player_direction = 1 * M_PI / 2;
	else if (env_p->map_info->map[i][j] == 'W')
		env_p->map_info->player_direction = 2 * M_PI / 2;
	else if (env_p->map_info->map[i][j] == 'N')
		env_p->map_info->player_direction = 3 * M_PI / 2;
}

void	add_player_pos(t_mlx_data *env_p, double i, double j)
{
	char	*msg;

	msg = duplicate_player(env_p);
	if (msg)
	{
		env_p->map_info->map[(int)(i + 1)] = NULL;
		call_error(env_p, msg);
	}
	set_player_position_from_i_j(env_p, (int)i, (int)j);
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
	if (env_p->map_info->player_x != 0.0 && env_p->map_info->player_y != 0.0)
		return (1);
	return (0);
}
