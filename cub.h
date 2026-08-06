/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 13:01:50 by anematol          #+#    #+#             */
/*   Updated: 2026/08/06 17:12:17 by ssin             ###   ########.fr       */
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
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h> // remove

#endif

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
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

void	set_minilibx();
void	parser(char *map);
