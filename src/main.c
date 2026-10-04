/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 13:01:56 by anematol          #+#    #+#             */
/*   Updated: 2026/10/03 12:34:56 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	main(int ac, char **av)
{
	t_mlx_data	env;

	if (ac == 1 || !av[1])
	{
		perror("Error\nMap is missing");
		exit(1);
	}
	init_env(&env);
	parser(av[1], &env);
	set_minilibx(&env);
	mlx_loop(env.mlx);
	return (0);
}
