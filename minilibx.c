/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 18:20:30 by ssin              #+#    #+#             */
/*   Updated: 2026/08/08 20:07:38 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// add sprites function

void	pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}



void	set_minilibx(t_mlx_data *env_p)
{

	env_p->mlx = mlx_init();
	env_p->test_img.width = 1080;
	env_p->test_img.height = 800;
	env_p->win = mlx_new_window(env_p->mlx, env_p->width,
		env_p->height, "CUB 3D");
	env_p->test_img.img = mlx_new_image(env_p->mlx, env_p->test_img.width,
		env_p->test_img.height);
	env_p->test_img.addr = mlx_get_data_addr(env_p->test_img.img,
		&env_p->test_img.bits_per_pixel, &env_p->test_img.line_length,
		&env_p->test_img.endian);

	// draw square
	int		x;
	int		y;

	x = 100;
	y = 100;
	while (x < 201)
	{
		pixel_put(&env_p->test_img, x, 100, 0x00FF0000);
		pixel_put(&env_p->test_img, x, 200, 0x00FF0000);
		pixel_put(&env_p->test_img, 100, y, 0x00FF0000);
		pixel_put(&env_p->test_img, 200, y, 0x00FF0000);
		x++;
		y++;
	}
	mlx_put_image_to_window(env_p->mlx, env_p->win, env_p->test_img.img, 0, 0);
	mlx_hook(env_p->win, DESTROY_NOTIFY, KEY_PRESS_MASK, close_window, env_p);
	mlx_hook(env_p->win, KEY_PRESS, KEY_PRESS_MASK, handle_key_press, env_p);
	mlx_loop(env_p->mlx);
}
