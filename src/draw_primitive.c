/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_primitive.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 13:45:43 by anematol          #+#    #+#             */
/*   Updated: 2026/10/03 13:57:31 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	draw_line(t_img img, t_coords begin, t_coords end, int color)
{
	t_vector	delta;
	t_coords	curr_delta;
	double		line_len;
	double		i;

	delta.x = (double)(end.x - begin.x);
	delta.y = (double)(end.y - begin.y);
	line_len = sqrt((delta.x * delta.x) + (delta.y * delta.y));
	i = 0.0;
	while (i <= line_len)
	{
		curr_delta.x = (int) round(delta.x * i / line_len);
		curr_delta.y = (int) round(delta.y * i / line_len);
		if (!is_out_of_bounds(img, add_coords(begin, curr_delta)))
			pixel_put(img, add_coords(begin, curr_delta).x,
				add_coords(begin, curr_delta).y, color);
		i++;
	}
}

void	draw_square(t_img img, t_coords start_point, int len, int color)
{
	t_coords	end_point;

	end_point.x = start_point.x + len;
	end_point.y = start_point.y;
	draw_line(img, start_point, end_point, color);
	start_point.x += len;
	start_point.y += len;
	draw_line(img, start_point, end_point, color);
	end_point.x -= len;
	end_point.y += len;
	draw_line(img, start_point, end_point, color);
	start_point.x -= len;
	start_point.y -= len;
	draw_line(img, start_point, end_point, color);
}

void	draw_triangle(t_img img, t_3points triangle, int color)
{
	draw_line(img, triangle.p1, triangle.p2, color);
	draw_line(img, triangle.p2, triangle.p3, color);
	draw_line(img, triangle.p3, triangle.p1, color);
}

void	fill_square(t_img img, t_coords start_point, int len, int color)
{
	t_coords	end_point;
	int			i;

	end_point.x = start_point.x + len;
	end_point.y = start_point.y;
	i = 0;
	while (i <= len)
	{
		draw_line(img, start_point, end_point, color);
		start_point.y++;
		end_point.y++;
		i++;
	}
}

void	fill_triangle(t_img img, t_3points triangle, int color)
{
	t_vector	delta;
	t_coords	curr_delta;
	double		line_len;
	double		i;

	delta.x = (double)(triangle.p3.x - triangle.p2.x);
	delta.y = (double)(triangle.p3.y - triangle.p2.y);
	line_len = sqrt((delta.x * delta.x) + (delta.y * delta.y));
	i = 0.0;
	while (i <= line_len)
	{
		curr_delta.x = (int) round(delta.x * i / line_len);
		curr_delta.y = (int) round(delta.y * i / line_len);
		draw_line(img, triangle.p1,
			add_coords(triangle.p2, curr_delta), color);
		i += 0.01;
	}
}
