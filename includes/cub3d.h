/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:47:52 by dongwook          #+#    #+#             */
/*   Updated: 2024/08/09 22:53:44 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <mlx.h>
#include "key_macos.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define KEY_PRESS_EVENT	2
#define KEY_EXIT_EVENT	17

#define TRUE 1
#define FALSE 0


#define VERTICAL 0
#define HORIZONTAL 1

#define TEX_W 64
#define TEX_H 64
#define	TEX_NUM 8

#define MAP_W 24
#define MAP_H 24

#define WIN_W 640
#define WIN_H 480

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	vec_x;
	double	vec_y;
	double	rotate_speed;
	double	move_speed;
}	t_player;

typedef struct s_camera
{
	double vec_x;
	double vec_y;
}	t_camera;

typedef struct s_mlx
{
	void *ptr;
	void *win;
}	t_mlx;

typedef struct s_img
{
	void	*ptr;
	int		*data;
	int		size_line;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}	t_img;

typedef struct s_data
{
	t_player	player;
	t_camera	camera;
	t_mlx		mlx;
	t_img		img;
	int			**texture;
	int			**buffer;
	int			re_buffer;
} t_data;


/* cub3d_key_event.c */

/* cub3d_loop.c */
int cub3d_loop(t_data *data);

/* cub3d_mlx.c */
void	cub3d_mlx_create_window(t_data *data);
void	cub3d_mlx_loop(t_data *data);

/* cub3d_texture.c */
int		cub3d_get_texture(t_data *data);

/* init_data.c */
int init_data(t_data *data);

/* utils.c */
void *ft_memset(void *ptr, int value, int num);

#endif