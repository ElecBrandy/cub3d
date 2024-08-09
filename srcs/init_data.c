/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 20:47:26 by dongwook          #+#    #+#             */
/*   Updated: 2024/08/09 22:36:57 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_player(t_data *data);
static void	init_camera(t_data *data);
static int	init_buffer(t_data *data);

int init_data(t_data *data)
{
	data->mlx.ptr = mlx_init();
	init_player(data);
	init_camera(data);
	if (init_buffer(data) != TRUE)
		return (FALSE);
	if (init_texture(data) != TRUE)
		return (FALSE);
	return (TRUE);
}

static void	init_player(t_data *data)
{
	data->player.pos_x = 22.0;
	data->player.pos_y = 11.5;
	data->player.vec_x = -1.0;
	data->player.vec_y = 0.0;
	data->player.move_speed = 0.05;
	data->player.rotate_speed = 0.05;
}

static void	init_camera(t_data *data)
{
	data->camera.vec_x = 0.0;
	data->camera.vec_y = 0.66;
}

static int	init_buffer(t_data *data)
{
	int	i;

	data->buffer = (int **)malloc(sizeof(int *) * WIN_H);
	if (!data->buffer)
		return (FALSE);
	i = 0;
	while (i < WIN_H)
	{
		data->buffer[i] = (int *)malloc(WIN_W * sizeof(int));
		if (!data->buffer[i])
		{
			// error : 그냥 exit 아님 free..?
			return (FALSE);
		}
		ft_memset(data->buffer[i], 0, WIN_W * sizeof(int));
	}
	return (TRUE);
}

static int	init_texture(t_data *data)
{
	int	i;

	data->texture = (int **)malloc(sizeof(int *) * TEX_NUM);
	if (!data->buffer)
		return (FALSE);
	i = 0;
	while (i < TEX_NUM)
	{
		data->texture[i] = (int *)malloc((TEX_H * TEX_W) * sizeof(int));
		if (!data->texture[i])
		{
			// error : 그냥 exit 아님 free..?
			return (FALSE);
		}
		ft_memset(data->texture[i], 0, (TEX_H * TEX_W) * sizeof(int));
	}
	return (TRUE);
}