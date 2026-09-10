/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 13:01:50 by anematol          #+#    #+#             */
/*   Updated: 2026/09/10 17:42:23 by ssin             ###   ########.fr       */
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
# define COORD_LENGTH 4

# include "../minilibx/mlx.h"
# include "../libft/libft.h"
# include "./events.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>

# include <math.h>
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# include <fcntl.h>
# include <stdio.h> // remove

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
  t_id        *identifiers;
}				t_mlx_data;

/* minilibx */
void	set_minilibx(t_mlx_data *env_p);
t_coords	rotate_point(t_coords point, t_coords center, double angle);
void	pixel_put(t_img img, int x, int y, int color);

/* parser */
void	parser(char *map, t_mlx_data *env);

char	**filter_color(t_mlx_data *env_p, char **tokens);
void	fill_color(t_mlx_data *env_p, char **colors, char **tokens);
void	check_fc_dup(t_mlx_data *env_p, char *token);
void	valid_ceiling_floor(t_mlx_data *env_p, char **tokens);

char	*fill_coordinates(t_id *id_p, char **tokens);
void	check_coordinate(t_mlx_data *env_p, char **tokens);
void	check_dup(t_mlx_data *env_p, char *token);
char	**valid_id_content(t_mlx_data *env_p, char **tokens);

void	check_file_permissions(t_mlx_data *env_p, char **tokens);
int	complete_ids(t_id *id_p);
int valid_char(char *token);
void	call_error(t_mlx_data *env_p, char *message);

int valid_map_content(char *tokens);

/* movement */
void	move_player(t_mlx_data *env_p);

/* hook_functions */
int		close_window(void *param);
int		handle_key_press(int keycode, void *param);
int		handle_key_release(int keycode, void *param);
int		update_game(void *param);

/* main */
void	destroy_everything_and_exit(t_mlx_data *env_p, int exit_code);

/* draw */
int		draw_to_window(t_mlx_data	*env_p);
void	draw_line(t_img img, t_coords begin, t_coords end, int color);
void	draw_rotated_triangle(t_mlx_data *env_p);

#endif
