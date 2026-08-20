/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 13:01:50 by anematol          #+#    #+#             */
/*   Updated: 2026/08/20 20:02:27 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H
# include "./minilibx/mlx.h"
# include "./libft/libft.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h> // remove
# include <stdlib.h>
# include <math.h>
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define DESTROY_NOTIFY 17
# define KEY_PRESS 0
# define XK_ESCAPE 53


# define MINI_PLAYER_CENTER_POINT 25
# define MINI_PLAYER_EDGE_POINT MINI_PLAYER_CENTER_POINT * 2
# define MINI_PLAYER_WIDTH MINI_PLAYER_CENTER_POINT / 5

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_length;
	int		endian;
}				t_img;

typedef struct	s_coords {
	int	x;
	int	y;
}				t_coords;

typedef struct s_mlx_data {
	t_img			test_img;
	t_img			background_img;
	void			*mlx;
	void			*win;
	int				width;
	int				height;
	int				mv_fwd_pressed;
	int				mv_bck_pressed;
	int				mv_l_pressed;
	int				mv_r_pressed;
	int				look_l_pressed;
	int				look_r_pressed;
	double			player_x;
	double			player_y;
	double			moving_speed;
	double			player_diretion;
	double			turning_speed;
}				t_mlx_data;

void	set_minilibx(t_mlx_data *env_p);
int		close_window(void *param);
int		handle_key_press(int keycode, void *param);
int		handle_key_release(int keycode, void *param);
void	destroy_everything_and_exit(t_mlx_data *env_p, int exit_code);
int		update_game(void *param);
void	move_player(t_mlx_data *env_p);
int		draw_to_window(t_mlx_data	*env_p);
void	pixel_put(t_img img, int x, int y, int color);
void	draw_line(t_img img, t_coords begin, t_coords end, int color);
t_coords	rotate_point(t_coords point, t_coords center, double angle);
void	draw_rotated_triangle(t_mlx_data *env_p);

#endif
