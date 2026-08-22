/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:58:58 by ssin              #+#    #+#             */
/*   Updated: 2026/08/22 12:54:50 by ssin             ###   ########.fr       */
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
	if (token && id_p->NO && ft_strncmp(ID_NO, token, 2) == VALID)
	{
		perror("Duplicated NO");
		exit(1); // call destroy_everything_and_exit()
	}
	if (token && id_p->SO && ft_strncmp(ID_SO, token, 2) == VALID)
	{
		perror("Duplicated SO");
		exit(1); // call destroy_everything_and_exit()
	}
	if (token && id_p->WE && ft_strncmp(ID_WE, token, 2) == VALID)
	{
		perror("Duplicated WE");
		exit(1); // call destroy_everything_and_exit()
	}
	if (token && id_p->EA && ft_strncmp(ID_EA, token, 2) == VALID)
	{
		perror("Duplicated EA");
		exit(1); // call destroy_everything_and_exit()
	}
}

static void	check_FC_dup(t_id *id_p, char *token)
{
	if (token && id_p->F_R != -1 && ft_strncmp(ID_F, token, 2) == VALID)
	{
		perror("Duplicated F");
		exit(1); // call destroy_everything_and_exit()
	}
	if (token && id_p->C_R != -1 && ft_strncmp(ID_C, token, 2) == VALID)
	{
		perror("Duplicated C");
		exit(1); // call destroy_everything_and_exit()
	}
}


static void	fill_coordinates(t_id *id_p, char **tokens)
{
	// the identifiers are filled with "\n"
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

static void	check_file_permissions(t_id *id_p, char **tokens)
{
	if (!tokens[0] || !tokens[1] || tokens[2])
	{
		perror("Check identifiers");
		exit(1); // call destroy_everything_and_exit()
	}
	// check if the file exists and has permission to read
	else
		fill_coordinates(id_p, tokens);
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
		ID_C,
		NULL,
		NULL
	};

	i = 0;
	while (i < COORD_LENGTH) {
		if (tokens && ft_strncmp(tokens[0], coordinates[i], 2) == VALID) {
			check_dup(id_p, tokens[0]);
			check_file_permissions(id_p, tokens);
			break ;
		}
		else if (tokens && color_key[i] && ft_strncmp(tokens[0], color_key[i], 1) == VALID) {
			check_FC_dup(id_p, tokens[0]);
			valid_ceiling_floor(id_p, tokens);
		}
		i++;
	}
}

static	int	complete_ids(t_id *id_p)
{
	if (id_p)
		if (id_p->NO && id_p->SO && id_p->WE && id_p->EA &&
			id_p->F_R != -1 && id_p->C_R != -1 &&
			id_p->F_G != -1 && id_p->C_G != -1 &&
			id_p->F_B != -1 && id_p->C_B != -1)
			return (1);
	return (0); // call destroy_everything_and_exit()
}

static int valid_char(char *token)
{
	if (ft_strncmp(token, " ", 1) == VALID ||
		ft_strncmp(token, "\t", 1) == VALID ||
		ft_strncmp(token, "\n", 1) == VALID)
		return (1);
	return (0);
}

static int valid_map_content(char **tokens)
{
	// while ()
	if (ft_strncmp(tokens[0], "0", 1) == VALID ||
		ft_strncmp(tokens[0], "1", 1) == VALID)
		return (1);
	return (0);
}

static int valid_id(char *token)
{
	if (ft_strncmp(token, ID_NO, 2) == VALID ||
		ft_strncmp(token, ID_SO, 2) == VALID ||
		ft_strncmp(token, ID_WE, 2) == VALID ||
		ft_strncmp(token, ID_EA, 2) == VALID ||
		ft_strncmp(token, ID_F, 1) == VALID ||
		ft_strncmp(token, ID_C, 1) == VALID)
		return (1);
	return (0);
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
		tokens = ft_split(line, ' ');
		if (tokens[0])
		{
			if (!complete_ids(id_p))
				check_coordinate(id_p, tokens);
			else if (complete_ids(id_p) && valid_id(tokens[0]))
			{
				perror("Duplicated identifiers");
				exit(1); // call destroy_everything_and_exit()
			}
			else if (complete_ids(id_p) && (valid_char(tokens[0]) || valid_map_content(tokens)))
				printf("%s", line);
			else
			{
				perror("Check identifiers");
				exit(1); // call destroy_everything_and_exit()
			}
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
		exit (1); // call destroy_everything_and_exit()
	}

	char	*ext = ft_strrchr(map_name_p, '.');
	if (!ext || (ft_strncmp(EXTENSION, ext, 5) != CUB))
	{
		perror("Invalid map extension");
		exit (1); // call destroy_everything_and_exit()
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
			perror("Could not open file");
			exit(1); // call destroy_everything_and_exit()
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
