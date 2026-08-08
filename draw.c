/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/08 20:05:46 by anematol          #+#    #+#             */
/*   Updated: 2026/08/08 22:20:55 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// Get pixel color from sprite
int	get_img_pixel(t_img image, int x, int y)
{
	char	*pixel;

	pixel = image.addr + (y * image.line_length + x * (image.bpp / 8));
	return (*(int *)pixel);
}

void	put_pixel_to_image(t_img image, int x, int y, int color)
{
	char	*dst;

	dst = image.addr + (y * image.line_length + x * (image.bpp / 8));
	*(unsigned int *)dst = color;
}

void	put_img_inside_img(t_img small_image, t_img large_image,
						int x, int y)
{
	int	i;
	int	j;
	int	pixel_color;

	i = 0;
	while (i < small_image.height)
	{
		j = 0;
		while (j < small_image.width)
		{
			pixel_color = get_img_pixel(small_image, j, i);
			if ((pixel_color > 0)
				&& (x + j >= 0 && x + j < large_image.width)
				&& (y + i >= 0 && y + i < large_image.height))
			{
				put_pixel_to_image(large_image, x + j, y + i, pixel_color);
			}
			j++;
		}
		i++;
	}
}

int	draw_to_window(t_mlx_data	*env_p)
{
	//copy_background_to_buffer(&env);
	//draw_collectibles(&env);
	//draw_exit(&env, env.collectible_count == 0);
	//put_img_inside_img(env.player_img, env.buffer_img,
	//	env.player_x, env.player_y);
	//put_img_inside_img(env_p->test_img, env_p->background_img,
	//	(int) env_p->player_x, (int) env_p->player_y);
	mlx_put_image_to_window(env_p->mlx, env_p->win, env_p->background_img.img, 0, 0);
	mlx_put_image_to_window(env_p->mlx, env_p->win, env_p->test_img.img, (int) env_p->player_x, (int) env_p->player_y);
	return (0);
}
