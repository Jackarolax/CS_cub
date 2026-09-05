/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/08 20:15:51 by anematol          #+#    #+#             */
/*   Updated: 2026/09/05 12:44:36 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

double	calculate_new_x(t_mlx_data *env_p)
{
	double new_x;

	new_x = env_p->player_x;
	if (env_p->mv_fwd_pressed)
		new_x += MOVING_SPEED * cos(env_p->player_direction);
	if (env_p->mv_bck_pressed)
		new_x -= MOVING_SPEED * cos(env_p->player_direction);
	if (env_p->mv_l_pressed)
		new_x -= MOVING_SPEED * cos(env_p->player_direction - M_PI / 2);
	if (env_p->mv_r_pressed)
		new_x -= MOVING_SPEED * cos(env_p->player_direction + M_PI / 2);
	return (new_x);
}

double	calculate_new_y(t_mlx_data *env_p)
{
	double	new_y;

	new_y = env_p->player_y;
	if (env_p->mv_fwd_pressed)
		new_y += MOVING_SPEED * sin(env_p->player_direction);
	if (env_p->mv_bck_pressed)
		new_y -= MOVING_SPEED * sin(env_p->player_direction);
	if (env_p->mv_l_pressed)
		new_y -= MOVING_SPEED * sin(env_p->player_direction - M_PI / 2);
	if (env_p->mv_r_pressed)
		new_y -= MOVING_SPEED * sin(env_p->player_direction + M_PI / 2);
	return (new_y);
}

void	move_player_with_collisions(t_mlx_data *env_p, int new_x, int new_y)
{
	if (!check_collision(env_p, new_x, env_p->player_y))
	{
		//count_moves(env_p, new_x, collision_position_y(env_p, new_y));
		env_p->player_x = new_x;
		env_p->player_y = collision_position_y(env_p, new_y);
	}
	else if (!check_collision(env_p, env_p->player_x, new_y))
	{
		//count_moves(env_p, collision_position_x(env_p, new_x), new_y);
		env_p->player_x = collision_position_x(env_p, new_x);
		env_p->player_y = new_y;
	}
	else if (touching_x(env_p))
	{
		printf("touching x");
		//count_moves(env_p, env_p->player_x,
		//	collision_position_y(env_p, new_y));
		env_p->player_y = collision_position_y(env_p, new_y);
	}
	else if (touching_y(env_p))
	{
		printf("touching y");
		//count_moves(env_p, collision_position_x(env_p, new_x),
		//	env_p->player_y);
		env_p->player_x = collision_position_x(env_p, new_x);
	}
}

void	move_player(t_mlx_data *env_p)
{
	double	new_x;
	double	new_y;

	new_x = calculate_new_x(env_p);
	new_y = calculate_new_y(env_p);
	if (env_p->look_l_pressed)
		env_p->player_direction -= TURNING_SPEED * M_PI / 180;
	if (env_p->look_r_pressed)
		env_p->player_direction += TURNING_SPEED * M_PI / 180;
	if (env_p->player_direction > 2.0 * M_PI)
		env_p->player_direction -= 2.0 * M_PI;
	else if (env_p->player_direction < 0)
		env_p->player_direction += 2.0 * M_PI;
	if (!check_collision(env_p, new_x, new_y))
	{
		//count_moves(env_p, new_x, new_y);
		env_p->player_x = new_x;
		env_p->player_y = new_y;
		//check_element_collisions(env_p, new_x, new_y);
		return ;
	}
	//check_element_collisions(env_p, new_x, new_y);
	move_player_with_collisions(env_p, new_x, new_y);
}
