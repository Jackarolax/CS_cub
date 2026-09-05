/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 13:01:56 by anematol          #+#    #+#             */
/*   Updated: 2026/09/05 13:19:45 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	free_map(t_mlx_data *env_p)
{
	int	i;

	i = 0;
	while (env_p->map[i])
	{
		free(env_p->map[i]);
		i++;
	}
	free(env_p->map);
}

void	init_env(t_mlx_data *env_p)
{
	env_p->mlx = NULL;
	env_p->win = NULL;
	env_p->width = 0;
	env_p->height = 0;
	env_p->player_img.img = NULL;
	env_p->background_img.img = NULL;
	env_p->buffer_img.img = NULL;
	env_p->mv_fwd_pressed = 0;
	env_p->mv_bck_pressed = 0;
	env_p->mv_l_pressed = 0;
	env_p->mv_r_pressed = 0;
	env_p->look_l_pressed = 0;
	env_p->look_r_pressed = 0;
	env_p->player_x = 0.0;
	env_p->player_y = 0.0;
	env_p->player_direction = 0.0;
	env_p->map = NULL;
	env_p->map_height = 0;
	env_p->map_width = 0;
	env_p->block_size = 0;
}

void	destroy_everything_and_exit(t_mlx_data *env_p, int exit_code)
{
	if (env_p->player_img.img)
		mlx_destroy_image(env_p->mlx, env_p->player_img.img);
	if (env_p->background_img.img)
		mlx_destroy_image(env_p->mlx, env_p->background_img.img);
	if (env_p->buffer_img.img)
		mlx_destroy_image(env_p->mlx, env_p->buffer_img.img);
	if (env_p->win)
		mlx_destroy_window(env_p->mlx, env_p->win);
	if (env_p->mlx)
		mlx_destroy_display(env_p->mlx);
	if (env_p->map)
		free_map(env_p);

	free(env_p->mlx);
	exit(exit_code);
}

int main(int ac, char **av)
{
	t_mlx_data	env;
	// add param validation
	if (ac == 1 || !av[1])
	{
		perror("Map is missing");
		exit(1);
	}

	parser(av[1]);

	init_env(&env);
	env.height = 800;
	env.width = 1080;
	set_minilibx(&env);
	// parser

	// execution
	return (0);
}
