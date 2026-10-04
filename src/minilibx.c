/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 18:20:30 by ssin              #+#    #+#             */
/*   Updated: 2026/10/03 19:32:43 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

// Load sprite into env from XPM file
void	load_sprite(t_mlx_data *env_p, t_img *image_p, char *path)
{
	int	width;
	int	height;

	image_p->img = mlx_xpm_file_to_image(env_p->mlx, path, &width,
			&height);
	if (!image_p->img)
	{
		printf("Error: Could not load sprite %s\n", path);
		destroy_everything_and_exit(env_p, 1);
	}
	image_p->width = width;
	image_p->height = height;
	image_p->addr = mlx_get_data_addr(image_p->img, &image_p->bpp,
			&image_p->line_length, &image_p->endian);
}

t_coords	rotate_point(t_coords point, t_coords center, double angle)
{
	t_coords	delta_point;
	t_coords	new_delta;
	t_coords	new_point;

	delta_point.x = point.x - center.x;
	delta_point.y = point.y - center.y;
	new_delta.x = delta_point.x * cos(angle) - delta_point.y * sin(angle);
	new_delta.y = delta_point.x * sin(angle) + delta_point.y * cos(angle);
	new_point.x = new_delta.x + center.x;
	new_point.y = new_delta.y + center.y;
	return (new_point);
}

void	set_player_position_from_i_j(t_mlx_data *env_p, int i, int j)
{
	env_p->player_x = j * env_p->block_size
		+ (env_p->block_size / 2) - MINI_PLAYER_CENTER_POINT;
	env_p->player_y = i * env_p->block_size
		+ (env_p->block_size / 2) - MINI_PLAYER_CENTER_POINT;
	if (env_p->map_info->map[i][j] == 'E')
		env_p->player_direction = 0 * M_PI / 2;
	else if (env_p->map_info->map[i][j] == 'S')
		env_p->player_direction = 1 * M_PI / 2;
	else if (env_p->map_info->map[i][j] == 'W')
		env_p->player_direction = 2 * M_PI / 2;
	else if (env_p->map_info->map[i][j] == 'N')
		env_p->player_direction = 3 * M_PI / 2;
}

//the map has to be initialized before calling this function
//assumes there is only one player position character (N, E, S, W)
void	set_player_position(t_mlx_data *env_p)
{
	int	i;
	int	j;

	if (!env_p->map_info->map)
		destroy_everything_and_exit(env_p, EXIT_FAILURE);
	i = 0;
	while (env_p->map_info->map[i])
	{
		j = 0;
		while (env_p->map_info->map[i][j])
		{
			if (env_p->map_info->map[i][j] == 'N'
				|| env_p->map_info->map[i][j] == 'E'
				|| env_p->map_info->map[i][j] == 'S'
				|| env_p->map_info->map[i][j] == 'W')
				return (set_player_position_from_i_j(env_p, i, j));
			j++;
		}
		i++;
	}
	destroy_everything_and_exit(env_p, EXIT_FAILURE);
}

void	create_image(t_mlx_data *env_p, t_img *image_p, int width, int height)
{
	image_p->width = width;
	image_p->height = height;
	image_p->img = mlx_new_image(env_p->mlx, width, height);
	image_p->addr = mlx_get_data_addr(image_p->img, &image_p->bpp,
			&image_p->line_length, &image_p->endian);
}

void	load_images(t_mlx_data *env_p)
{
	create_image(env_p, &env_p->player_img,
		MINI_PLAYER_EDGE_POINT, MINI_PLAYER_EDGE_POINT);
	create_image(env_p, &env_p->background_img, WIN_WIDTH, WIN_HEIGHT);
	create_image(env_p, &env_p->background_buffer_img, WIN_WIDTH, WIN_HEIGHT);
	load_sprite(env_p, &env_p->sprite_n_img, "./flagstone-tile-gray.xpm");
	load_sprite(env_p, &env_p->sprite_e_img, "./flagstone-tile-gray.xpm");
	load_sprite(env_p, &env_p->sprite_s_img, "./flagstone-tile-gray.xpm");
	load_sprite(env_p, &env_p->sprite_w_img, "./flagstone-tile-gray.xpm");
}

void	set_minilibx(t_mlx_data *env_p)
{
	env_p->mlx = mlx_init();
	env_p->block_size = BLOCK_SIZE;
	env_p->ceil_color = GREY;
	env_p->floor_color = DARK_GREY;
	set_player_position(env_p);
	env_p->width = env_p->map_info->map_width * env_p->block_size;
	env_p->height = env_p->map_info->map_height * env_p->block_size;
	env_p->win = mlx_new_window(env_p->mlx, WIN_WIDTH, WIN_HEIGHT, "CUB 3D");
	load_images(env_p);
	draw_ceil(env_p);
	draw_floor(env_p);
	mlx_hook(env_p->win, DESTROY_NOTIFY, KEY_PRESS_MASK, close_window, env_p);
	mlx_hook(env_p->win, KEY_PRESS, KEY_PRESS_MASK, handle_key_press, env_p);
	mlx_hook(env_p->win, KEY_RELEASE, KEY_RELEASE_MASK,
		handle_key_release, env_p);
	mlx_loop_hook(env_p->mlx, update_game, env_p);
}
