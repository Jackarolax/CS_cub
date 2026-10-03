/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_coordinates.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 19:01:30 by ssin              #+#    #+#             */
/*   Updated: 2026/09/22 10:10:29 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

char	*fill_coordinates(t_id *id_p, char **tokens)
{
	if (ft_strlen(tokens[0]) == 2)
	{
		if (ft_strncmp(tokens[0], ID_NO, 2) == VALID)
		{
			id_p->no = ft_strtrim(tokens[1], " \t\n");
			return (id_p->no);
		}
		else if (ft_strncmp(tokens[0], ID_SO, 2) == VALID)
		{
			id_p->so = ft_strtrim(tokens[1], " \t\n");
			return (id_p->so);
		}
		else if (ft_strncmp(tokens[0], ID_WE, 2) == VALID)
		{
			id_p->we = ft_strtrim(tokens[1], " \t\n");
			return (id_p->we);
		}
		else if (ft_strncmp(tokens[0], ID_EA, 2) == VALID)
		{
			id_p->ea = ft_strtrim(tokens[1], " \t\n");
			return (id_p->ea);
		}
	}
	return (NULL);
}

static char	*duplicate_id(t_mlx_data *env_p, char *token, int size)
{
	if (token && env_p->identifiers->no
		&& ft_strncmp(ID_NO, token, size) == VALID)
		return ("Error\nDuplicated NO");
	if (token && env_p->identifiers->so
		&& ft_strncmp(ID_SO, token, size) == VALID)
		return ("Error\nDuplicated SO");
	if (token && env_p->identifiers->we
		&& ft_strncmp(ID_WE, token, size) == VALID)
		return ("Error\nDuplicated WE");
	if (token && env_p->identifiers->ea
		&& ft_strncmp(ID_EA, token, size) == VALID)
		return ("Error\nDuplicated EA");
	return (NULL);
}

char	*check_identifiers(t_mlx_data *env_p, char **tokens)
{
	size_t		i;
	char		*msg;

	i = 0;
	i = check_coordinate(tokens[0], &i);
	if (i < COORD_LENGTH)
	{
		msg = duplicate_id(env_p, tokens[0], 2);
		if (msg)
			return (msg);
		return (check_file_permissions(env_p, tokens));
	}
	else if (tokens && ft_strlen(tokens[0]) == 1
		&& (tokens[0][0] == ID_F || tokens[0][0] == ID_C))
	{
		check_fc_dup(env_p, tokens[0]);
		valid_ceiling_floor(env_p, tokens);
	}
	else if (!valid_space_nline(tokens[0][0]) && !valid_map_content(*tokens[0]))
		return ("Error\nNot a valid identifier");
	return (NULL);
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
			free_str_array(colors);
			call_error(env_p, "Error\nInvalid C / F content");
		}
		i++;
	}
	return (colors);
}
