/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 13:01:50 by anematol          #+#    #+#             */
/*   Updated: 2026/08/08 18:50:41 by anematol         ###   ########.fr       */
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
# include <stdlib.h>
# ifndef DestroyNotify
#  define DestroyNotify 17
# endif
# ifndef KeyPressMask
#  define KeyPressMask 1
# endif
# ifndef KeyPress
#  define KeyPress 0
# endif
# ifndef XK_Escape
#  define XK_Escape 53
# endif

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
