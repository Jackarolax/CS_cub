/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:58:58 by ssin              #+#    #+#             */
/*   Updated: 2026/09/10 17:40:46 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

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
			else if (complete_ids(env_p->identifiers) && (valid_char(tokens[0]) || valid_map_content(*tokens)))
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
