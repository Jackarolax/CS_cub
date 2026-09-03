/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 18:20:30 by ssin              #+#    #+#             */
/*   Updated: 2026/09/03 18:21:21 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

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

	// Rotate
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
	env_p->win = mlx_new_window(env_p->mlx, env_p->width,
		env_p->height, "CUB 3D");
	env_p->test_img.width = MINI_PLAYER_EDGE_POINT;
	env_p->test_img.height = MINI_PLAYER_EDGE_POINT;
	env_p->test_img.img = mlx_new_image(env_p->mlx, env_p->test_img.width,
		env_p->test_img.height);
	env_p->test_img.addr = mlx_get_data_addr(env_p->test_img.img,
		&env_p->test_img.bpp, &env_p->test_img.line_length,
		&env_p->test_img.endian);
	env_p->background_img.width = env_p->width;
	env_p->background_img.height = env_p->height;
	env_p->background_img.img = mlx_new_image(env_p->mlx, env_p->background_img.width,
		env_p->background_img.height);
	env_p->background_img.addr = mlx_get_data_addr(env_p->background_img.img,
		&env_p->background_img.bpp, &env_p->background_img.line_length,
		&env_p->background_img.endian);

	// draw triangle
	env_p->player_x = 500.0;
	env_p->player_y = 500.0;
	env_p->moving_speed = 0.5;
	env_p->player_diretion = 2 * M_PI / 4;
	env_p->turning_speed = 0.0001;
	//draw_rotated_triangle(env_p);
	mlx_put_image_to_window(env_p->mlx, env_p->win, env_p->test_img.img,
		(int) env_p->player_x, (int) env_p->player_y);
	mlx_hook(env_p->win, DESTROY_NOTIFY, KEY_PRESS_MASK, close_window, env_p);
	mlx_hook(env_p->win, KEY_PRESS, KEY_PRESS_MASK, handle_key_press, env_p);
	mlx_hook(env_p->win, KEY_RELEASE, KEY_PRESS_MASK, handle_key_release, env_p);
	mlx_loop_hook(env_p->mlx, update_game, env_p);
	mlx_loop(env_p->mlx);
}
