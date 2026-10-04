/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 11:50:23 by ssin              #+#    #+#             */
/*   Updated: 2026/10/04 11:50:27 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

static void	init_map_info(t_map_info *info)
{
	info->map_fd = -1;
	info->map = NULL;
	info->map_started = 0;
	info->map_height = 0;
	info->map_width = 0;
	info->player_x = 0.0;
	info->player_y = 0.0;
	info->last_row = 0;
}

static void	init_identifiers(t_id *identifiers_p)
{
	identifiers_p->line_start = NULL;
	identifiers_p->tokens = NULL;
	identifiers_p->so = NULL;
	identifiers_p->we = NULL;
	identifiers_p->no = NULL;
	identifiers_p->ea = NULL;
	identifiers_p->f_r = -1;
	identifiers_p->f_g = -1;
	identifiers_p->f_b = -1;
	identifiers_p->c_r = -1;
	identifiers_p->c_g = -1;
	identifiers_p->c_b = -1;
}

static void	init_img(t_mlx_data *env_p)
{
	env_p->player_img.img = NULL;
	env_p->player_img.img = NULL;
	env_p->background_img.img = NULL;
	env_p->sprite_n_img.img = NULL;
	env_p->sprite_e_img.img = NULL;
	env_p->sprite_s_img.img = NULL;
	env_p->sprite_w_img.img = NULL;
}

void	init_env(t_mlx_data *env_p)
{
	ft_bzero(env_p, sizeof(t_mlx_data));
	env_p->identifiers = ft_calloc(1, sizeof(t_id));
	if (!env_p->identifiers)
		exit(1);
	env_p->map_info = ft_calloc(1, sizeof(t_map_info));
	if (!env_p->map_info)
		return (free(env_p->identifiers), exit(1));
	init_identifiers(env_p->identifiers);
	init_map_info(env_p->map_info);
	init_img(env_p);
}
