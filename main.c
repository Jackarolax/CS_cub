/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 13:01:56 by anematol          #+#    #+#             */
/*   Updated: 2026/08/25 20:42:51 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	init_identifiers(t_id *identifiers_p)
{
	identifiers_p->SO = NULL;
	identifiers_p->WE = NULL;
	identifiers_p->NO = NULL;
	identifiers_p->EA = NULL;
	identifiers_p->F_R = -1;
	identifiers_p->F_G = -1;
	identifiers_p->F_B = -1;
	identifiers_p->C_R = -1;
	identifiers_p->C_G = -1;
	identifiers_p->C_B = -1;
}

void	init_env(t_mlx_data *env_p)
{
	env_p->identifiers = ft_calloc(1, sizeof(t_id));
	if (!env_p->identifiers)
		exit(1);
	init_identifiers(env_p->identifiers);
	env_p->mlx = NULL;
	env_p->win = NULL;
	env_p->width = 0;
	env_p->height = 0;
	env_p->test_img.img = NULL;
	env_p->background_img.img = NULL;
	env_p->mv_fwd_pressed = 0;
	env_p->mv_bck_pressed = 0;
	env_p->mv_l_pressed = 0;
	env_p->mv_r_pressed = 0;
	env_p->look_l_pressed = 0;
	env_p->look_r_pressed = 0;
	env_p->player_x = 0.0;
	env_p->player_y = 0.0;
	env_p->moving_speed = 0.0;
	env_p->player_diretion = 0.0;
	env_p->turning_speed = 0.0;
}

void	destroy_everything_and_exit(t_mlx_data *env_p, int exit_code)
{
	if (env_p->test_img.img)
		mlx_destroy_image(env_p->mlx, env_p->test_img.img);
	if (env_p->background_img.img)
		mlx_destroy_image(env_p->mlx, env_p->background_img.img);
	if (env_p->win)
		mlx_destroy_window(env_p->mlx, env_p->win);
	if (env_p->mlx)
		mlx_destroy_display(env_p->mlx);
	free(env_p->identifiers);
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


	init_env(&env);
	parser(av[1], &env);
	env.height = 800;
	env.width = 1080;
	set_minilibx(&env);
	// parser

	// execution
	return (0);
}
