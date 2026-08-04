/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 13:01:56 by anematol          #+#    #+#             */
/*   Updated: 2026/08/04 18:50:08 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int main(int ac, char **av)
{
	// add param validation
	if (ac == 1 || !av[1])
	{
		perror("Map is missing");
		exit(1);
	}

	parser(av[1]);
	set_minilibx();

	// parser

	// execution
	return (0);
}
