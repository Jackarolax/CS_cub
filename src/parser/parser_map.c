/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 19:05:01 by ssin              #+#    #+#             */
/*   Updated: 2026/09/22 09:32:07 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

static char	**get_buffer(t_mlx_data *env_p, char *line, int *size, int i)
{
	char	**tmp;

	if (ft_strlen(line) > 0)
		*size = ft_strlen(line) - 1;
	if (*size > env_p->map_info->map_width)
		env_p->map_info->map_width = *size;
	tmp = realloc(env_p->map_info->map, sizeof(char *) * (i + 2));
	if (!tmp)
		call_error(env_p, "Error\nMemory allocation failed");
	return (tmp);
}

int	add_line_to_map(t_mlx_data *env_p, char *line, int i)
{
	int		size;
	int		j;

	j = 0;
	size = 0;
	env_p->map_info->map = get_buffer(env_p, line, &size, i);
	if (line[0] == '\n' || line[0] == '\0')
	{
		env_p->map_info->map[i] = NULL;
		call_error(env_p, "Error\nInvalid map");
	}
	env_p->map_info->map[i] = ft_substr(line, 0, size);
	env_p->map_info->map[i + 1] = NULL;
	while (line[j])
	{
		if (!valid_space_nline(line[j]) && !valid_map_content(line[j]))
			call_error(env_p, "Error\nCheck map");
		if (is_player_id(line[j]))
			add_player_pos(env_p, i, j);
		j++;
	}
	return (0);
}

static int	valid_first_last_rows(char *row)
{
	int	i;

	i = 0;
	while (row && row[i])
	{
		if (row[i] == '1' || row[i] == '	' || row[i] == ' ')
			i++;
		else
			return (1);
	}
	return (0);
}

int	valid_map_content(char letter)
{
	if (letter == '0' || letter == '1' || is_player_id(letter))
		return (1);
	return (0);
}

void	valid_map(t_mlx_data *env_p)
{
	int	i;

	i = 0;
	if (valid_first_last_rows(env_p->map_info->map[0])
		|| valid_first_last_rows(
			env_p->map_info->map[env_p->map_info->last_row]))
		call_error(env_p, "Error\nCheck map's first/last rows");
	while (env_p->map_info->map[i] && i < env_p->map_info->last_row)
	{
		check_walkable_cels(env_p, i);
		i++;
	}
	if (!player_exists(env_p))
		call_error(env_p, "Error\nSet player position");
	standardize_map(env_p);
}
