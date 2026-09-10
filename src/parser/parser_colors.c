/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 19:00:24 by ssin              #+#    #+#             */
/*   Updated: 2026/09/03 19:14:27 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

char	**filter_color(t_mlx_data *env_p, char **tokens)
{
	char	**colors;

	colors = NULL;
	if (tokens && tokens[1] && !tokens[2])
		colors = ft_split(tokens[1], ',');
	else if (tokens && tokens[1] && tokens[2] && tokens[3] && !tokens[4]
		&& tokens[1][ft_strlen(tokens[1]) - 1] == ','
		&& tokens[2][ft_strlen(tokens[2]) - 1] == ',')
	{
		colors = ft_calloc(4, sizeof(char *));
		if (colors)
		{
			colors[0] = ft_substr(tokens[1], 0, ft_strlen(tokens[1]) - 1);
			colors[1] = ft_substr(tokens[2], 0, ft_strlen(tokens[2]) - 1);
			colors[2] = ft_strdup(tokens[3]);
		}
	}
	if (!colors || !colors[0] || !colors[1] || !colors[2] || colors[3])
	{
		free(colors);
		perror("Invalid C / F content");
		destroy_everything_and_exit(env_p, 1);
	}
	return (colors);
}

void	fill_color(t_mlx_data *env_p, char **colors, char **tokens)
{
	if (colors && ft_strncmp(tokens[0], ID_F, 1) == VALID)
	{
		env_p->identifiers->F_R = ft_atoi(colors[0]);
		env_p->identifiers->F_G = ft_atoi(colors[1]);
		env_p->identifiers->F_B = ft_atoi(colors[2]);
	}
	else if (colors && ft_strncmp(tokens[0], ID_C, 1) == VALID)
	{
		env_p->identifiers->C_R = ft_atoi(colors[0]);
		env_p->identifiers->C_G = ft_atoi(colors[1]);
		env_p->identifiers->C_B = ft_atoi(colors[2]);
	}
	else
	{
		perror("Invalid C / F");
		destroy_everything_and_exit(env_p, 1);
	}
}

void	check_fc_dup(t_mlx_data *env_p, char *token)
{
	if (token && env_p->identifiers->F_R != -1
		&& ft_strncmp(ID_F, token, 2) == VALID)
	{
		perror("Duplicated F");
		destroy_everything_and_exit(env_p, 1);
	}
	if (token && env_p->identifiers->C_R != -1
		&& ft_strncmp(ID_C, token, 2) == VALID)
	{
		perror("Duplicated C");
		destroy_everything_and_exit(env_p, 1);
	}
}

void	valid_ceiling_floor(t_mlx_data *env_p, char **tokens)
{
	char	**colors;
	int		i;

	colors = valid_id_content(env_p, tokens);
	i = 0;
	while (colors[i])
	{
		if (ft_atoi(colors[i]) < 0 || ft_atoi(colors[i]) > 255)
		{
			perror("Invalid C / F content");
			destroy_everything_and_exit(env_p, 1);
		}
		i++;
	}
	fill_color(env_p, colors, tokens);
}
