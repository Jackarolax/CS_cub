/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:58:58 by ssin              #+#    #+#             */
/*   Updated: 2026/09/17 18:17:11 by ssin             ###   ########.fr       */
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
	env_p->map_info->map = realloc(env_p->map_info->map, sizeof(char *) * (size + 2));
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
			else if (complete_ids(env_p->identifiers) && (valid_space_nline(tokens[0]) || valid_map_content(*tokens)))
			{
				check_map(env_p, line, i);
				env_p->map_info->last_row = i;
				if (!valid_space_nline(tokens[0]))
					i++;
			}
			else
				call_error(env_p, "Check file content");
		}
		free_str_array(tokens);
		free(line);
		line = get_next_line(map_fd);
	}
	if (!env_p->map_info->map)
		call_error(env_p, "Check file content");
	env_p->map_info->map[i] = NULL;
	env_p->map_info->map_height = i;
	return (0);
}

static void	cell_is_close_to_edge(t_mlx_data *env_p, size_t i, size_t j)
{
	if (ft_strncmp(&env_p->map_info->map[i][j + 1], " ", 1) == VALID
		|| (j > 0 && ft_strncmp(&env_p->map_info->map[i][j - 1], " ", 1) == VALID)
		|| ft_strncmp(&env_p->map_info->map[i + 1][j], " ", 1) == VALID
		|| (i > 0 && ft_strncmp(&env_p->map_info->map[i - 1][j], " ", 1) == VALID)
		|| ft_strncmp(&env_p->map_info->map[i][j + 1], "\0", 1) == VALID
		|| (j > 0 && ft_strncmp(&env_p->map_info->map[i][j - 1], "\0", 1) == VALID)
		|| ft_strncmp(&env_p->map_info->map[i + 1][j], "\0", 1) == VALID
		|| (i > 0 && ft_strncmp(&env_p->map_info->map[i - 1][j], "\0", 1) == VALID))
		call_error(env_p, "Check map edge");
}

int	valid_player_id(char *string)
{
	if (ft_strncmp(string, "N", 1) == VALID
		|| ft_strncmp(string, "S", 1) == VALID
		|| ft_strncmp(string, "E", 1) == VALID
		|| ft_strncmp(string, "W", 1) == VALID)
		return (1);
	return (0);
}

static int	player_exists(t_mlx_data *env_p)
{
	if (env_p->player_x && env_p->player_y)
		return (1);
	return (0);
}

static int	check_walkable_cels(t_mlx_data *env_p, size_t i)
{
	size_t	j;

	j = 0;
	while (env_p->map_info->map[i][j])
	{
		if (i > env_p->map_info->map_height || j > env_p->map_info->map_width)
			return (1);
		if (ft_strncmp(&env_p->map_info->map[i][j], "0", 1) == VALID
			|| valid_player_id(&env_p->map_info->map[i][j]))
		{
			if (valid_player_id(&env_p->map_info->map[i][j]))
			{
				if (player_exists(env_p))
					call_error(env_p, "More than 1 player position");
				env_p->player_x = i;
				env_p->player_y = j;
			}
			cell_is_close_to_edge(env_p, i, j);
		}
		j++;
	}
	return (0);
}

static void	standardize_map(t_mlx_data *env_p)
{
	size_t	i;
	size_t	j;
	size_t	line_len;

	i = 0;
	while (env_p->map_info->map[i])
	{
		j = 0;
		// replace spaces with 1's at the beginning of the line
		while (env_p->map_info->map[i][j] && ft_strncmp(&env_p->map_info->map[i][j], " ", 1) == VALID)
		{
			env_p->map_info->map[i][j] = '1';
			j++;
		}
		line_len = ft_strlen(env_p->map_info->map[i]);
		if (line_len < env_p->map_info->map_width)
		{
			env_p->map_info->map[i] = realloc(env_p->map_info->map[i], sizeof(char) * (env_p->map_info->map_width + 1));
			// replace the spaces with 1's at the end of the line
			while (line_len < env_p->map_info->map_width)
			{
				env_p->map_info->map[i][line_len] = '1';
				line_len++;
			}
			env_p->map_info->map[i][line_len] = '\0';
		}
		i++;
	}
	// just to print and check, remove later
	i = 0;
	while (env_p->map_info->map[i] && i < env_p->map_info->last_row)
	{
		printf("%s\n", env_p->map_info->map[i]);
		i++;
	}
}

static void	valid_map(t_mlx_data *env_p)
{
	size_t	i;

	i = 0;
	if (valid_first_last_rows(env_p->map_info->map[0])
		|| valid_first_last_rows(env_p->map_info->map[env_p->map_info->last_row]))
		call_error(env_p, "Check map's first/last rows");
	while (env_p->map_info->map[i] && i < env_p->map_info->last_row)
	{
		check_walkable_cels(env_p, i);
		i++;
	}
	if (!player_exists(env_p))
		call_error(env_p, "Set player position");

	standardize_map(env_p);
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
