/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/08 20:05:46 by anematol          #+#    #+#             */
/*   Updated: 2026/09/05 12:21:57 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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
	while (i <= line_len && begin.x + (int) (delta_x * i / line_len) <= img.width
						&& begin.y + (delta_y * i / line_len) <= img.height)
	{
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

void	draw_obstacles(t_mlx_data *env_p)
{
	int		grid_x;
	int		grid_y;
	char	**map;

	map = env_p->map;
	if (!map)
	{
		printf("Error: draw_obstacles called with NULL map\n");
		return ;
	}
	grid_y = 0;
	while (map[grid_y])
	{
		grid_x = 0;
		while (map[grid_y][grid_x])
		{
			if (map[grid_y][grid_x] == '1')
				draw_square(env_p->background_img,
					give_coords(grid_x * env_p->block_size,
					grid_y * env_p->block_size),
					env_p->block_size - 2, 0xFFFFFFFF);
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

void	draw_rotated_triangle(t_mlx_data *env_p)
{
	t_coords	point_right;
	t_coords	point_left_up;
	t_coords	point_left_down;
	t_coords	center_point;

	point_right.x = MINI_PLAYER_CENTER_POINT + MINI_PLAYER_LENGTH / 2;
	point_right.y = MINI_PLAYER_CENTER_POINT;
	point_left_up.x = MINI_PLAYER_CENTER_POINT - MINI_PLAYER_LENGTH / 2;
	point_left_up.y = MINI_PLAYER_CENTER_POINT - MINI_PLAYER_WIDTH / 2;
	point_left_down.x = MINI_PLAYER_CENTER_POINT - MINI_PLAYER_LENGTH / 2;
	point_left_down.y = MINI_PLAYER_CENTER_POINT + MINI_PLAYER_WIDTH / 2;
	center_point.x = MINI_PLAYER_CENTER_POINT;
	center_point.y = MINI_PLAYER_CENTER_POINT;
	draw_line(env_p->player_img,
		rotate_point(point_right, center_point, env_p->player_direction),
		rotate_point(point_left_down, center_point, env_p->player_direction),
		0x00FF0000);
	draw_line(env_p->player_img,
		rotate_point(point_left_down, center_point, env_p->player_direction),
		rotate_point(point_left_up, center_point, env_p->player_direction),
		0x00FF0000);
	draw_line(env_p->player_img,
		rotate_point(point_left_up, center_point, env_p->player_direction),
		rotate_point(point_right, center_point, env_p->player_direction),
		0x00FF0000);
}

// Get pixel color from sprite
int	get_img_pixel(t_img image, int x, int y)
{
	char	*pixel;

	pixel = image.addr + (y * image.line_length + x * (image.bpp / 8));
	return (*(int *)pixel);
}
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

void	draw_ray(t_img image, t_mlx_data *env_p, double degree_angle)
{
	double	vector_x;
	double	vector_y;
	double	delta_x;
	double	delta_y;

	vector_x = cos(env_p->player_direction + (degree_angle / 180 * M_PI));
	vector_y = sin(env_p->player_direction + (degree_angle / 180 * M_PI));
	delta_x = vector_x;
	delta_y = vector_y;
	while (!check_ray_collision(env_p,(int) (vector_x + env_p->player_x + MINI_PLAYER_CENTER_POINT),
										(int) (vector_y + env_p->player_y + MINI_PLAYER_CENTER_POINT)))
	{
		vector_x += delta_x;
		vector_y += delta_y;
	}
	draw_line(image, give_coords((int) env_p->player_x + MINI_PLAYER_CENTER_POINT, (int) env_p->player_y + MINI_PLAYER_CENTER_POINT),
		give_coords((int)(vector_x + env_p->player_x + MINI_PLAYER_CENTER_POINT), (int) (vector_y + env_p->player_y + MINI_PLAYER_CENTER_POINT)), 0x00FF0000);


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
	int i;

	//copy_background_to_buffer(&env);
	//draw_collectibles(&env);
	//draw_exit(&env, env.collectible_count == 0);
	//put_img_inside_img(env.player_img, env.buffer_img,
	//	env.player_x, env.player_y);
	//put_img_inside_img(env_p->player_img, env_p->background_img,
	//	(int) env_p->player_x, (int) env_p->player_y);

	reset_img(env_p->player_img);
	draw_rotated_triangle(env_p);
	reset_img(env_p->background_img);
	draw_obstacles(env_p);
	draw_ray(env_p->background_img, env_p, 0);
	i = 1;
	while (i < 45)
	{
		draw_ray(env_p->background_img, env_p, i);
		draw_ray(env_p->background_img, env_p, -i);
		i++;
	}
	//copy_background_to_buffer(env_p);
	//put_img_inside_img(env_p->player_img, env_p->buffer_img, (int) env_p->player_x, (int) env_p->player_y);
	mlx_put_image_to_window(env_p->mlx, env_p->win, env_p->background_img.img, 0, 0);
	put_img_inside_img(env_p->player_img, env_p->background_img, (int) env_p->player_x, (int) env_p->player_y);
	return (0);
}
