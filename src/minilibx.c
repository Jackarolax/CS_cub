/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 18:20:30 by ssin              #+#    #+#             */
/*   Updated: 2026/09/24 22:58:48 by anematol         ###   ########.fr       */
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
		exit(1);
		return ;
	}
	//	if (check_width != image_p->width || check_height != image_p->height)
	//	{
	//		printf("Error: Sprite %s has
	//incorrect dimensions (expected %dx%d, got %dx%d)\n",
	//			path, image_p->width, image_p->height, check_width, check_height);
	//		destroy_everything_and_exit(env_p, 1);
	//		exit(1);
	//		return ;
	//	}
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

	// Translate to origin
	delta_point.x = point.x - center.x;
	delta_point.y = point.y - center.y;

	// Rotate need to understand the math behind that better
	// Rotate need to understand the math behind that better
	new_delta.x = delta_point.x * cos(angle) - delta_point.y * sin(angle);
	new_delta.y = delta_point.x * sin(angle) + delta_point.y * cos(angle);

	// Translate back
	new_point.x = new_delta.x + center.x;
	new_point.y = new_delta.y + center.y;

	return (new_point);
}

void	set_player_position_from_i_j(t_mlx_data *env_p, int i, int j)
{
	env_p->player_x = j * env_p->block_size +
					(env_p->block_size / 2) - MINI_PLAYER_CENTER_POINT;
	env_p->player_y = i * env_p->block_size +
					(env_p->block_size / 2) - MINI_PLAYER_CENTER_POINT;
	if (env_p->map[i][j] == 'E')
		env_p->player_direction = 0 * M_PI / 2;
	else if (env_p->map[i][j] == 'S')
		env_p->player_direction = 1 * M_PI / 2;
	else if (env_p->map[i][j] == 'W')
		env_p->player_direction = 2 * M_PI / 2;
	else if (env_p->map[i][j] == 'N')
		env_p->player_direction = 3 * M_PI / 2;

}


//the map has to be initialized before calling this function
//assumes there is only one player position character (N, E, S, W)
void	set_player_position(t_mlx_data *env_p)
{
	int	i;
	int	j;

	if (!env_p->map)
		destroy_everything_and_exit(env_p, 1);
	i = 0;
	while(env_p->map[i])
	{
		j = 0;
		while(env_p->map[i][j])
		{
			if (env_p->map[i][j] == 'N'
				|| env_p->map[i][j] == 'E'
				|| env_p->map[i][j] == 'S'
				|| env_p->map[i][j] == 'W')
				return (set_player_position_from_i_j(env_p, i, j));

			j++;
		}
		i++;
	}
	destroy_everything_and_exit(env_p, 1);
}


void	set_minilibx(t_mlx_data *env_p)
{

	env_p->mlx = mlx_init();
	env_p->block_size = BLOCK_SIZE;
	//env_p->map = malloc(15 * sizeof(char*));
	//env_p->map[0] = ft_strdup("111111111111111111111111111111111");
	//env_p->map[1] = ft_strdup("111111111000000000110000000000001");
	//env_p->map[2] = ft_strdup("111111111011000001110000000000001");
	//env_p->map[3] = ft_strdup("1111111110E1000000000000000000001");
	//env_p->map[4] = ft_strdup("111111111011000001110000000000001");
	//env_p->map[5] = ft_strdup("100000000011000001110111111111111");
	//env_p->map[6] = ft_strdup("111101111111110111000000100011111");
	//env_p->map[7] = ft_strdup("111101111111110111010100100011111");
	//env_p->map[8] = ft_strdup("110000001101010111000000100011111");
	//env_p->map[9] = ft_strdup("100000000000000011000000100011111");
	//env_p->map[10] = ft_strdup("100000000000000011010100100011111");
	//env_p->map[11] = ft_strdup("11000001110101011111011110N011111");
	//env_p->map[12] = ft_strdup("11110111 1110101 1011110100011111");
	//env_p->map[13] = ft_strdup("11111111 1111111 1111111111111111");
	//env_p->map[14] = NULL;
	//env_p->map_height = 14;
	//env_p->map_width = 33;
	env_p->map = malloc(9 * sizeof(char*));
	env_p->map[0] = ft_strdup("1111111111");
	env_p->map[1] = ft_strdup("1000100001");
	env_p->map[2] = ft_strdup("1000010101");
	env_p->map[3] = ft_strdup("1000010101");
	env_p->map[4] = ft_strdup("1011110101");
	env_p->map[5] = ft_strdup("1000N11101");
	env_p->map[6] = ft_strdup("1010000001");
	env_p->map[7] = ft_strdup("1111111111");
	env_p->map[8] = NULL;
	env_p->map_height = 8;
	env_p->map_width = 10;
	env_p->ceil_color = RED + BLUE;
	env_p->floor_color = RED + GREEN;

	set_player_position(env_p);
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
	load_sprite(env_p, &env_p->sprite_n_img, "./green.xpm");
	load_sprite(env_p, &env_p->sprite_e_img, "./red.xpm");
	load_sprite(env_p, &env_p->sprite_s_img, "./blue.xpm");
	load_sprite(env_p, &env_p->sprite_w_img, "./white.xpm");
	draw_obstacles(env_p);
	mlx_put_image_to_window(env_p->mlx, env_p->win, env_p->player_img.img,
		(int) env_p->player_x, (int) env_p->player_y);
	mlx_hook(env_p->win, DESTROY_NOTIFY, KEY_PRESS_MASK, close_window, env_p);
	mlx_hook(env_p->win, KEY_PRESS, KEY_PRESS_MASK, handle_key_press, env_p);
	mlx_hook(env_p->win, KEY_RELEASE, KEY_RELEASE_MASK, handle_key_release, env_p);
	mlx_loop_hook(env_p->mlx, update_game, env_p);
	mlx_loop(env_p->mlx);
}
