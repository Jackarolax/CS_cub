/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 21:25:59 by anematol          #+#    #+#             */
/*   Updated: 2026/08/04 21:47:50 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	close_window(void *param)
{
	t_mlx_data	*env_p;

	env_p = (t_mlx_data *)param;
	destroy_everything_and_exit(env_p, 0);
	return (0);
}

int	handle_key_press(int keycode, void *param)
{
	t_mlx_data	*env_p;

	env_p = (t_mlx_data *)param;
	if (keycode == XK_Escape)
		close_window(param);
	return (0);
}
