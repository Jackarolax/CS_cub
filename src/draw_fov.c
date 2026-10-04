/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fov.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 13:53:48 by anematol          #+#    #+#             */
/*   Updated: 2026/10/03 13:57:59 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	draw_ceil(t_mlx_data *env_p)
{
	t_coords	start;
	t_coords	end;

	start.x = 0;
	start.y = 0;
	end.x = WIN_WIDTH;
	end.y = 0;
	while (start.y <= WIN_HEIGHT / 2)
	{
		draw_line(env_p->background_buffer_img, start, end, env_p->ceil_color);
		start.y++;
		end.y++;
	}
}

void	draw_floor(t_mlx_data *env_p)
{
	t_coords	start;
	t_coords	end;

	start.x = 0;
	start.y = WIN_HEIGHT / 2;
	end.x = WIN_WIDTH;
	end.y = WIN_HEIGHT / 2;
	while (start.y <= WIN_HEIGHT)
	{
		draw_line(env_p->background_buffer_img, start, end, env_p->floor_color);
		start.y++;
		end.y++;
	}
}

void	draw_fov_line_sprite(t_img sprite,
	t_mlx_data *env_p, int x, int line_len)
{
	int		y_up;
	int		y_down;
	double	wall_x;
	double	wall_y;

	y_up = (WIN_HEIGHT / 2) - (line_len / 2);
	y_down = (WIN_HEIGHT / 2) + (line_len / 2);
	wall_x = get_wall_x(env_p);
	wall_y = 0.0;
	while (wall_y < 1.0)
	{
		if (y_up + (int)((double)(y_down - y_up) *wall_y) > 0
			&& y_up + (int)((double)(y_down - y_up) *wall_y)
				< env_p->background_img.height)
			pixel_put(env_p->background_img, x,
				y_up + (y_down - y_up) * wall_y,
				get_img_pixel(sprite, (int)((double)sprite.width * wall_x),
					(int)((double)sprite.height * wall_y)));
		wall_y += 0.9 / ((double)(y_down - y_up));
	}
}

void	draw_corresponding_fov_line(t_mlx_data *env_p, double degree_angle)
{
	int		x;
	int		line_len;
	double	sign;

	if (degree_angle < 0.0)
		sign = -1.0;
	else
		sign = 1.0;
	degree_angle *= sign;
	x = (WIN_WIDTH / 2)
		+ (int)round((double)(WIN_WIDTH / 2)
			*(degree_angle / ((double)FOV_DEGREE / 2.0)) * sign);
	line_len = ((FOV_HEIGHT_SCALING_FACTOR * WIN_HEIGHT / FOV_DEGREE)
			* WIN_HEIGHT) / get_ray_len(env_p, degree_angle * sign);
	if (get_wall_collision_side(env_p) == 'N')
		draw_fov_line_sprite(env_p->sprite_n_img, env_p, x, line_len);
	else if (get_wall_collision_side(env_p) == 'S')
		draw_fov_line_sprite(env_p->sprite_s_img, env_p, x, line_len);
	else if (get_wall_collision_side(env_p) == 'W')
		draw_fov_line_sprite(env_p->sprite_w_img, env_p, x, line_len);
	else if (get_wall_collision_side(env_p) == 'E')
		draw_fov_line_sprite(env_p->sprite_e_img, env_p, x, line_len);
}

void	draw_fov(t_mlx_data *env_p)
{
	double	degree_angle;
	double	line_delta;

	line_delta = ((double)FOV_DEGREE / (double)WIN_WIDTH);
	draw_corresponding_fov_line(env_p, 0);
	degree_angle = line_delta;
	while ((int) degree_angle < FOV_DEGREE / 2)
	{
		draw_corresponding_fov_line(env_p, degree_angle);
		draw_corresponding_fov_line(env_p, -degree_angle);
		degree_angle += line_delta;
	}
}
