/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_coordinates.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 19:01:30 by ssin              #+#    #+#             */
/*   Updated: 2026/09/03 19:14:07 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

char	*fill_coordinates(t_id *id_p, char **tokens)
{
	if (ft_strlen(tokens[0]) == 2)
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
	}
	return (NULL);
}

void	check_coordinate(t_mlx_data *env_p, char **tokens)
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
	else if (tokens && ft_strlen(tokens[0]) == 1
			&& (ft_strncmp(tokens[0], ID_F, 1) == VALID
			|| ft_strncmp(tokens[0], ID_C, 1) == VALID))
	{
		check_fc_dup(env_p, tokens[0]);
		valid_ceiling_floor(env_p, tokens);
	}
	else if (!valid_char(tokens[0]) && !valid_map_content(*tokens))
		call_error(env_p, "Not a valid identifier");
}

void	check_dup(t_mlx_data *env_p, char *token)
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

char	**valid_id_content(t_mlx_data *env_p, char **tokens)
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