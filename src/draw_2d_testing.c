/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2d_testing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 13:47:56 by anematol          #+#    #+#             */
/*   Updated: 2026/10/03 14:23:28 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	draw_rotated_triangle(t_mlx_data *env_p)
{
	t_3points	triangle;
	t_coords	center_point;

	triangle.p1.x = MINI_PLAYER_CENTER_POINT + MINI_PLAYER_LENGTH / 2;
	triangle.p1.y = MINI_PLAYER_CENTER_POINT;
	triangle.p2.x = MINI_PLAYER_CENTER_POINT - MINI_PLAYER_LENGTH / 2;
	triangle.p2.y = MINI_PLAYER_CENTER_POINT - MINI_PLAYER_WIDTH / 2;
	triangle.p3.x = MINI_PLAYER_CENTER_POINT - MINI_PLAYER_LENGTH / 2;
	triangle.p3.y = MINI_PLAYER_CENTER_POINT + MINI_PLAYER_WIDTH / 2;
	center_point.x = MINI_PLAYER_CENTER_POINT;
	center_point.y = MINI_PLAYER_CENTER_POINT;
	triangle.p1 = rotate_point(triangle.p1, center_point,
			env_p->player_direction);
	triangle.p2 = rotate_point(triangle.p2, center_point,
			env_p->player_direction);
	triangle.p3 = rotate_point(triangle.p3, center_point,
			env_p->player_direction);
	fill_triangle(env_p->player_img, triangle, RED + BLUE + GREEN);
	draw_triangle(env_p->player_img, triangle, RED);
}

void	draw_obstacles(t_mlx_data *env_p)
{
	int		grid_x;
	int		grid_y;

	grid_y = 0;
	while (env_p->map_info->map[grid_y])
	{
		grid_x = 0;
		while (env_p->map_info->map[grid_y][grid_x])
		{
			if (env_p->map_info->map[grid_y][grid_x] == '1')
			{
				fill_square(env_p->background_img,
					give_coords(grid_x * env_p->block_size,
						grid_y * env_p->block_size),
					env_p->block_size, WHITE);
				draw_square(env_p->background_img,
					give_coords(grid_x * env_p->block_size,
						grid_y * env_p->block_size),
					env_p->block_size, WHITE);
			}
			grid_x++;
		}
		grid_y++;
	}
}

void	draw_2nd_ray(t_img image, t_mlx_data *env_p, t_coords wall_coll_pos)
{
	t_vector	ray_vector;

	ray_vector = env_p->ray_vector;
	if (ray_vector.x >= 0.0 && (wall_coll_pos.x % env_p->block_size) == 0
		&& (wall_coll_pos.y % env_p->block_size) != 0)
		draw_line(image, wall_coll_pos,
			give_coords(wall_coll_pos.x + env_p->block_size, wall_coll_pos.y),
			GREEN);
	else if (ray_vector.x < 0.0 && (wall_coll_pos.x % env_p->block_size) == 0
		&& (wall_coll_pos.y % env_p->block_size) != 0)
		draw_line(image, wall_coll_pos,
			give_coords(wall_coll_pos.x - env_p->block_size, wall_coll_pos.y),
			GREEN);
	else if (ray_vector.y >= 0.0 && (wall_coll_pos.y % env_p->block_size) == 0
		&& (wall_coll_pos.x % env_p->block_size) != 0)
		draw_line(image, wall_coll_pos,
			give_coords(wall_coll_pos.x, wall_coll_pos.y + env_p->block_size),
			RED);
	else if (ray_vector.y < 0.0 && (wall_coll_pos.y % env_p->block_size) == 0
		&& (wall_coll_pos.x % env_p->block_size) != 0)
		draw_line(image, wall_coll_pos,
			give_coords(wall_coll_pos.x, wall_coll_pos.y - env_p->block_size),
			RED);
}

void	draw_ray(t_img image, t_mlx_data *env_p, double degree_angle)
{
	t_vector	ray_vector;
	t_coords	wall_coll_pos;

	ray_vector = get_ray_vector(env_p, degree_angle);
	env_p->ray_vector = ray_vector;
	wall_coll_pos = get_exact_collision_point(env_p, ray_vector);
	draw_line(image,
		give_coords((int) env_p->player_x + MINI_PLAYER_CENTER_POINT,
			(int) env_p->player_y + MINI_PLAYER_CENTER_POINT),
		wall_coll_pos,
		0x00FF0000);
	draw_2nd_ray(image, env_p, wall_coll_pos);
}

void	draw_fov_line(t_mlx_data *env_p, int x, int line_len)
{
	int		y_up;
	int		y_down;
	int		thickness;
	double	wall_x;

	y_up = (WIN_HEIGHT / 2) - (line_len / 2);
	y_down = (WIN_HEIGHT / 2) + (line_len / 2);
	thickness = (y_down - y_up) / 20;
	wall_x = get_wall_x(env_p);
	if (wall_x < 0.05 || wall_x > 0.95)
		draw_line(env_p->background_img, give_coords(x, y_up),
			give_coords(x, y_down), BLUE);
	else
		draw_line(env_p->background_img, give_coords(x, y_up),
			give_coords(x, y_down), BLUE + GREEN);
	if (y_up + thickness >= 0)
		draw_line(env_p->background_img, give_coords(x, y_up),
			give_coords(x, y_up + thickness), BLUE);
	if (y_down - thickness <= env_p->background_img.height)
		draw_line(env_p->background_img, give_coords(x, y_down - thickness),
			give_coords(x, y_down), BLUE);
}
