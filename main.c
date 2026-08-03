/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 13:01:56 by anematol          #+#    #+#             */
/*   Updated: 2026/08/03 19:57:22 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int main(int ac, char **av)
{
	// add param validation
	if (ac > 1)
	{
		printf("%i\n", ac);
		printf("%s\n", av[1]);
	}

	set_minilibx();

	// parser
	// execution
	return (0);
}
