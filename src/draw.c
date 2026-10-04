/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/08 20:05:46 by anematol          #+#    #+#             */
/*   Updated: 2026/10/03 14:16:07 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	pixel_put(t_img img, int x, int y, int color)
{
	char	*dst;

	dst = img.addr + (y * img.line_length + x * (img.bpp / 8));
	*(unsigned int *)dst = color;
}

void	reset_img(t_img image)
{
	char	*pixels;
	int		total_size;

	pixels = mlx_get_data_addr(image.img, &image.bpp,
			&image.line_length, &image.endian);
	total_size = image.line_length * image.height;
	ft_bzero(pixels, total_size);
}

// Get pixel color from sprite
int	get_img_pixel(t_img image, int x, int y)
{
	char	*pixel;

	pixel = image.addr + (y * image.line_length + x * (image.bpp / 8));
	return (*(int *)pixel);
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
				pixel_put(large_image, x + j, y + i, pixel_color);
			}
			j++;
		}
		i++;
	}
}

int	draw_to_window(t_mlx_data	*env_p)
{
	reset_img(env_p->background_img);
	put_img_inside_img(env_p->background_buffer_img, env_p->background_img,
		0, 0);
	draw_fov(env_p);
	mlx_put_image_to_window(env_p->mlx, env_p->win,
		env_p->background_img.img, 0, 0);
	return (0);
}
