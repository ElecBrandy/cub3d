/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 22:42:26 by dongwook          #+#    #+#             */
/*   Updated: 2024/08/09 22:55:55 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void cub3d_get_xpm(t_data *data, int *texture, char *path);

int cub3d_get_texture(t_data *data)
{
	cub3d_get_xpm(data, data->texture[0], "./files/textures/eagle.xpm");
	cub3d_get_xpm(data, data->texture[1], "./files/textures/redbrick.xpm");
	cub3d_get_xpm(data, data->texture[2], "./files/textures/purplestone.xpm");
	cub3d_get_xpm(data, data->texture[3], "./files/textures/greystone.xpm");
	cub3d_get_xpm(data, data->texture[4], "./files/textures/bluestone.xpm");
	cub3d_get_xpm(data, data->texture[5], "./files/textures/mossy.xpm");
	cub3d_get_xpm(data, data->texture[6], "./files/textures/wood.xpm");
	cub3d_get_xpm(data, data->texture[7], "./files/textures/colorstone.xpm");
}

static void cub3d_get_xpm(t_data *data, int *texture, char *path)
{
	int     y;
	int     x;
	t_img   tmp;

	tmp.ptr = mlx_xpm_file_to_image(data->mlx.ptr, path, &tmp.img_width, &tmp.img_height);
	tmp.data = (int *)mlx_get_data_addr(tmp.ptr, &tmp.bpp, &tmp.size_line, &tmp.endian);
	y = 0;
	while (y < tmp.img_height)
	{
		x = 0;
		while (x < tmp.img_width)
		{
			texture[tmp.img_width * y + x] = tmp.data[tmp.img_width * y + x];
		}
		y++;
	}
	mlx_destroy_image(data->mlx.ptr, tmp.ptr);
}
