/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 23:47:11 by anematol          #+#    #+#             */
/*   Updated: 2026/09/27 16:39:10 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	check_ray_collision(t_mlx_data *env_p, int check_x, int check_y)
{
	int	tile_x;
	int	tile_y;

	tile_x = check_x / env_p->block_size;
	tile_y = check_y / env_p->block_size;
	if (tile_x < 0 || tile_x >= env_p->map_info->map_width
		|| tile_y < 0 || tile_y >= env_p->map_info->map_height)
		return (1);
	if (env_p->map_info->map[tile_y][tile_x] == '1')
		return (1);
	return (0);
}

t_vector	give_vector(double x, double y)
{
	t_vector	vector;

	vector.x = x;
	vector.y = y;
	return (vector);
}

//returns the vector of the ray casted out from the current player position
//to the current player direction plus the given degree_angle
t_vector	get_ray_vector(t_mlx_data *env_p, double degree_angle)
{
	t_vector	vector;
	t_vector	delta;

	vector.x = cos(env_p->player_direction + (degree_angle / 180 * M_PI));
	vector.y = sin(env_p->player_direction + (degree_angle / 180 * M_PI));
	delta.x = vector.x;
	delta.y = vector.y;
	while (!check_ray_collision(env_p,
			(int)(vector.x + env_p->player_x + MINI_PLAYER_CENTER_POINT),
		(int)(vector.y + env_p->player_y + MINI_PLAYER_CENTER_POINT)))
	{
		vector.x += 0.1 * delta.x;
		vector.y += 0.1 * delta.y;
	}
	return (vector);
}

double	get_ray_len(t_mlx_data *env_p, double degree_angle)
{
	t_vector	ray_vector;
	double		ray_len;

	ray_vector = get_ray_vector(env_p, degree_angle);
	env_p->ray_vector = ray_vector;
	ray_len = sqrt(ray_vector.x * ray_vector.x + ray_vector.y * ray_vector.y);
	return (ray_len);
}

t_coords	get_exact_collision_point(t_mlx_data *env_p, t_vector ray_vector)
{
	t_coords	collision_point;

	if (ray_vector.x > 0)
		collision_point.x = (int)(ray_vector.x + env_p->player_x);
	else
		collision_point.x = (int)ceil(ray_vector.x + env_p->player_x);
	if (ray_vector.y > 0)
		collision_point.y = (int)(ray_vector.y + env_p->player_y);
	else
		collision_point.y = (int)ceil(ray_vector.y + env_p->player_y);
	collision_point.x += MINI_PLAYER_CENTER_POINT;
	collision_point.y += MINI_PLAYER_CENTER_POINT;
	return (collision_point);
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
