/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 23:47:11 by anematol          #+#    #+#             */
/*   Updated: 2026/09/20 19:15:49 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

//returns
//double	get_position_of_block(t_mlx_data *env_p, t_vector ray_vector)
//{
//
//}

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
	//if (vector.x < 0.0)
	//	delta.x = -1 * fmod(env_p->player_x, (double)env_p->block_size);
	//else
	//	delta.x = (double) env_p->block_size - fmod(env_p->player_x, (double)env_p->block_size);
	//if (vector.y < 0.0)
	//	delta.y = -1 * fmod(env_p->player_y, (double)env_p->block_size);
	//else
	//	delta.y = (double) env_p->block_size - fmod(env_p->player_y, (double)env_p->block_size);

	delta.x = vector.x;
	delta.y = vector.y;


	while (!check_ray_collision(env_p,(int) (vector.x + env_p->player_x + MINI_PLAYER_CENTER_POINT),
										(int) (vector.y + env_p->player_y + MINI_PLAYER_CENTER_POINT)))
	{
		vector.x += 0.1 * delta.x;
		vector.y += 0.1 * delta.y;
	}
	//if (sqrt(vector.x * vector.x + vector.y * vector.y) < (2 * (double)env_p->block_size))
	//{
	//	vector.x -=	delta.x;
	//	vector.y -= delta.y;
	//	while (!check_ray_collision(env_p,(int) (vector.x + env_p->player_x + MINI_PLAYER_CENTER_POINT),
	//									(int) (vector.y + env_p->player_y + MINI_PLAYER_CENTER_POINT)))
	//	{
	//		vector.x += 0.1 * delta.x;
	//		vector.y += 0.1 * delta.y;
	//	}
	//}
	return (vector);
}

double	get_ray_len(t_mlx_data *env_p, double degree_angle)
{
	t_vector	ray_vector;
	double		ray_len;

	ray_vector = get_ray_vector(env_p, degree_angle);
	env_p->ray_vector = ray_vector;
	ray_len = sqrt(ray_vector.x * ray_vector.x + ray_vector.y * ray_vector.y);
	return(ray_len);
}

t_coords	get_exact_collision_point(t_mlx_data *env_p, t_vector ray_vector)
{
	t_coords collision_point;

	if (ray_vector.x > 0)
		collision_point.x = (int) (ray_vector.x + env_p->player_x);
	else
		collision_point.x = (int) ceil(ray_vector.x + env_p->player_x);
	if (ray_vector.y > 0)
		collision_point.y = (int) (ray_vector.y + env_p->player_y);
	else
		collision_point.y = (int) ceil(ray_vector.y + env_p->player_y);
	collision_point.x += MINI_PLAYER_CENTER_POINT;
	collision_point.y += MINI_PLAYER_CENTER_POINT;
	return (collision_point);

}

char	get_wall_collision_side(t_mlx_data *env_p)
{
	t_vector ray_vector;
	t_coords wall_collision_pos;

	ray_vector = env_p->ray_vector;
	wall_collision_pos = get_exact_collision_point(env_p, ray_vector);
	if (ray_vector.x >= 0.0 && (wall_collision_pos.x % env_p->block_size) == 0)
		return ('E');
	else if (ray_vector.x < 0.0 && (wall_collision_pos.x % env_p->block_size) == 0)
		return ('W');
	else if (ray_vector.y >= 0.0 && (wall_collision_pos.y % env_p->block_size) == 0)
		return ('S');
	else if (ray_vector.y < 0.0 &&(wall_collision_pos.y % env_p->block_size) == 0)
		return ('N');
	else
		return (0);
}

//returns the position of the ray/wall collision in a double betwee 0 and 1
double get_wall_x(t_mlx_data *env_p)
{
	t_vector ray_vector;
	t_coords wall_collision_pos;

	ray_vector = env_p->ray_vector;
	wall_collision_pos = get_exact_collision_point(env_p, ray_vector);
	if (ray_vector.x >= 0.0 && (wall_collision_pos.x % env_p->block_size) == 0)
		return (fmod(ray_vector.y + env_p->player_y + (double)MINI_PLAYER_CENTER_POINT, (double)env_p->block_size) / (double)(env_p->block_size));
	else if (ray_vector.x < 0.0 && (wall_collision_pos.x % env_p->block_size) == 0)
		return (1.0 - fmod(ray_vector.y + env_p->player_y + (double)MINI_PLAYER_CENTER_POINT, (double)env_p->block_size) / (double)(env_p->block_size));
	else if (ray_vector.y >= 0.0 && (wall_collision_pos.y % env_p->block_size) == 0)
		return (1.0 - fmod(ray_vector.x + env_p->player_x + (double)MINI_PLAYER_CENTER_POINT, (double)env_p->block_size) / (double)(env_p->block_size));
	else if (ray_vector.y < 0.0 &&(wall_collision_pos.y % env_p->block_size) == 0)
		return (fmod(ray_vector.x + env_p->player_x + (double)MINI_PLAYER_CENTER_POINT, (double)env_p->block_size) / (double)(env_p->block_size));
	else
		return (-1.0);
}
