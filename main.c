/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 13:01:56 by anematol          #+#    #+#             */
/*   Updated: 2026/08/04 21:51:48 by anematol         ###   ########.fr       */
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
}

void	destroy_everything_and_exit(t_mlx_data *env_p, int exit_code)
{
	if (env_p->test_img.img)
		mlx_destroy_image(env_p->mlx, env_p->test_img.img);
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
	printf("%s\n", av[1]);

	init_env(&env);
	env.height = 800;
	env.width = 1080;
	set_minilibx(&env);

	// parser
	// execution
	return (0);
}
