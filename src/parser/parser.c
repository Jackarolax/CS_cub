/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:58:58 by ssin              #+#    #+#             */
/*   Updated: 2026/09/22 09:59:47 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

static void	validate_tokens(t_mlx_data *env_p, char **tokens,
			char *line, int *i)
{
	char	*exit_msg;

	env_p->identifiers->tokens = tokens;
	if (!complete_ids(env_p->identifiers))
	{
		exit_msg = check_identifiers(env_p, tokens);
		if (exit_msg)
			call_error(env_p, exit_msg);
	}
	else if (complete_ids(env_p->identifiers)
		&& env_p->map_info->map_started && tokens[0][0] == '\n')
		add_line_to_map(env_p, line, *i);
	else if (complete_ids(env_p->identifiers)
		&& !env_p->map_info->map_started && tokens[0][0] == '\n')
		return ;
	else if (complete_ids(env_p->identifiers) && valid_map_content(*tokens[0]))
	{
		if (env_p->map_info->map_started == 0)
			env_p->map_info->map_started = 1;
		add_line_to_map(env_p, line, *i);
		env_p->map_info->last_row = *i;
		*i = *i + 1;
	}
	else
		call_error(env_p, "Error\nCheck file content");
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
		call_error(env_p, "Error\nEmpty file");
	while (line)
	{
		tokens = ft_split(line, ' ');
		env_p->identifiers->line_start = line;
		line = NULL;
		if (tokens[0])
			validate_tokens(env_p, tokens,
				env_p->identifiers->line_start, &i);
		clean_memo(env_p, tokens);
		line = get_next_line(map_fd);
	}
	if (!env_p->map_info->map)
		call_error(env_p, "Error\nCheck file content");
	env_p->map_info->map[i] = NULL;
	env_p->map_info->map_height = i;
	return (0);
}

static int	valid_extension(t_mlx_data *env_p, char *map_name_p)
{
	char	*ext;

	if (!map_name_p || access(map_name_p, F_OK) == -1)
		call_error(env_p, "Error\nInvalid file");
	ext = ft_strrchr(map_name_p, '.');
	if (!ext || (ft_strncmp(EXTENSION, ext, 5) != CUB))
		call_error(env_p, "Error\nInvalid map extension");
	return (1);
}

void	parser(char *map_name_p, t_mlx_data *env_p)
{
	int	map_fd;

	map_fd = -1;
	if (valid_extension(env_p, map_name_p))
	{
		map_fd = open(map_name_p, O_RDONLY);
		if (map_fd == ERROR)
			call_error(env_p, "Error\nCould not open file");
		env_p->map_info->map_fd = map_fd;
		valid_file(map_fd, env_p);
		valid_map(env_p);
	}
	if (!complete_ids(env_p->identifiers))
		call_error(env_p, "Error\nMissing identifiers");
}
