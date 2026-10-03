/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_memo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 18:16:19 by ssin              #+#    #+#             */
/*   Updated: 2026/09/29 18:16:20 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	clean_memo(t_mlx_data *env_p, char **tokens)
{
	free_str_array(tokens);
	tokens = NULL;
	env_p->identifiers->tokens = NULL;
	free(env_p->identifiers->line_start);
	env_p->identifiers->line_start = NULL;
}

void	free_str_array(char **str)
{
	char	**str_start;

	str_start = str;
	if (str)
	{
		while (*str)
		{
			free(*str);
			str++;
		}
		free(str_start);
	}
}
