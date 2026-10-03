/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 19:05:49 by ssin              #+#    #+#             */
/*   Updated: 2026/09/22 09:56:29 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

char	*check_file_permissions(t_mlx_data *env_p, char **tokens)
{
	char	*path;

	if (!tokens[0] || !tokens[1] || tokens[2])
		return ("Error\nCheck identifiers");
	else
	{
		path = fill_coordinates(env_p->identifiers, tokens);
		if (!path)
			return ("Error\nNot a valid identifier");
		if (path && access(path, F_OK | R_OK) == -1)
			return ("Error\nCould not open sprite file");
	}
	return (NULL);
}

int	check_coordinate(char *tokens, size_t *i)
{
	const char	*coordinates[] = {
		ID_NO,
		ID_SO,
		ID_EA,
		ID_WE
	};

	while (*i < COORD_LENGTH
		&& ft_strncmp(tokens, coordinates[*i], 2) != VALID)
		(*i)++;
	return (*i);
}

int	complete_ids(t_id *id_p)
{
	if (id_p)
		if (id_p->no && id_p->so && id_p->we && id_p->ea
			&& id_p->f_r != -1 && id_p->c_r != -1
			&& id_p->f_g != -1 && id_p->c_g != -1
			&& id_p->f_b != -1 && id_p->c_b != -1)
			return (1);
	return (0);
}

int	valid_space_nline(char character)
{
	if (character == ' '
		|| character == '\n'
		|| character == '\t')
		return (1);
	return (0);
}

void	call_error(t_mlx_data *env_p, char *message)
{
	if (env_p->map_info->map_fd >= 0)
	{
		close(env_p->map_info->map_fd);
		env_p->map_info->map_fd = -1;
	}
	perror(message);
	destroy_everything_and_exit(env_p, EXIT_FAILURE);
}
