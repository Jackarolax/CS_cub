/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 18:20:30 by ssin              #+#    #+#             */
/*   Updated: 2026/08/08 22:27:00 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// add sprites function

void	pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}



void	set_minilibx(t_mlx_data *env_p)
{

	env_p->mlx = mlx_init();
	env_p->win = mlx_new_window(env_p->mlx, env_p->width,
		env_p->height, "CUB 3D");
	env_p->test_img.width = 50;
	env_p->test_img.height = 50;
	env_p->test_img.img = mlx_new_image(env_p->mlx, env_p->test_img.width,
		env_p->test_img.height);
	env_p->test_img.addr = mlx_get_data_addr(env_p->test_img.img,
		&env_p->test_img.bpp, &env_p->test_img.line_length,
		&env_p->test_img.endian);
	env_p->background_img.width = env_p->width;
	env_p->background_img.height = env_p->height;
	env_p->background_img.img = mlx_new_image(env_p->mlx, env_p->background_img.width,
		env_p->background_img.height);
	env_p->background_img.addr = mlx_get_data_addr(env_p->background_img.img,
		&env_p->background_img.bpp, &env_p->background_img.line_length,
		&env_p->background_img.endian);

	// draw circle
	int		x;
	int		y;

	x = 0;
	y = -24;
	while (y <= 24)
	{
		x = -24;
		while (x <= 24)
		{
			// Check if the pixel is inside the circle radius
			if ((x * x) + (y * y) <= (24 * 24))
			{
				pixel_put(&env_p->test_img, 25 + x, 25 + y, 0x00FF0000);
			}
			x++;
		}
		y++;
	}
	env_p->player_x = 500.0;
	env_p->player_y = 500.0;
	env_p->moving_speed = 0.5;
	env_p->player_diretion = 2 * M_PI / 4;
	env_p->turning_speed = 0.0001;
	mlx_put_image_to_window(env_p->mlx, env_p->win, env_p->test_img.img,
		(int) env_p->player_x, (int) env_p->player_y);
	mlx_hook(env_p->win, DestroyNotify, KeyPressMask, close_window, env_p);
	mlx_hook(env_p->win, KeyPress, KeyPressMask, handle_key_press, env_p);
	mlx_hook(env_p->win, KeyRelease, KeyReleaseMask, handle_key_release, env_p);
	mlx_loop_hook(env_p->mlx, update_game, env_p);
	mlx_loop(env_p->mlx);
}
