/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/08 20:15:51 by anematol          #+#    #+#             */
/*   Updated: 2026/08/08 22:33:06 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

double	calculate_new_x(t_mlx_data *env_p)
{
	double new_x;

	new_x = env_p->player_x;
	if (env_p->mv_fwd_pressed)
		new_x += env_p->moving_speed * cos(env_p->player_diretion);
	if (env_p->mv_bck_pressed)
		new_x -= env_p->moving_speed * cos(env_p->player_diretion);
	if (env_p->mv_l_pressed)
		new_x += env_p->moving_speed * cos(env_p->player_diretion - M_PI / 2);
	if (env_p->mv_r_pressed)
		new_x += env_p->moving_speed * cos(env_p->player_diretion + M_PI / 2);
	return (new_x);
}

double	calculate_new_y(t_mlx_data *env_p)
{
	double	new_y;

	new_y = env_p->player_y;
	if (env_p->mv_fwd_pressed)
		new_y -= env_p->moving_speed * sin(env_p->player_diretion);
	if (env_p->mv_bck_pressed)
		new_y += env_p->moving_speed * sin(env_p->player_diretion);
	if (env_p->mv_l_pressed)
		new_y += env_p->moving_speed * sin(env_p->player_diretion + M_PI / 2);
	if (env_p->mv_r_pressed)
		new_y += env_p->moving_speed * sin(env_p->player_diretion - M_PI / 2);
	return (new_y);
}



void	move_player(t_mlx_data *env_p)
{
	double	new_x;
	double	new_y;
	//double	new_direction;

	new_x = calculate_new_x(env_p);
	new_y = calculate_new_y(env_p);
	if (env_p->look_l_pressed)
		env_p->player_diretion += 0.1 * M_PI / 180;
	if (env_p->look_r_pressed)
		env_p->player_diretion -= 0.1 * M_PI / 180;

	//if (env_p->mv_fwd_pressed)
	//	new_direction += speed * sin(env_p->player_diretion);

	//if (!check_collision(env_p, new_x, new_y))
	//{
	//	count_moves(env_p, new_x, new_y);
	//	env_p->player_x = new_x;
	//	env_p->player_y = new_y;
	//	check_element_collisions(env_p, new_x, new_y);
	//	return ;
	//}
	//check_element_collisions(env_p, new_x, new_y);
	//move_player_with_collisions(env_p, new_x, new_y);
	env_p->player_x = new_x;
	env_p->player_y = new_y;
}
