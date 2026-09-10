/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:58:58 by ssin              #+#    #+#             */
/*   Updated: 2026/09/03 19:53:27 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

static int	check_map(t_mlx_data *env_p, char *line, int i)
{
	if (ft_strncmp(line, "\n", 1) == VALID || ft_strncmp(line, "\0", 1) == VALID)
		return (0);
	size_t	size;

	size = ft_strlen(line) - 1;
	if (size > env_p->map_info->map_width)
		env_p->map_info->map_width = size;
	env_p->map_info->map = realloc(env_p->map_info->map, sizeof(char *) * (i + 1));
	if (!env_p->map_info->map)
		call_error(env_p, "Memory allocation failed");
	if (line[size] == '\n')
	{
		env_p->map_info->map[i] = ft_substr(line, 0, size);
		while (*line && valid_map_content(&*line))
			line++;
		if (*line != '\n' && *line != '\0')
			call_error(env_p, "Check map");
	}
	return (0);
}

static int	valid_file(int map_fd, t_mlx_data *env_p)
{
	char	*line;
	char	**tokens;
	int		i;

	line = get_next_line(map_fd);
	tokens = NULL;
	i = 0;
	if (line == NULL)
		call_error(env_p, "Empty file");
	while (line)
	{
		tokens = ft_split(line, ' ');
		if (tokens[0])
		{
			if (!complete_ids(env_p->identifiers))
				check_coordinate(env_p, tokens);
			else if (complete_ids(env_p->identifiers) && (valid_char(tokens[0]) || valid_map_content(*tokens)))
			{
				check_map(env_p, line, i);
				if (!valid_char(tokens[0]))
					i++;
			}
			else
				call_error(env_p, "Check file content");
		}
		line = get_next_line(map_fd);
	}
	env_p->map_info->map[i] = NULL;
	env_p->map_info->map_height = i;
	free(tokens);
	return (0);
}

static void	valid_map(t_mlx_data *env_p)
{
	int	i;

	i = 0;
	while (env_p->map_info->map[i])
	{
		printf("%s\n", env_p->map_info->map[i]);
		i++;
	}
	/*
	check first/last rows
	↓
	check first/last chars
	↓
	check internal walls
	↓
	check characters (0, 1, N, S, E, W, ...)
	*/
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
	int	map_fd;

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
		valid_map(env_p);
	}
	if (!complete_ids(env_p->identifiers))
	{
		perror("Missing identifiers");
		destroy_everything_and_exit(env_p, 1);
	}
}
