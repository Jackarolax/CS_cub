/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 23:47:11 by anematol          #+#    #+#             */
/*   Updated: 2026/09/13 15:59:23 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	check_ray_collision(t_mlx_data *env_p, int check_x, int check_y)
{
	int	tile_x;
	int	tile_y;

	tile_x = check_x / env_p->block_size;
	tile_y = check_y / env_p->block_size;
	if (tile_x < 0 || tile_x >= env_p->map_width
		|| tile_y < 0 || tile_y >= env_p->map_height)
		return (1);
	if (env_p->map[tile_y][tile_x] == '1')
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
	while (!check_ray_collision(env_p,(int) (vector.x + env_p->player_x + MINI_PLAYER_CENTER_POINT),
										(int) (vector.y + env_p->player_y + MINI_PLAYER_CENTER_POINT)))
	{
		vector.x += delta.x;
		vector.y += delta.y;
	}
	if (sqrt(vector.x * vector.x + vector.y * vector.y) < (2 * (double)env_p->block_size))
	{
		vector.x -=	delta.x;
		vector.y -= delta.y;
		while (!check_ray_collision(env_p,(int) (vector.x + env_p->player_x + MINI_PLAYER_CENTER_POINT),
										(int) (vector.y + env_p->player_y + MINI_PLAYER_CENTER_POINT)))
		{
			vector.x += 0.1 * delta.x;
			vector.y += 0.1 * delta.y;
		}
	}
	return (vector);
}

double	get_ray_len(t_mlx_data *env_p, double degree_angle)
{
	t_vector	ray_vector;
	double		ray_len;

	ray_vector = get_ray_vector(env_p, degree_angle);
	ray_len = sqrt(ray_vector.x * ray_vector.x + ray_vector.y * ray_vector.y);
	return(ray_len);
}
