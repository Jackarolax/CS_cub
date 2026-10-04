/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coords_and_vectors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 13:43:35 by anematol          #+#    #+#             */
/*   Updated: 2026/10/03 13:57:07 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

t_coords	give_coords(int x, int y)
{
	t_coords	coords;

	coords.x = x;
	coords.y = y;
	return (coords);
}

t_vector	give_vector(double x, double y)
{
	t_vector	vector;

	vector.x = x;
	vector.y = y;
	return (vector);
}

t_coords	add_coords(t_coords coords_1, t_coords coords_2)
{
	coords_1.x += coords_2.x;
	coords_1.y += coords_2.y;
	return (coords_1);
}

t_coords	vector2coords(t_vector vector)
{
	t_coords	coords;

	coords.x = (int) round(vector.x);
	coords.y = (int) round(vector.y);
	return (coords);
}

t_3points	give_3points(t_coords p1, t_coords p2, t_coords p3)
{
	t_3points	points;

	points.p1 = p1;
	points.p2 = p2;
	points.p3 = p3;
	return (points);
}
