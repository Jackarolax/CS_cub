/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/08 20:05:46 by anematol          #+#    #+#             */
/*   Updated: 2026/09/20 18:30:08 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

t_coords	give_coords(int x, int y)
{
	t_coords	coords;
	coords.x = x;
	coords.y = y;
	return (coords);
}

void reset_img(t_img image)
{
	char *pixels;
	int total_size;

	pixels = mlx_get_data_addr(image.img, &image.bpp, &image.line_length, &image.endian);

	// Calculate total size in bytes (size_line is the width in bytes, including padding)
	total_size = image.line_length * image.height;

	// Efficiently zero it out
	ft_bzero(pixels, total_size);
}
void	draw_line(t_img img, t_coords begin, t_coords end, int color)
{
	double	delta_x;
	double	delta_y;
	double	line_len;
	double	i;

	delta_x = (double) (end.x - begin.x);
	delta_y = (double) (end.y - begin.y);
	line_len = sqrt((delta_x * delta_x) + (delta_y * delta_y));
	i = 0.0;
	while (i <= line_len)
	{
		if (begin.x + (int) (delta_x * i / line_len) <= img.width
			&& begin.y + (delta_y * i / line_len) <= img.height
			&& begin.x + (int) (delta_x * i / line_len) >= 0
			&& begin.y + (delta_y * i / line_len) >= 0)
			pixel_put(img, begin.x + (int) (delta_x * i / line_len),
				begin.y + (delta_y * i / line_len), color);
		i++;
	}
}


void	draw_square(t_img img, t_coords start_point, int len, int color)
{
	t_coords	end_point;

	end_point.x = start_point.x + len;
	end_point.y = start_point.y;
	draw_line(img, start_point, end_point, color);
	start_point.x += len;
	start_point.y += len;
	draw_line(img, start_point, end_point, color);
	end_point.x -= len;
	end_point.y += len;
	draw_line(img, start_point, end_point, color);
	start_point.x -= len;
	start_point.y -= len;
	draw_line(img, start_point, end_point, color);
}

void	fill_square(t_img img, t_coords start_point, int len, int color)
{
	t_coords	end_point;
	int			i;

	end_point.x = start_point.x + len;
	end_point.y = start_point.y;
	i = 0;
	while(i <= len)
	{
		draw_line(img, start_point, end_point, color);
		start_point.y++;
		end_point.y++;
		i++;
	}
}

void	draw_obstacles(t_mlx_data *env_p)
{
	int		grid_x;
	int		grid_y;

	grid_y = 0;
	while (env_p->map[grid_y])
	{
		grid_x = 0;
		while (env_p->map[grid_y][grid_x])
		{
			if (env_p->map[grid_y][grid_x] == '1')
			{
				fill_square(env_p->background_img,
					give_coords(grid_x * env_p->block_size,
					grid_y * env_p->block_size),
					env_p->block_size, WHITE);
				draw_square(env_p->background_img,
					give_coords(grid_x * env_p->block_size,
					grid_y * env_p->block_size),
					env_p->block_size, RED);
			}
			grid_x++;
		}
		grid_y++;
	}
}

void	copy_background_to_buffer(t_mlx_data *env_p)
{
	ft_memcpy(env_p->buffer_img.addr, env_p->background_img.addr,
		env_p->background_img.height * env_p->background_img.line_length);
}

//the ostacle sprite has to be initialized already
//void	draw_obstacles(t_mlx_data *env_p)
//{
//	int		grid_x;
//	int		grid_y;
//	char	**map;
//
//	map = env_p->map;
//	if (!map)
//	{
//		ft_printf("Error: draw_obstacles called with NULL map\n");
//		return ;
//	}
//	grid_y = 0;
//	while (grid_y < env_p->map_height)
//	{
//		grid_x = 0;
//		while (grid_x < env_p->map_width)
//		{
//			if (map[grid_y][grid_x] == '1')
//				put_img_inside_img(env_p->wall_img,
//					env_p->background_img,
//					grid_x * env_p->block_size,
//					grid_y * env_p->block_size);
//			grid_x++;
//		}
//		grid_y++;
//	}
//}

t_3points give_3points(t_coords p1, t_coords p2, t_coords p3)
{
	t_3points points;

	points.p1 = p1;
	points.p2 = p2;
	points.p3 = p3;
	return (points);
}

void	draw_triangle(t_img img, t_3points triangle, int color)
{
	draw_line(img, triangle.p1, triangle.p2, color);
	draw_line(img, triangle.p2, triangle.p3, color);
	draw_line(img, triangle.p3, triangle.p1, color);
}

void	fill_triangle(t_img img, t_3points triangle, int color)
{
	double	delta_x;
	double	delta_y;
	double	line_len;
	double	i;

	delta_x = (double) (triangle.p3.x - triangle.p2.x);
	delta_y = (double) (triangle.p3.y - triangle.p2.y);
	line_len = sqrt((delta_x * delta_x) + (delta_y * delta_y));
	i = 0.0;
	while (i <= line_len)
	{
		if (triangle.p2.x + (int) (delta_x * i / line_len) <= img.width
			&& triangle.p2.y + (delta_y * i / line_len) <= img.height
			&& triangle.p2.x + (int) (delta_x * i / line_len) >= 0
			&& triangle.p2.y + (delta_y * i / line_len) >= 0)
			draw_line(img, triangle.p1,
				give_coords(triangle.p2.x + (int) (delta_x * i / line_len),
				triangle.p2.y + (delta_y * i / line_len)), color);
		i += 0.01;
	}
}

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
	triangle.p1 = rotate_point(triangle.p1, center_point, env_p->player_direction);
	triangle.p2 = rotate_point(triangle.p2, center_point, env_p->player_direction);
	triangle.p3 = rotate_point(triangle.p3, center_point, env_p->player_direction);
	fill_triangle(env_p->player_img, triangle, RED + BLUE + GREEN);
	draw_triangle(env_p->player_img, triangle, RED);
}

// Get pixel color from sprite
static int	get_img_pixel(t_img image, int x, int y)
{
	char	*pixel;

	pixel = image.addr + (y * image.line_length + x * (image.bpp / 8));
	return (*(int *)pixel);
}

void	draw_ray(t_img image, t_mlx_data *env_p, double degree_angle)
{
	t_vector	ray_vector;
	t_coords	wall_collision_pos;

	ray_vector = get_ray_vector(env_p, degree_angle);
	env_p->ray_vector = ray_vector;
	wall_collision_pos = get_exact_collision_point(env_p, ray_vector);
	draw_line(image,
		give_coords((int) env_p->player_x + MINI_PLAYER_CENTER_POINT,
		(int) env_p->player_y + MINI_PLAYER_CENTER_POINT),
		wall_collision_pos,
		0x00FF0000);
	if (ray_vector.x >= 0.0 && (wall_collision_pos.x % env_p->block_size) == 0 && (wall_collision_pos.y % env_p->block_size) != 0)
		draw_line(image, wall_collision_pos, give_coords(wall_collision_pos.x + env_p->block_size, wall_collision_pos.y), RED);
	else if (ray_vector.x < 0.0 && (wall_collision_pos.x % env_p->block_size) == 0 && (wall_collision_pos.y % env_p->block_size) != 0)
		draw_line(image, wall_collision_pos, give_coords(wall_collision_pos.x - env_p->block_size, wall_collision_pos.y), RED);
	else if (ray_vector.y >= 0.0 && (wall_collision_pos.y % env_p->block_size) == 0 && (wall_collision_pos.x % env_p->block_size) != 0)
		draw_line(image, wall_collision_pos, give_coords(wall_collision_pos.x, wall_collision_pos.y + env_p->block_size), RED);
	else if (ray_vector.y < 0.0 &&(wall_collision_pos.y % env_p->block_size) == 0 && (wall_collision_pos.x % env_p->block_size) != 0)
		draw_line(image, wall_collision_pos, give_coords(wall_collision_pos.x, wall_collision_pos.y - env_p->block_size), RED);

	//wall_collision_pos.x = wall_collision_pos.x - (wall_collision_pos.x % env_p->block_size) - env_p->block_size
	//					* (ray_vector.x < 0.0 && (wall_collision_pos.x % env_p->block_size) == 0);
	//wall_collision_pos.y = wall_collision_pos.y - (wall_collision_pos.y % env_p->block_size) - env_p->block_size
	//					* (ray_vector.y < 0.0 && (wall_collision_pos.y % env_p->block_size) == 0);
	//draw_square(image, wall_collision_pos, env_p->block_size, RED);
}
void	draw_fov_line(t_img image, t_mlx_data *env_p, int x, int line_len)
{
	int		y_up;
	int		y_down;
	int		thickness;
	double	wall_x;

	y_up = (env_p->win_height / 2) - (line_len / 2);
	y_down = (env_p->win_height / 2) + (line_len / 2);
	thickness = (y_down - y_up) / 20;
	wall_x = get_wall_x(env_p);
	if (wall_x < 0.05 || wall_x > 0.95)
		draw_line(image, give_coords(x, y_up),
			give_coords(x, y_down), BLUE);
	else
		draw_line(image, give_coords(x, y_up),
			give_coords(x, y_down), BLUE + GREEN);
	if (y_up + thickness >= 0)
		draw_line(image, give_coords(x, y_up), give_coords(x, y_up + thickness), BLUE);
	if (y_down - thickness <= image.height)
		draw_line(image, give_coords(x, y_down - thickness), give_coords(x, y_down), BLUE);

}
void	draw_fov_line_sprite(t_img image, t_img sprite, t_mlx_data *env_p, int x, int line_len)
{
	int		y_up;
	int		y_down;
	double	wall_x;
	double	wall_y;

	y_up =  (env_p->win_height / 2) - (line_len / 2);
	y_down =  (env_p->win_height / 2) + (line_len / 2);
	wall_x = get_wall_x(env_p);
	wall_y = 0.0;
	get_img_pixel(sprite, (int)((double)sprite.width * wall_x), (int)((double)sprite.height * wall_y));
	while(wall_y < 1.0)
	{
		if (y_up + (int)((double)(y_down - y_up) * wall_y) > 0
			&& y_up + (int)((double)(y_down - y_up) * wall_y) < image.height)
			pixel_put(image, x, y_up + (y_down - y_up) * wall_y,
				get_img_pixel(sprite, (int)((double)sprite.width * wall_x), (int)((double)sprite.height * wall_y)));
		wall_y += 0.9 /((double)(y_down - y_up));
	}
}

void	draw_corresponding_fov_line(t_img image, t_mlx_data *env_p, double degree_angle)
{
	int		x;
	int		line_len;
	double	sign;

	if (degree_angle < 0.0)
		sign = -1.0;
	else
		sign = 1.0;
	degree_angle *= sign;
	x = (env_p->win_width / 2)
		 + (int)round((double)(env_p->win_width / 2)
		 * (degree_angle / ((double)FOV_DEGREE / 2.0)) * sign);
	line_len = ((FOV_HEIGHT_SCALING_FACTOR * env_p->win_height / FOV_DEGREE)
		* env_p->win_height) / get_ray_len(env_p, degree_angle * sign);
	if (get_wall_collision_side(env_p) == 'N')
		draw_fov_line_sprite(image, env_p->sprite_n_img, env_p, x, line_len);
	else if (get_wall_collision_side(env_p) == 'S')
		draw_fov_line_sprite(image, env_p->sprite_n_img, env_p, x, line_len);
	else if (get_wall_collision_side(env_p) == 'W')
		draw_fov_line_sprite(image, env_p->sprite_n_img, env_p, x, line_len);
	else if (get_wall_collision_side(env_p) == 'E')
		draw_fov_line_sprite(image, env_p->sprite_n_img, env_p, x, line_len);
}

void	draw_fov(t_img image, t_mlx_data *env_p)
{
	double	degree_angle;
	double	line_delta;

	line_delta = ((double)FOV_DEGREE / (double)WIN_WIDTH);
	draw_corresponding_fov_line(image, env_p, 0);
	degree_angle = line_delta;
	while ((int) degree_angle < FOV_DEGREE / 2)
	{
		draw_corresponding_fov_line(image, env_p, degree_angle);
		draw_corresponding_fov_line(image, env_p, -degree_angle);
		degree_angle += line_delta;
	}
}

void	put_img_inside_img(t_img small_image, t_img large_image,
						int x, int y)
{
	int	i;
	int	j;
	int	pixel_color;

	i = 0;
	while (i < small_image.height)
	{
		j = 0;
		while (j < small_image.width)
		{
			pixel_color = get_img_pixel(small_image, j, i);
			if ((pixel_color > 0)
				&& (x + j >= 0 && x + j < large_image.width)
				&& (y + i >= 0 && y + i < large_image.height))
			{
				pixel_put(large_image, x + j, y + i, pixel_color);
			}
			j++;
		}
		i++;
	}
}

int	draw_to_window(t_mlx_data	*env_p)
{
	reset_img(env_p->background_img);
	draw_fov(env_p->background_img, env_p);
	//reset_img(env_p->player_img);
	//draw_rotated_triangle(env_p);
	//draw_obstacles(env_p);
	//draw_ray(env_p->background_img, env_p, 0);
	//double i = 1.0;
	//while (i < 45)
	//{
	//	draw_ray(env_p->background_img, env_p, i);
	//	draw_ray(env_p->background_img, env_p, -i);
	//	i += 1.0;
	//}
	//copy_background_to_buffer(env_p);
	put_img_inside_img(env_p->player_img, env_p->background_img, (int) env_p->player_x, (int) env_p->player_y);
	mlx_put_image_to_window(env_p->mlx, env_p->win, env_p->background_img.img, 0, 0);
	return (0);
}
