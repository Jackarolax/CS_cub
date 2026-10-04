/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 14:01:12 by anematol          #+#    #+#             */
/*   Updated: 2026/10/04 10:47:05 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	is_out_of_bounds(t_img img, t_coords coords)
{
	if (coords.x >= 0 && coords.y >= 0
		&& coords.x <= img.width && coords.y <= img.height)
		return (0);
	else
		return (1);
}

char	decide_on_edge(t_mlx_data *env_p,
	t_coords w_coll_pos, t_vector ray_vector)
{
	if (check_ray_collision(env_p, w_coll_pos.x + 1, w_coll_pos.y + 1)
		&& check_ray_collision(env_p, w_coll_pos.x + 1, w_coll_pos.y - 1))
		return ('E');
	if (check_ray_collision(env_p, w_coll_pos.x - 1, w_coll_pos.y + 1)
		&& check_ray_collision(env_p, w_coll_pos.x - 1, w_coll_pos.y - 1))
		return ('W');
	if (check_ray_collision(env_p, w_coll_pos.x + 1, w_coll_pos.y + 1)
		&& check_ray_collision(env_p, w_coll_pos.x - 1, w_coll_pos.y + 1))
		return ('S');
	if (check_ray_collision(env_p, w_coll_pos.x + 1, w_coll_pos.y - 1)
		&& check_ray_collision(env_p, w_coll_pos.x - 1, w_coll_pos.y - 1))
		return ('N');
	if (ray_vector.y >= 0)
		return ('S');
	if (ray_vector.y < 0)
		return ('N');
	else
		return (0);
}

char	get_wall_collision_side(t_mlx_data *env_p)
{
	t_vector	ray_vector;
	t_coords	wall_coll_pos;

	ray_vector = env_p->ray_vector;
	wall_coll_pos = get_exact_collision_point(env_p, ray_vector);
	if ((wall_coll_pos.y % env_p->block_size) == 0
		&& (wall_coll_pos.x % env_p->block_size) == 0)
		return (decide_on_edge(env_p, wall_coll_pos, ray_vector));
	else if (ray_vector.x >= 0.0 && (wall_coll_pos.x % env_p->block_size) == 0)
		return ('E');
	else if (ray_vector.x < 0.0 && (wall_coll_pos.x % env_p->block_size) == 0)
		return ('W');
	else if (ray_vector.y >= 0.0 && (wall_coll_pos.y % env_p->block_size) == 0)
		return ('S');
	else if (ray_vector.y < 0.0 && (wall_coll_pos.y % env_p->block_size) == 0)
		return ('N');
	else
		return (0);
}

//returns the position of the ray/wall collision in a double betwee 0 and 1
double	get_wall_x(t_mlx_data *env_p)
{
	t_vector	ray_vector;
	t_coords	wall_coll_pos;

	ray_vector = env_p->ray_vector;
	wall_coll_pos = get_exact_collision_point(env_p, ray_vector);
	if (ray_vector.x >= 0.0 && (wall_coll_pos.x % env_p->block_size) == 0)
		return (fmod(ray_vector.y + env_p->player_y
				+ (double)MINI_PLAYER_CENTER_POINT, (double)env_p->block_size)
			/ (double)(env_p->block_size));
	else if (ray_vector.x < 0.0 && (wall_coll_pos.x % env_p->block_size) == 0)
		return (1.0 - fmod(ray_vector.y + env_p->player_y
				+ (double)MINI_PLAYER_CENTER_POINT, (double)env_p->block_size)
			/ (double)(env_p->block_size));
	else if (ray_vector.y >= 0.0 && (wall_coll_pos.y % env_p->block_size) == 0)
		return (1.0 - fmod(ray_vector.x + env_p->player_x
				+ (double)MINI_PLAYER_CENTER_POINT, (double)env_p->block_size)
			/ (double)(env_p->block_size));
	else if (ray_vector.y < 0.0 && (wall_coll_pos.y % env_p->block_size) == 0)
		return (fmod(ray_vector.x + env_p->player_x
				+ (double)MINI_PLAYER_CENTER_POINT, (double)env_p->block_size)
			/ (double)(env_p->block_size));
	else
		return (-1.0);
}
