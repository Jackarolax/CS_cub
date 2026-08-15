/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:58:58 by ssin              #+#    #+#             */
/*   Updated: 2026/08/15 18:17:28 by ssin             ###   ########.fr       */
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

static void	check_dup(char *id, char *token)
{
	if (id)
	{
		if (ft_strncmp(token, ID_NO, 2) == VALID ||
			ft_strncmp(token, ID_SO, 2) == VALID ||
			ft_strncmp(token, ID_WE, 2) == VALID ||
			ft_strncmp(token, ID_EA, 2) == VALID ||
			ft_strncmp(token, ID_F, 1) == VALID ||
			ft_strncmp(token, ID_C, 1) == VALID)
		{
			perror("Duplicated identifier");
			exit(1); // call destroy_everything_and_exit()
		}
	}
}

static int	valid_identifier(int map_fd, t_id *id_p)
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
		tokens = ft_split(line, ' ');
		if (!id_p->NO && ft_strncmp(tokens[0], ID_NO, 2) == VALID)
		{
			check_dup(id_p->NO, tokens[0]);
			// check_file(); // check if it's a valid path, and if has permission to handle error and not save garbage
			id_p->NO = ft_strdup(tokens[1]);
		}
		else if (!id_p->SO && ft_strncmp(tokens[0], ID_SO, 2) == VALID)
		{
			check_dup(id_p->SO, tokens[0]);
			id_p->SO = ft_strdup(tokens[1]);
		}
		else if (!id_p->WE && ft_strncmp(tokens[0], ID_WE, 2) == VALID)
		{
			check_dup(id_p->WE, tokens[0]);
			id_p->WE = ft_strdup(tokens[1]);
		}
		else if (!id_p->EA && ft_strncmp(tokens[0], ID_EA, 2) == VALID)
		{
			check_dup(id_p->EA, tokens[0]);
			id_p->EA = ft_strdup(tokens[1]);
		}
		else if (id_p->C_R && ft_strncmp(tokens[0], ID_C, 1) == VALID)
		{
			perror("Duplicated identifier");
			exit(1);
		}
		else if ((!id_p->F_R && ft_strncmp(tokens[0], ID_F, 1) == VALID) ||
			(!id_p->C_R && ft_strncmp(tokens[0], ID_C, 1) == VALID))
			valid_ceiling_floor(id_p, tokens);
		else if ((ft_strncmp(tokens[0], "0", 1) == VALID) ||
				(ft_strncmp(tokens[0], "1", 1) == VALID))
			printf("map\n");
		else if ((ft_strncmp(tokens[0], "\n", 1) == VALID) ||
				(tokens[0][0] == 32))
			printf("new line / space\n");
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
		valid_identifier(map_fd, &identifiers);
		// valid_map();
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
