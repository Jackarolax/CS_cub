/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 13:01:50 by anematol          #+#    #+#             */
/*   Updated: 2026/09/20 18:47:45 by anematol         ###   ########.fr       */
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

#define WIN_HEIGHT 800
#define WIN_WIDTH 1200
#define BLOCK_SIZE 100

#define FOV_DEGREE 130
#define FOV_HEIGHT_SCALING_FACTOR 9

# define MOVING_SPEED 2
# define TURNING_SPEED 2

# define MINI_PLAYER_CENTER_POINT 25
# define MINI_PLAYER_EDGE_POINT MINI_PLAYER_CENTER_POINT * 2
# define MINI_PLAYER_WIDTH 20
# define MINI_PLAYER_LENGTH 40


#define WHITE 0x00FFFFFF
#define RED 0x00FF0000
#define GREEN 0x0000FF00
#define BLUE 0x000000FF


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

typedef struct	s_vector {
	double	x;
	double	y;
}				t_vector;

typedef struct	s_3points {
	t_coords p1;
	t_coords p2;
	t_coords p3;
}				t_3points;


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
	t_img		player_img;
	t_img		sprite_n_img;
	t_img		sprite_s_img;
	t_img		sprite_w_img;
	t_img		sprite_e_img;
	t_img		background_img;
	t_img		buffer_img;
	void		*mlx;
	void		*win;
	int			win_width;
	int			win_height;
	int			width;
	int			height;
	int			mv_fwd_pressed;
	int			mv_bck_pressed;
	int			mv_l_pressed;
	int			mv_r_pressed;
	int			look_l_pressed;
	int			look_r_pressed;
	double		player_x;
	double		player_y;
	double		player_direction;
	t_vector	ray_vector;
	char		**map;
	int			map_height;
	int			map_width;
	int			block_size;
	t_id		*identifiers;
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
void	free_str_array(char **str);

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
void	draw_square(t_img img, t_coords start_point, int len, int color);
void	draw_obstacles(t_mlx_data *env_p);
int		check_collision(t_mlx_data *env_p, int check_x, int check_y);
int		collision_position_x(t_mlx_data *env_p, int new_x);
int		collision_position_y(t_mlx_data *env_p, int new_y);
int		touching_x(t_mlx_data *env_p);
int		touching_y(t_mlx_data *env_p);
t_coords	give_coords(int x, int y);
t_vector	give_vector(double x, double y);
t_vector	get_ray_vector(t_mlx_data *env_p, double degree_angle);
double		get_ray_len(t_mlx_data *env_p, double degree_angle);
t_coords	get_exact_collision_point(t_mlx_data *env_p, t_vector ray_vector);
char	get_wall_collision_side(t_mlx_data *env_p);
double get_wall_x(t_mlx_data *env_p);

#endif
