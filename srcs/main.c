/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:00:16 by dongwook          #+#    #+#             */
/*   Updated: 2024/08/07 18:38:06 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	1. 맵 파싱

	2. 초기화
	- 플레이어 초기화 (구조체, 위치, 시작 시선(방향)
	- mlx 초기화 (mlx -> window -> images -> hooks)

	3. 무한반복
	시선이동있을때마다 프레임 그리기
	플레이어 이동 구현
*/

#include "./../includes/cub3d.h"

typedef struct s_player
{
	double pos_x;
	double pos_y;
	double vec_x;
	double vec_y;
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

typedef struct s_data
{
	t_player	player;
	t_camera	camera;
	t_mlx		mlx;
} t_data;


int main(void)
{
	t_data *data;
	double time_of_current_frame = 0;
	double time_of_previous_frame = 0;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (1);
	memset(data, 0, sizeof(t_data));
	
	// 플레이어 초기화
	data->player.pos_x = 22;
	data->player.pos_y = 12;
	data->player.vec_x = -1;
	data->player.vec_y = 0;

	// 카메라 초기화
	data->camera.vec_x = 0;
	data->camera.vec_y = 0;
	
	// mlx 초기화
	data->mlx.ptr = mlx_init(); // mlx 초기화하고
	data->mlx.win = mlx_new_window(data->mlx.ptr, width, height, "mlx"); // 창 새로 만들기

	// 무한루프
	mlx_loop_hook(data->mlx.ptr, &main_loop, data);

	// 이거 뭐지
	mlx_hook(data->mlx.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);

	// 무한루프(mlx 대기)
	return (0);
}

int main_loop(t_data *data)
{
	calc(data);
	return (0);
}

void	calc(t_data *data)
{
	int x;

	x = 0;
	while (x < width)
	{
		
	}
}