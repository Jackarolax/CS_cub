/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 18:20:30 by ssin              #+#    #+#             */
/*   Updated: 2026/09/13 13:17:30 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// add sprites function

void	pixel_put(t_img img, int x, int y, int color)
{
	char	*dst;

	dst = img.addr + (y * img.line_length + x * (img.bpp / 8));
	*(unsigned int*)dst = color;
}

t_coords	rotate_point(t_coords point, t_coords center, double angle)
{
	t_coords	delta_point;
	t_coords	new_delta;
	t_coords	new_point;

	// Translate to origin
	delta_point.x = point.x - center.x;
	delta_point.y = point.y - center.y;

	// Rotate need to understand the math behind that better
	new_delta.x = delta_point.x * cos(angle) - delta_point.y * sin(angle);
	new_delta.y = delta_point.x * sin(angle) + delta_point.y * cos(angle);

	// Translate back
	new_point.x = new_delta.x + center.x;
	new_point.y = new_delta.y + center.y;

	return (new_point);
}

void	set_minilibx(t_mlx_data *env_p)
{

	env_p->mlx = mlx_init();

	// draw triangle
	env_p->player_x = 910.0;
	env_p->player_y = 210.0;
	env_p->player_direction = 2 * M_PI / 4;
	env_p->block_size = 100;
	env_p->map = malloc(15 * sizeof(char*));
	env_p->map[0] = ft_strdup("111111111111111111111111111111111");
	env_p->map[1] = ft_strdup("111111111000000000110000000000001");
	env_p->map[2] = ft_strdup("111111111011000001110000000000001");
	env_p->map[3] = ft_strdup("111111111001000000000000000000001");
	env_p->map[4] = ft_strdup("111111111011000001110000000000001");
	env_p->map[5] = ft_strdup("100000000011000001110111111111111");
	env_p->map[6] = ft_strdup("111101111111110111000000100011111");
	env_p->map[7] = ft_strdup("111101111111110111010100100011111");
	env_p->map[8] = ft_strdup("110000001101010111000000100011111");
	env_p->map[9] = ft_strdup("100000000000000011000000100011111");
	env_p->map[10] = ft_strdup("100000000000000011010100100011111");
	env_p->map[11] = ft_strdup("11000001110101011111011110N011111");
	env_p->map[12] = ft_strdup("11110111 1110101 1011110100011111");
	env_p->map[13] = ft_strdup("11111111 1111111 1111111111111111");
	env_p->map[14] = NULL;
	env_p->map_height = 14;
	env_p->map_width = 35;
	env_p->width = env_p->map_width * env_p->block_size;
	env_p->height = env_p->map_height * env_p->block_size;
	env_p->win = mlx_new_window(env_p->mlx, env_p->win_width,
		env_p->win_height, "CUB 3D");
	env_p->player_img.width = MINI_PLAYER_EDGE_POINT;
	env_p->player_img.height = MINI_PLAYER_EDGE_POINT;
	env_p->player_img.img = mlx_new_image(env_p->mlx, env_p->player_img.width,
		env_p->player_img.height);
	env_p->player_img.addr = mlx_get_data_addr(env_p->player_img.img,
		&env_p->player_img.bpp, &env_p->player_img.line_length,
		&env_p->player_img.endian);
	env_p->background_img.width = env_p->win_width;
	env_p->background_img.height = env_p->win_height;
	env_p->background_img.img = mlx_new_image(env_p->mlx, env_p->background_img.width,
		env_p->background_img.height);
	env_p->background_img.addr = mlx_get_data_addr(env_p->background_img.img,
		&env_p->background_img.bpp, &env_p->background_img.line_length,
		&env_p->background_img.endian);
	env_p->buffer_img.width = env_p->width;
	env_p->buffer_img.height = env_p->height;
	env_p->buffer_img.img = mlx_new_image(env_p->mlx, env_p->buffer_img.width,
		env_p->buffer_img.height);
	env_p->buffer_img.addr = mlx_get_data_addr(env_p->buffer_img.img,
		&env_p->buffer_img.bpp, &env_p->buffer_img.line_length,
		&env_p->buffer_img.endian);

	//draw_rotated_triangle(env_p);
	draw_obstacles(env_p);
	mlx_put_image_to_window(env_p->mlx, env_p->win, env_p->player_img.img,
		(int) env_p->player_x, (int) env_p->player_y);
	mlx_hook(env_p->win, DestroyNotify, KeyPressMask, close_window, env_p);
	mlx_hook(env_p->win, KeyPress, KeyPressMask, handle_key_press, env_p);
	mlx_hook(env_p->win, KeyRelease, KeyReleaseMask, handle_key_release, env_p);
	mlx_loop_hook(env_p->mlx, update_game, env_p);
	mlx_loop(env_p->mlx);
}
