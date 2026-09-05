/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_collision_checking.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:20:00 by anematol          #+#    #+#             */
/*   Updated: 2026/08/22 13:22:44 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_collision(t_mlx_data *env_p, int check_x, int check_y)
{
	int	left;
	int	right;
	int	top;
	int	bottom;

	left = check_x / env_p->block_size;
	right = (check_x + env_p->player_img.width - 1) / env_p->block_size;
	top = check_y / env_p->block_size;
	bottom = (check_y + env_p->player_img.height - 1) / env_p->block_size;
	if (left < 0 || right >= env_p->map_width
		|| top < 0 || bottom >= env_p->map_height)
		return ('1');
	if (env_p->map[top][left] == '1'
		|| env_p->map[top][right] == '1'
		|| env_p->map[bottom][left] == '1'
		|| env_p->map[bottom][right] == '1')
		return (1);
	return (0);
}

int	collision_position_x(t_mlx_data *env_p, int new_x)
{
	int	i;

	i = 0;
	if (new_x < env_p->player_x)
	{
		while (i <= env_p->player_x - new_x)
		{
			if (check_collision(env_p, env_p->player_x - i, env_p->player_y))
				return (env_p->player_x - i + 1);
			i++;
		}
	}
	else if (new_x > env_p->player_x)
	{
		while (i <= new_x - env_p->player_x)
		{
			if (check_collision(env_p, env_p->player_x + i, env_p->player_y))
				return (env_p->player_x + i - 1);
			i++;
		}
	}
	return (env_p->player_x);
}

int	collision_position_y(t_mlx_data *env_p, int new_y)
{
	int	i;

	i = 0;
	if (new_y < env_p->player_y)
	{
		while (i <= env_p->player_y - new_y)
		{
			if (check_collision(env_p, env_p->player_x, env_p->player_y - i))
				return (env_p->player_y - i + 1);
			i++;
		}
	}
	else if (new_y > env_p->player_y)
	{
		while (i <= new_y - env_p->player_y)
		{
			if (check_collision(env_p, env_p->player_x, env_p->player_y + i))
				return (env_p->player_y + i - 1);
			i++;
		}
	}
	return (env_p->player_y);
}

int	touching_x(t_mlx_data *env_p)
{
	if (check_collision(env_p, env_p->player_x - 1, env_p->player_y)
		|| check_collision(env_p, env_p->player_x + 1, env_p->player_y))
		return (1);
	return (0);
}

int	touching_y(t_mlx_data *env_p)
{
	if (check_collision(env_p, env_p->player_x, env_p->player_y - 1)
		|| check_collision(env_p, env_p->player_x, env_p->player_y + 1))
		return (1);
	return (0);
}
