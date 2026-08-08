/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 13:01:56 by anematol          #+#    #+#             */
/*   Updated: 2026/08/08 22:43:32 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_env(t_mlx_data *env_p)
{
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
	free(env_p->mlx);
	exit(exit_code);
}

int main(int ac, char **av)
{
	t_mlx_data	env;
	// add param validation
	printf("%i\n", ac);
	if (ac == 2)
		printf("%s\n", av[1]);

	init_env(&env);
	env.height = 800;
	env.width = 1080;
	set_minilibx(&env);

	// parser
	// execution
	return (0);
}
