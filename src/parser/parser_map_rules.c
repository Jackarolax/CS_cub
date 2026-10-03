/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map_rules.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 18:23:43 by ssin              #+#    #+#             */
/*   Updated: 2026/09/29 18:23:57 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

static void	cell_is_close_to_edge(t_mlx_data *env_p, int i, int j)
{
	if (env_p->map_info->map[i][j + 1] == ' '
		|| (j > 0 && env_p->map_info->map[i][j - 1] == ' ')
		|| (j == 0 && env_p->map_info->map[i][j] == '0')
		|| env_p->map_info->map[i + 1][j] == ' '
		|| (i > 0 && env_p->map_info->map[i - 1][j] == ' ')
		|| env_p->map_info->map[i][j + 1] == '\0'
		|| (j > 0 && env_p->map_info->map[i][j - 1] == '\0')
		|| (j == 0 && env_p->map_info->map[i][j] == '0')
		|| env_p->map_info->map[i + 1][j] == '\0'
		|| (i > 0 && env_p->map_info->map[i - 1][j] == '\0'))
		call_error(env_p, "Error\nCheck map edge");
}

double	check_walkable_cels(t_mlx_data *env_p, double i)
{
	double	j;

	j = 0.0;
	while (env_p->map_info->map[(int)i][(int)j])
	{
		if (i > env_p->map_info->map_height || j > env_p->map_info->map_width)
			return (1);
		if (env_p->map_info->map[(int)i][(int)j] == '0'
			|| is_player_id(env_p->map_info->map[(int)i][(int)j]))
			cell_is_close_to_edge(env_p, i, j);
		j += 1.0;
	}
	return (0);
}

static void	replace_map_spaces_beg(t_map_info *map_info_p, int i, int *j)
{
	while (map_info_p->map[i][*j] && map_info_p->map[i][*j] == ' ')
	{
		map_info_p->map[i][*j] = '1';
		(*j)++;
	}
}

static void	replace_map_spaces_end(t_map_info *map_info_p, int i, int *line_len)
{
	while (*line_len < map_info_p->map_width)
	{
		map_info_p->map[i][*line_len] = '1';
		(*line_len)++;
	}
}

void	standardize_map(t_mlx_data *env_p)
{
	int	i;
	int	j;
	int	line_len;

	i = 0;
	while (env_p->map_info->map[i])
	{
		j = 0;
		replace_map_spaces_beg(env_p->map_info, i, &j);
		line_len = ft_strlen(env_p->map_info->map[i]);
		if (line_len < env_p->map_info->map_width)
		{
			env_p->map_info->map[i] = realloc(
					env_p->map_info->map[i],
					sizeof(char) * (env_p->map_info->map_width + 1));
			replace_map_spaces_end(env_p->map_info, i, &line_len);
			env_p->map_info->map[i][line_len] = '\0';
		}
		i++;
	}
}
