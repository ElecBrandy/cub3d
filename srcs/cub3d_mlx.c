/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 22:14:41 by dongwook          #+#    #+#             */
/*   Updated: 2024/08/09 22:52:18 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub3d_mlx_create_window(t_data *data)
{
	data->mlx.win = mlx_new_window(data->mlx.ptr, WIN_W, WIN_H, "mlx");
	data->img.ptr = mlx_new_image(data->mlx.ptr, WIN_W, WIN_H);
	data->img.data = (int *)mlx_get_data_addr(data->img.ptr, &data->img.bpp, &data->img.size_line, &data->img.endian);
}

void	cub3d_mlx_loop(t_data *data)
{
	mlx_loop_hook(data->mlx.ptr, &cub3d_loop, &data);
	mlx_hook(data->mlx.win, KEY_PRESS_EVENT, 0, &cub3d_key_event, &data);
	mlx_loop(data->mlx.ptr);
}