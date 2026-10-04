/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_everything.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 11:50:14 by ssin              #+#    #+#             */
/*   Updated: 2026/10/04 11:50:37 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

static void	destroy_img(t_mlx_data *env_p)
{
	if (env_p->player_img.img)
		mlx_destroy_image(env_p->mlx, env_p->player_img.img);
	if (env_p->background_img.img)
		mlx_destroy_image(env_p->mlx, env_p->background_img.img);
	if (env_p->background_buffer_img.img)
		mlx_destroy_image(env_p->mlx, env_p->background_buffer_img.img);
	if (env_p->sprite_n_img.img)
		mlx_destroy_image(env_p->mlx, env_p->sprite_n_img.img);
	if (env_p->sprite_e_img.img)
		mlx_destroy_image(env_p->mlx, env_p->sprite_e_img.img);
	if (env_p->sprite_w_img.img)
		mlx_destroy_image(env_p->mlx, env_p->sprite_w_img.img);
	if (env_p->sprite_s_img.img)
		mlx_destroy_image(env_p->mlx, env_p->sprite_s_img.img);
}

static void	destroy_ids(char *string)
{
	if (string)
	{
		free(string);
		string = NULL;
	}
}

static void	destroy_tokens(t_mlx_data *env_p)
{
	if (env_p->identifiers->tokens)
	{
		free_str_array(env_p->identifiers->tokens);
		env_p->identifiers->tokens = NULL;
	}
	if (env_p->identifiers)
	{
		free(env_p->identifiers);
		env_p->identifiers = NULL;
	}
}

void	destroy_everything_and_exit(t_mlx_data *env_p, int exit_code)
{
	destroy_img(env_p);
	if (env_p->win)
		mlx_destroy_window(env_p->mlx, env_p->win);
	if (env_p->mlx)
		mlx_destroy_display(env_p->mlx);
	destroy_ids(env_p->identifiers->line_start);
	destroy_ids(env_p->identifiers->no);
	destroy_ids(env_p->identifiers->so);
	destroy_ids(env_p->identifiers->we);
	destroy_ids(env_p->identifiers->ea);
	destroy_tokens(env_p);
	if (env_p->map_info)
	{
		free_str_array(env_p->map_info->map);
		env_p->map_info->map = NULL;
		free(env_p->map_info);
		env_p->map_info = NULL;
	}
	if (env_p->mlx)
		free(env_p->mlx);
	exit(exit_code);
}
