/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 13:01:50 by anematol          #+#    #+#             */
/*   Updated: 2026/08/04 21:49:26 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H
# include "./minilibx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h> // remove
#include <stdlib.h>

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_mlx_data {
	t_img			test_img;
	void			*mlx;
	void			*win;
	int				width;
	int				height;
}				t_mlx_data;

void	set_minilibx(t_mlx_data *env_p);
int		close_window(void *param);
int		handle_key_press(int keycode, void *param);
void	destroy_everything_and_exit(t_mlx_data *env_p, int exit_code);

#endif
