/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 13:01:50 by anematol          #+#    #+#             */
/*   Updated: 2026/08/11 18:50:31 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# define SIZE 1000
# define EXTENSION ".cub"
# define CUB 0
# define VALID 0
# define ERROR -1
# define ID_NO "NO"
# define ID_SO "SO"
# define ID_WE "WE"
# define ID_EA "EA"
# define ID_F "F"
# define ID_C "C"

# include "./minilibx/mlx.h"
# include "./libft/libft.h"
# include "./events.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>

# include <math.h>
#define M_PI 3.14159265358979323846
# include <fcntl.h>
# include <stdio.h> // remove

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_length;
	int		endian;
}				t_img;

typedef struct  s_id {
  char  *NO;
  char  *SO;
  char  *WE;
  char  *EA;
  int   F_R;
  int   F_G;
  int   F_B;
  int   C_R;
  int   C_G;
  int   C_B;
} t_id;

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
void	parser(char *map);
void	set_minilibx(t_mlx_data *env_p);
int		close_window(void *param);
int		handle_key_press(int keycode, void *param);
int		handle_key_release(int keycode, void *param);
void	destroy_everything_and_exit(t_mlx_data *env_p, int exit_code);
int		update_game(void *param);
void	move_player(t_mlx_data *env_p);
int		draw_to_window(t_mlx_data	*env_p);

#endif
