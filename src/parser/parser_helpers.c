/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 19:05:49 by ssin              #+#    #+#             */
/*   Updated: 2026/09/03 19:13:29 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	check_file_permissions(t_mlx_data *env_p, char **tokens)
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
		if (!path)
		{
			perror("Not a valid identifier");
			destroy_everything_and_exit(env_p, 1);
		}
		if (path && access(path, F_OK | R_OK) == -1)
		{
			perror("Could not open sprite file");
			destroy_everything_and_exit(env_p, 1);
		}
	}
}

int	complete_ids(t_id *id_p)
{
	if (id_p)
		if (id_p->NO && id_p->SO && id_p->WE && id_p->EA
			&& id_p->F_R != -1 && id_p->C_R != -1
			&& id_p->F_G != -1 && id_p->C_G != -1
			&& id_p->F_B != -1 && id_p->C_B != -1)
			return (1);
	return (0);
}

int valid_char(char *token)
{
	if (ft_strncmp(token, " ", 1) == VALID
		|| ft_strncmp(token, "\t", 1) == VALID
		|| ft_strncmp(token, "\n", 1) == VALID)
		return (1);
	return (0);
}

void	call_error(t_mlx_data *env_p, char *message)
{
	perror(message);
	destroy_everything_and_exit(env_p, 1);
}
