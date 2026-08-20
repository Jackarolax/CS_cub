/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:58:58 by ssin              #+#    #+#             */
/*   Updated: 2026/08/06 17:42:21 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	valid_identifier(char *id, t_id *id_p)
{
	(void)id_p;
	// if there's a duplicate id (id already filled), should be an error
	// if there's more than 2 tokens for directions, should be an error
	if (ft_strncmp(id, ID_NO, 2) == VALID) // improve this validation
		printf("NO\n");
		// for each tokens = get_next_line(buf):
			// if (tokens == \n) continue
			// ft_split(tokens, " ")
				// tokens[0] == id
				// tokens[1] == content
			// valid_texture (check if path exists, check if there's permission)
			// save content id_p->NO = ft_strdup(tokens[1])
	// CHECK FILE IN DESKTOP
	if (ft_strncmp(id, ID_SO, 2) == VALID)
		printf("SO\n");
	if (ft_strncmp(id, ID_WE, 2) == VALID)
		printf("WE\n");
	if (ft_strncmp(id, ID_EA, 2) == VALID)
		printf("EA\n");
	if (ft_strncmp(id, ID_F, 1) == VALID)
		printf("F\n");
	if (ft_strncmp(id, ID_C, 1) == VALID)
		printf("C\n");

	// check if every id have valid content
	return (0);
}

static int	valid_extension(char *map_name_p)
{
	if (!map_name_p)
	{
		perror("Invalid map extension");
		// call destroy_everything_and_exit()
		exit (1); // remove
	}

	char	*ext = ft_strchr(map_name_p, '.');
	if (!ext || (ft_strncmp(EXTENSION, ext, 4) != CUB))
	{
		perror("Invalid map extension");
		// call destroy_everything_and_exit()
		exit (1); // remove
	}

	return (1);
}

static void	init_identifiers(t_id *identifiers_p)
{
	identifiers_p->NO = NULL;
	identifiers_p->SO = NULL;
	identifiers_p->WE = NULL;
	identifiers_p->EA = NULL;
	identifiers_p->F_R = 0;
	identifiers_p->F_G = 0;
	identifiers_p->F_B = 0;
	identifiers_p->C_R = 0;
	identifiers_p->C_G = 0;
	identifiers_p->C_B = 0;
}

void	parser(char *map_name_p)
{
	int		map_fd;
	char	buf[SIZE + 1];
	t_id	identifiers;

	init_identifiers(&identifiers);
	map_fd = 0;
	if (valid_extension(map_name_p))
	{
		map_fd = open(map_name_p, O_RDONLY);
		if (map_fd == ERROR)
		{
			// call destroy_everything_and_exit()
			perror("Could not open file");
			exit(1);
		}
		if (read(map_fd, buf, SIZE) > 0)
		{
			buf[SIZE] = '\0';
			// check if the file contains all the identifiers before starting the map
			valid_identifier("WE", &identifiers);
			// valid_map();
		}
		// else handle read error or empty file
	}
}
