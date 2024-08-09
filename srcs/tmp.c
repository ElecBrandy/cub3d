/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 15:18:03 by yohlee            #+#    #+#             */
/*   Updated: 2024/08/09 22:11:33 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "key_macos.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define KEY_PRESS_EVENT	2
#define KEY_EXIT_EVENT	17
#define texWidth 64
#define texHeight 64
#define mapWidth 24
#define mapHeight 24
#define width 640
#define height 480

typedef struct	s_img
{
	void	*img;
	int		*data;

	int		size_l;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}				t_img;

typedef struct	s_info
{
	double posX;
	double posY;
	double vec_x;
	double vec_y;
	double camera_vec_x;
	double camera_vec_y;
	void	*mlx;
	void	*win;
	t_img	img;
	int		buf[height][width];
	int		**texture;
	double	moveSpeed;
	double	rotSpeed;
	int		re_buf;

}				t_info;

int	worldMap[mapWidth][mapHeight] =
						{
							{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
							{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
							{4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
							{4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
							{4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
							{4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
							{4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
							{4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
							{4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
							{4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
							{4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
							{4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
							{6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
							{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
							{6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
							{4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
							{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
							{4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
							{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
							{4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
							{4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
							{4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
							{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
							{4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
						};

void	draw(t_info *info)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			info->img.data[y * width + x] = info->buf[y][x];
		}
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}

void	calc(t_info *info)
{
	int	x;

	x = 0;
	if (info->re_buf == 1)
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				info->buf[i][j] = 0;
			}
		}
	}
	while (x < width)
	{
		double cameraX = 2 * x / (double)width - 1;
		double raydir_x= info->vec_x + info->camera_vec_x * cameraX;
		double raydir_y = info->vec_y + info->camera_vec_y * cameraX;
		
		int current_grid_x = (int)info->posX;
		int current_grid_y = (int)info->posY;

		//length of ray from current position to next x or y-side
		double distance_to_reach_x_grid;
		double distance_to_reach_y_grid;
		
		 //length of ray from one x or y-side to next x or y-side
		double distance_to_next_x_grid = fabs(1 / raydir_x);
		double distance_to_next_y_grid = fabs(1 / raydir_y);
		double distance_player_to_wall;
		
		//what direction to step in x or y-direction (either +1 or -1)
		int sign_x;
		int sign_y;
		
		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		if (raydir_x< 0)
		{
			sign_x = -1;
			distance_to_reach_x_grid = (info->posX - current_grid_x) * distance_to_next_x_grid;
		}
		else
		{
			sign_x = 1;
			distance_to_reach_x_grid = (current_grid_x + 1.0 - info->posX) * distance_to_next_x_grid;
		}
		if (raydir_y < 0)
		{
			sign_y = -1;
			distance_to_reach_y_grid = (info->posY - current_grid_y) * distance_to_next_y_grid;
		}
		else
		{
			sign_y = 1;
			distance_to_reach_y_grid = (current_grid_y + 1.0 - info->posY) * distance_to_next_y_grid;
		}

		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (distance_to_reach_x_grid < distance_to_reach_y_grid)
			{
				distance_to_reach_x_grid += distance_to_next_x_grid;
				current_grid_x += sign_x;
				side = 0;
			}
			else
			{
				distance_to_reach_y_grid += distance_to_next_y_grid;
				current_grid_y += sign_y;
				side = 1;
			}
			//Check if ray has hit a wall
			if (worldMap[current_grid_x][current_grid_y] > 0) hit = 1;
		}
		if (side == 0)
			distance_player_to_wall = (current_grid_x - info->posX + (1 - sign_x) / 2) / raydir_x;
		else
			distance_player_to_wall = (current_grid_y - info->posY + (1 - sign_y) / 2) / raydir_y;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(height / distance_player_to_wall);

		//calculate lowest and highest pixel to fill in current stripe
		int draw_start_pixel = -lineHeight / 2 + height / 2;
		if(draw_start_pixel < 0)
			draw_start_pixel = 0;
		int draw_end_pixel = lineHeight / 2 + height / 2;
		if(draw_end_pixel >= height)
			draw_end_pixel = height - 1;

		// texturing calculations
		int texNum = worldMap[current_grid_x][current_grid_y];

		// calculate value of wallX
		double wallX;
		if (side == 0)
			wallX = info->posY + distance_player_to_wall * raydir_y;
		else
			wallX = info->posX + distance_player_to_wall * raydir_x;
		wallX -= floor(wallX);

		// x coordinate on the texture
		int texX = (int)(wallX * (double)texWidth);
		if (side == 0 && raydir_x> 0)
			texX = texWidth - texX - 1;
		if (side == 1 && raydir_y < 0)
			texX = texWidth - texX - 1;

		// How much to increase the texture coordinate perscreen pixel
		double step = 1.0 * texHeight / lineHeight;


		// Starting texture coordinate
		double texPos = (draw_start_pixel - height / 2 + lineHeight / 2) * step;

        
		for (int y = draw_start_pixel; y < draw_end_pixel; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int)texPos & (texHeight - 1);
			texPos += step;
			int color = info->texture[texNum][texHeight * texY + texX];
			// make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if (side == 1)
				color = (color >> 1) & 8355711;
			info->buf[y][x] = color;
			info->re_buf = 1;
		}
		x++;
	}
}

int	main_loop(t_info *info)
{
	calc(info);
	draw(info);
	return (0);
}

int	key_press(int key, t_info *info)
{
	if (key == K_W)
	{
		if (!worldMap[(int)(info->posX + info->vec_x * info->moveSpeed)][(int)(info->posY)])
			info->posX += info->vec_x * info->moveSpeed;
		if (!worldMap[(int)(info->posX)][(int)(info->posY + info->vec_y * info->moveSpeed)])
			info->posY += info->vec_y * info->moveSpeed;
	}
	//move backwards if no wall behind you
	if (key == K_S)
	{
		if (!worldMap[(int)(info->posX - info->vec_x * info->moveSpeed)][(int)(info->posY)])
			info->posX -= info->vec_x * info->moveSpeed;
		if (!worldMap[(int)(info->posX)][(int)(info->posY - info->vec_y * info->moveSpeed)])
			info->posY -= info->vec_y * info->moveSpeed;
	}
	//rotate to the right
	if (key == K_D)
	{
		//both camera direction and camera plane must be rotated
		double oldvec_x = info->vec_x;
		info->vec_x = info->vec_x * cos(-info->rotSpeed) - info->vec_y * sin(-info->rotSpeed);
		info->vec_y = oldvec_x * sin(-info->rotSpeed) + info->vec_y * cos(-info->rotSpeed);
		double oldcamera_vec_x = info->camera_vec_x;
		info->camera_vec_x = info->camera_vec_x * cos(-info->rotSpeed) - info->camera_vec_y * sin(-info->rotSpeed);
		info->camera_vec_y = oldcamera_vec_x * sin(-info->rotSpeed) + info->camera_vec_y * cos(-info->rotSpeed);
	}
	//rotate to the left
	if (key == K_A)
	{
		//both camera direction and camera plane must be rotated
		double oldvec_x = info->vec_x;
		info->vec_x = info->vec_x * cos(info->rotSpeed) - info->vec_y * sin(info->rotSpeed);
		info->vec_y = oldvec_x * sin(info->rotSpeed) + info->vec_y * cos(info->rotSpeed);
		double oldcamera_vec_x = info->camera_vec_x;
		info->camera_vec_x = info->camera_vec_x * cos(info->rotSpeed) - info->camera_vec_y * sin(info->rotSpeed);
		info->camera_vec_y = oldcamera_vec_x * sin(info->rotSpeed) + info->camera_vec_y * cos(info->rotSpeed);
	}
	if (key == K_ESC)
		exit(0);
	mlx_clear_window(info->mlx, info->win);
	main_loop(info);
	return (0);
}

void	load_image(t_info *info, int *texture, char *path, t_img *img)
{
	img->img = mlx_xpm_file_to_image(info->mlx, path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
	for (int y = 0; y < img->img_height; y++)
	{
		for (int x = 0; x < img->img_width; x++)
		{
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
		}
	}
	mlx_destroy_image(info->mlx, img->img);
}

void	load_texture(t_info *info)
{
	t_img	img;
	load_image(info, info->texture[0], "./files/textures/eagle.xpm", &img);
	load_image(info, info->texture[1], "./files/textures/redbrick.xpm", &img);
	load_image(info, info->texture[2], "./files/textures/purplestone.xpm", &img);
	load_image(info, info->texture[3], "./files/textures/greystone.xpm", &img);
	load_image(info, info->texture[4], "./files/textures/bluestone.xpm", &img);
	load_image(info, info->texture[5], "./files/textures/mossy.xpm", &img);
	load_image(info, info->texture[6], "./files/textures/wood.xpm", &img);
	load_image(info, info->texture[7], "./files/textures/colorstone.xpm", &img);
}

int	main(void)
{
	t_info info;
	info.mlx = mlx_init();

	info.posX = 22.0;
	info.posY = 11.5;
	info.vec_x = -1.0;
	info.vec_y = 0.0;
	info.camera_vec_x = 0.0;
	info.camera_vec_y = 0.66;
	info.re_buf = 0;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			info.buf[i][j] = 0;
		}
	}

	if (!(info.texture = (int **)malloc(sizeof(int *) * 8)))
		return (-1);
	for (int i = 0; i < 8; i++)
	{
		if (!(info.texture[i] = (int *)malloc(sizeof(int) * (texHeight * texWidth))))
			return (-1);
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < texHeight * texWidth; j++)
		{
			info.texture[i][j] = 0;
		}
	}

	load_texture(&info);

	info.moveSpeed = 0.05;
	info.rotSpeed = 0.05;
	
	info.win = mlx_new_window(info.mlx, width, height, "mlx");

	info.img.img = mlx_new_image(info.mlx, width, height);
	info.img.data = (int *)mlx_get_data_addr(info.img.img, &info.img.bpp, &info.img.size_l, &info.img.endian);

	mlx_loop_hook(info.mlx, &main_loop, &info);
	mlx_hook(info.win, KEY_PRESS_EVENT, 0, &key_press, &info);

	mlx_loop(info.mlx);
}
