/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:58:58 by ssin              #+#    #+#             */
/*   Updated: 2026/08/19 17:17:16 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static char	**valid_id_content(char **tokens)
{
	int	i;
	// content has 3 parts?
	if (tokens[1])
		tokens = ft_split(tokens[1], ',');
	if ((!tokens[0] || ft_strncmp(tokens[0], "\n", 2) == VALID || ft_strncmp(tokens[0], "\0", 2) == VALID) ||
		(!tokens[1] || ft_strncmp(tokens[1], "\n", 2) == VALID || ft_strncmp(tokens[1], "\0", 2) == VALID) ||
		(!tokens[2] || ft_strncmp(tokens[2], "\n", 2) == VALID || ft_strncmp(tokens[2], "\0", 2) == VALID) ||
		tokens[3])
	{
		perror("Invalid C / F content");
		exit(1); // call destroy_everything_and_exit()
	}

	i = 0;
	while (tokens[i])
	{
		int	f = 0;
		while (tokens[i][f] && ft_isdigit(tokens[i][f]))
		{
			if (ft_isdigit(tokens[i][f]))
			{
				f++;
				continue ;
			}
			else
				exit(2);
		}
		if (tokens[i][f] && tokens[i][f] != '\n' && !ft_isdigit(tokens[i][f]))
		{
			perror("Invalid C / F content");
			exit(5);// call destroy_everything_and_exit() 
		}
		i++;
	}
	return (tokens);
}

static void	valid_ceiling_floor(t_id *id_p, char **tokens)
{
	char	**x;
	int		i;

	x = valid_id_content(tokens);
	i = 0;
	while (x[i])
	{
		if (ft_atoi(x[i]) < 0 || ft_atoi(x[i]) > 255)
		{
			perror("Invalid C / F content");
			exit(1); // call destroy_everything_and_exit()
		}
		i++;
	}
	if (x && ft_strncmp(tokens[0], ID_F, 1) == VALID)
	{	
		id_p->F_R = ft_atoi(x[0]);
		id_p->F_G = ft_atoi(x[1]);
		id_p->F_B = ft_atoi(x[2]);
	}
	else if (x && ft_strncmp(tokens[0], ID_C, 1) == VALID)
	{
		id_p->C_R = ft_atoi(x[0]);
		id_p->C_G = ft_atoi(x[1]);
		id_p->C_B = ft_atoi(x[2]);
	}
	else
	{
		perror("Invalid C / F");
		exit(1); // call destroy_everything_and_exit()
	}
}

static void	check_dup(t_id *id_p, char *token)
{
	if (token)
	{
		if (id_p->NO != NULL &&
			id_p->SO != NULL &&
			id_p->WE != NULL &&
			id_p->EA != NULL)
		{
			perror("Duplicated identifier");
			exit(1); // call destroy_everything_and_exit()
		}
	}
}

static void	fill_coordinates(t_id *id_p, char **tokens)
{
	// os identifiers estão sendo preenchidos com "\n"
	// make a clean before saving inside id_p->[coord]
	if (ft_strncmp(tokens[0], ID_NO, 2) == VALID)
		id_p->NO = ft_strdup(tokens[1]);
	else if (ft_strncmp(tokens[0], ID_SO, 2) == VALID)
		id_p->SO = ft_strdup(tokens[1]);
	else if (ft_strncmp(tokens[0], ID_WE, 2) == VALID)
		id_p->WE = ft_strdup(tokens[1]);
	else if (ft_strncmp(tokens[0], ID_EA, 2) == VALID)
		id_p->EA = ft_strdup(tokens[1]);
}

static void	check_coordinate(t_id *id_p, char **tokens)
{
	size_t i;
	const char *coordinates[] = {
		ID_NO,
		ID_SO,
		ID_EA,
		ID_WE
	};
	const char *color_key[] = {
		ID_F,
		ID_C
	};

	i = 0;
	while (i < COORD_LENGTH) {
		if (tokens && ft_strncmp(tokens[0], coordinates[i], 2) == VALID) {
			check_dup(id_p, tokens[0]);
			// check_file(); // check if it's a valid path, and if has permission to handle error and not save garbage
			fill_coordinates(id_p, tokens);
			break ;
		}
		if (tokens && ft_strncmp(tokens[0], color_key[i], 1) == VALID)
			valid_ceiling_floor(id_p, tokens);
		i++;
	}
}

static	int	ids_are_complete(t_id *id_p)
{
	if (id_p)
		if (id_p->NO && id_p->SO && id_p->WE && id_p->EA && id_p->F_R != -1 && id_p->C_R != -1)
			return (1);
	return (0); // call destroy_everything_and_exit()
}

static void	valid_map(t_id *id_p, char *line, char **tokens)
{
	(void)id_p;
	(void)line;
	printf("validating... %s\n", *tokens);
}

static int	valid_file(int map_fd, t_id *id_p)
{
	char	*line;
	char	**tokens;

	line = get_next_line(map_fd);
	tokens = NULL;
	if (line == NULL)
	{
		perror("Empty file");
		exit(1); // call destroy_everything_and_exit()
	}
	while (line)
	{
		tokens = ft_split(line, ' '); // considerar vários espaços entre identificador e valor (ft_trim combinado com is_space)
		if (!id_p->NO || !id_p->SO || !id_p->WE || !id_p->EA ||
			id_p->F_R  == -1 || id_p->C_R  == -1)
			check_coordinate(id_p, tokens);
		// improve this else if
		else if (((id_p->F_R  != -1) && ft_strncmp(tokens[0], ID_F, 1) == VALID) ||
			((id_p->C_R  != -1) && ft_strncmp(tokens[0], ID_C, 1) == VALID))
		{
			perror("Duplicated identifier");
			exit(1);
		}
		else if ((ft_strncmp(tokens[0], ID_NO, 2) && ft_strncmp(tokens[0], ID_SO, 2) && ft_strncmp(tokens[0], ID_WE, 2) && ft_strncmp(tokens[0], ID_EA, 2) && ft_strncmp(tokens[0], ID_F, 1) && ft_strncmp(tokens[0], ID_C, 1)) &&
			ids_are_complete(id_p))
			valid_map(id_p, line, tokens);
		/*else if ((ft_strncmp(tokens[0], "0", 1) == VALID) ||
				(ft_strncmp(tokens[0], "1", 1) == VALID))*/
		else if ((ft_strncmp(tokens[0], "\n", 1) == VALID) ||
				(tokens[0][0] == 32) ||
			(ft_strncmp(tokens[0], "0", 1) == VALID) ||
			(ft_strncmp(tokens[0], "1", 1) == VALID))
			printf("new line / space / map\n");
		else
		{
			perror("Not valid identifier");
			exit(1); // call destroy_everything_and_exit()
		}
		line = get_next_line(map_fd);
	}
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
	identifiers_p->F_R = -1;
	identifiers_p->F_G = -1;
	identifiers_p->F_B = -1;
	identifiers_p->C_R = -1;
	identifiers_p->C_G = -1;
	identifiers_p->C_B = -1;
}

void	parser(char *map_name_p)
{
	int		map_fd;
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
		// check if the file contains all the identifiers before starting the map
		valid_file(map_fd, &identifiers);
	}

	// check if identifiers are not NULL or -1
	printf("%s\n", identifiers.NO);
	printf("%s\n", identifiers.SO);
	printf("%s\n", identifiers.WE);
	printf("%s\n", identifiers.EA);
	printf("%d\n", identifiers.F_R);
	printf("%d\n", identifiers.F_G);
	printf("%d\n", identifiers.F_B);
	printf("%d\n", identifiers.C_R);
	printf("%d\n", identifiers.C_G);
	printf("%d\n", identifiers.C_B);
}
