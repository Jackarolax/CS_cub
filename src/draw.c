/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/08 20:05:46 by anematol          #+#    #+#             */
/*   Updated: 2026/09/03 19:50:10 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

static void reset_img(t_img image)
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
		pixel_put(img, begin.x + (int) (delta_x * i / line_len),
			begin.y + (delta_y * i / line_len), color);
		i++;
	}
}

void	draw_rotated_triangle(t_mlx_data *env_p)
{
	t_coords	point_right;
	t_coords	point_left_up;
	t_coords	point_left_down;
	t_coords	center_point;

	point_right.x = MINI_PLAYER_EDGE_POINT - 1;
	point_right.y = MINI_PLAYER_CENTER_POINT;
	point_left_up.x = 1;
	point_left_up.y = MINI_PLAYER_CENTER_POINT - MINI_PLAYER_WIDTH;
	point_left_down.x = 1;
	point_left_down.y = MINI_PLAYER_CENTER_POINT + MINI_PLAYER_WIDTH;
	center_point.x = MINI_PLAYER_CENTER_POINT;
	center_point.y = MINI_PLAYER_CENTER_POINT;
	draw_line(env_p->test_img,
		rotate_point(point_right, center_point, -env_p->player_diretion),
		rotate_point(point_left_down, center_point, -env_p->player_diretion),
		0x00FF0000);
	draw_line(env_p->test_img,
		rotate_point(point_left_down, center_point, -env_p->player_diretion),
		rotate_point(point_left_up, center_point, -env_p->player_diretion),
		0x00FF0000);
	draw_line(env_p->test_img,
		rotate_point(point_left_up, center_point, -env_p->player_diretion),
		rotate_point(point_right, center_point, -env_p->player_diretion),
		0x00FF0000);
}

// Get pixel color from sprite
/*static int	get_img_pixel(t_img image, int x, int y)
{
	char	*pixel;

	pixel = image.addr + (y * image.line_length + x * (image.bpp / 8));
	return (*(int *)pixel);
}*/

/*static void	put_img_inside_img(t_img small_image, t_img large_image,
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
}*/

int	draw_to_window(t_mlx_data	*env_p)
{
	//copy_background_to_buffer(&env);
	//draw_collectibles(&env);
	//draw_exit(&env, env.collectible_count == 0);
	//put_img_inside_img(env.player_img, env.buffer_img,
	//	env.player_x, env.player_y);
	//put_img_inside_img(env_p->test_img, env_p->background_img,
	//	(int) env_p->player_x, (int) env_p->player_y);
	mlx_put_image_to_window(env_p->mlx, env_p->win, env_p->background_img.img, 0, 0);
	reset_img(env_p->test_img);
	draw_rotated_triangle(env_p);
	mlx_put_image_to_window(env_p->mlx, env_p->win, env_p->test_img.img, (int) env_p->player_x, (int) env_p->player_y);
	return (0);
}
