/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:58:58 by ssin              #+#    #+#             */
/*   Updated: 2026/09/03 16:49:34 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static char	**filter_color(t_mlx_data *env_p, char **tokens)
{
	char	**colors;

	colors = NULL;
	if (tokens && tokens[1] && !tokens[2])
		colors = ft_split(tokens[1], ',');
	else if (tokens && tokens[1] && tokens[2] && tokens[3] && !tokens[4]
		&& tokens[1][ft_strlen(tokens[1]) - 1] == ','
		&& tokens[2][ft_strlen(tokens[2]) - 1] == ',')
	{
		colors = ft_calloc(4, sizeof(char *));
		if (colors)
		{
			colors[0] = ft_substr(tokens[1], 0, ft_strlen(tokens[1]) - 1);
			colors[1] = ft_substr(tokens[2], 0, ft_strlen(tokens[2]) - 1);
			colors[2] = ft_strdup(tokens[3]);
		}
	}
	if (!colors || !colors[0] || !colors[1] || !colors[2] || colors[3])
	{
		free(colors);
		perror("Invalid C / F content");
		destroy_everything_and_exit(env_p, 1);
	}
	return (colors);
}

static char	**valid_id_content(t_mlx_data *env_p, char **tokens)
{
	char	**colors;
	int		i;
	int		j;

	colors = filter_color(env_p, tokens);
	i = 0;
	while (colors[i])
	{
		j = 0;
		while (colors[i][j] && ft_isdigit(colors[i][j]))
			j++;
		if (!j || (colors[i][j] && colors[i][j] != '\n'))
		{
			perror("Invalid C / F content");
			destroy_everything_and_exit(env_p, 1);
		}
		i++;
	}
	return (colors);
}

static void	fill_color(t_mlx_data *env_p, char **colors, char **tokens)
{
	if (colors && ft_strncmp(tokens[0], ID_F, 1) == VALID)
	{
		env_p->identifiers->F_R = ft_atoi(colors[0]);
		env_p->identifiers->F_G = ft_atoi(colors[1]);
		env_p->identifiers->F_B = ft_atoi(colors[2]);
	}
	else if (colors && ft_strncmp(tokens[0], ID_C, 1) == VALID)
	{
		env_p->identifiers->C_R = ft_atoi(colors[0]);
		env_p->identifiers->C_G = ft_atoi(colors[1]);
		env_p->identifiers->C_B = ft_atoi(colors[2]);
	}
	else
	{
		perror("Invalid C / F");
		destroy_everything_and_exit(env_p, 1);
	}
}

static void	valid_ceiling_floor(t_mlx_data *env_p, char **tokens)
{
	char	**colors;
	int		i;

	colors = valid_id_content(env_p, tokens);
	i = 0;
	while (colors[i])
	{
		if (ft_atoi(colors[i]) < 0 || ft_atoi(colors[i]) > 255)
		{
			perror("Invalid C / F content");
			destroy_everything_and_exit(env_p, 1);
		}
		i++;
	}
	fill_color(env_p, colors, tokens);
}

static void	check_dup(t_mlx_data *env_p, char *token)
{
	if (token && env_p->identifiers->NO && ft_strncmp(ID_NO, token, 2) == VALID)
	{
		perror("Duplicated NO");
		destroy_everything_and_exit(env_p, 1);
	}
	if (token && env_p->identifiers->SO && ft_strncmp(ID_SO, token, 2) == VALID)
	{
		perror("Duplicated SO");
		destroy_everything_and_exit(env_p, 1);
	}
	if (token && env_p->identifiers->WE && ft_strncmp(ID_WE, token, 2) == VALID)
	{
		perror("Duplicated WE");
		destroy_everything_and_exit(env_p, 1);
	}
	if (token && env_p->identifiers->EA && ft_strncmp(ID_EA, token, 2) == VALID)
	{
		perror("Duplicated EA");
		destroy_everything_and_exit(env_p, 1);
	}
}

static void	check_fc_dup(t_mlx_data *env_p, char *token)
{
	if (token && env_p->identifiers->F_R != -1
		&& ft_strncmp(ID_F, token, 2) == VALID)
	{
		perror("Duplicated F");
		destroy_everything_and_exit(env_p, 1);
	}
	if (token && env_p->identifiers->C_R != -1
		&& ft_strncmp(ID_C, token, 2) == VALID)
	{
		perror("Duplicated C");
		destroy_everything_and_exit(env_p, 1);
	}
}

static char	*fill_coordinates(t_id *id_p, char **tokens)
{
	if (ft_strncmp(tokens[0], ID_NO, 2) == VALID)
	{
		id_p->NO = ft_strtrim(tokens[1], " \t\n");
		return (id_p->NO);
	}
	else if (ft_strncmp(tokens[0], ID_SO, 2) == VALID)
	{
		id_p->SO = ft_strtrim(tokens[1], " \t\n");
		return (id_p->SO);
	}
	else if (ft_strncmp(tokens[0], ID_WE, 2) == VALID)
	{
		id_p->WE = ft_strtrim(tokens[1], " \t\n");
		return (id_p->WE);
	}
	else if (ft_strncmp(tokens[0], ID_EA, 2) == VALID)
	{
		id_p->EA = ft_strtrim(tokens[1], " \t\n");
		return (id_p->EA);
	}
	return (NULL);
}

static void	check_file_permissions(t_mlx_data *env_p, char **tokens)
{
	char	*path;

	if (!tokens[0] || !tokens[1] || tokens[2])
	{
		perror("Check identifiers");
		destroy_everything_and_exit(env_p, 1);
	}
	else
	{
		path = fill_coordinates(env_p->identifiers, tokens);
		if (path && access(path, F_OK | R_OK) == -1)
		{
			perror("Could not open sprite file");
			destroy_everything_and_exit(env_p, 1);
		}
	}
}

static void	check_coordinate(t_mlx_data *env_p, char **tokens)
{
	size_t	i;
	const char	*coordinates[] = {
		ID_NO,
		ID_SO,
		ID_EA,
		ID_WE
	};

	i = 0;
	while (i < COORD_LENGTH
		&& ft_strncmp(tokens[0], coordinates[i], 2) != VALID)
		i++;
	if (i < COORD_LENGTH)
	{
		check_dup(env_p, tokens[0]);
		check_file_permissions(env_p, tokens);
	}
	else if (tokens && (ft_strncmp(tokens[0], ID_F, 1) == VALID
			|| ft_strncmp(tokens[0], ID_C, 1) == VALID))
	{
		check_fc_dup(env_p, tokens[0]);
		valid_ceiling_floor(env_p, tokens);
	}
}

static	int	complete_ids(t_id *id_p)
{
	if (id_p)
		if (id_p->NO && id_p->SO && id_p->WE && id_p->EA
			&& id_p->F_R != -1 && id_p->C_R != -1
			&& id_p->F_G != -1 && id_p->C_G != -1
			&& id_p->F_B != -1 && id_p->C_B != -1)
			return (1);
	return (0);
}

/*static int	check_map(char *line)
{
	while (*line)
	{
		printf("%c", line[0]);
		line++;
	}
	return (0);
}
*/

static int valid_char(char *token)
{
	if (ft_strncmp(token, " ", 1) == VALID
		|| ft_strncmp(token, "\t", 1) == VALID
		|| ft_strncmp(token, "\n", 1) == VALID)
		return (1);
	return (0);
}

static int valid_map_content(char **tokens)
{
	if (ft_strncmp(tokens[0], "0", 1) == VALID
		|| ft_strncmp(tokens[0], "1", 1) == VALID)
		return (1);
	return (0);
}

static void	call_error(t_mlx_data *env_p, char *message)
{
	perror(message);
	destroy_everything_and_exit(env_p, 1);
}

static int	valid_file(int map_fd, t_mlx_data *env_p)
{
	char	*line;
	char	**tokens;

	line = get_next_line(map_fd);
	tokens = NULL;
	if (line == NULL)
		call_error(env_p, "Empty file");
	while (line)
	{
		tokens = ft_split(line, ' ');
		if (tokens[0])
		{
			if (!complete_ids(env_p->identifiers))
				check_coordinate(env_p, tokens);
			else if (complete_ids(env_p->identifiers) && (valid_char(tokens[0]) || valid_map_content(tokens)))
				printf("%s", line);
			else
				call_error(env_p, "Check identifiers");
		}
		line = get_next_line(map_fd);
	}
	return (0);
}

static int	valid_extension(t_mlx_data *env_p, char *map_name_p)
{
	char	*ext;

	if (!map_name_p || access(map_name_p, F_OK) == -1)
	{
		perror("Invalid file");
		destroy_everything_and_exit(env_p, 1);
	}
	ext = ft_strrchr(map_name_p, '.');
	if (!ext || (ft_strncmp(EXTENSION, ext, 5) != CUB))
	{
		perror("Invalid map extension");
		destroy_everything_and_exit(env_p, 1);
	}
	return (1);
}

void	parser(char *map_name_p, t_mlx_data *env_p)
{
	int		map_fd;

	map_fd = 0;
	if (valid_extension(env_p, map_name_p))
	{
		map_fd = open(map_name_p, O_RDONLY);
		if (map_fd == ERROR)
		{
			perror("Could not open file");
			destroy_everything_and_exit(env_p, 1);
		}
		valid_file(map_fd, env_p);
	}
	if (!complete_ids(env_p->identifiers))
	{
		perror("Missing identifiers");
		destroy_everything_and_exit(env_p, 1);
	}
}
