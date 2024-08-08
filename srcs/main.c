/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:00:16 by dongwook          #+#    #+#             */
/*   Updated: 2024/08/08 20:49:25 by dongwook         ###   ########.fr       */
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

#define VERTICAL 0
#define HORIZONTAL 1

#define FALSE 0
#define TRUE 1

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
	data->player.pos_x = 22.0;
	data->player.pos_y = 12.0;
	data->player.vec_x = -1.0;
	data->player.vec_y = 0.0;

	// 카메라 초기화
	data->camera.vec_x = 0.0;
	data->camera.vec_y = 0.66;
	
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
		double camera_x = 2 * x / (double)width - 1;
		double raydir_x = data->player.vec_x + data->camera.vec_x * camera_x;
		double raydir_y = data->player.vec_y + data->camera.vec_y * camera_x;

		// 광선 시작점으로 초기화 즉, 플레이어의 현재 위치 (정확한 시작점을 위한 int형으로)
		// 앞으로 이걸 갱신해나가면서 벽 충돌 체크
		int current_grid_x = (int)data->player.pos_x;
		int current_grid_y = (int)data->player.pos_y;
		
		// 광선이 게임 맵의 격자에서 다음 x축 또는 y축 격자선까지 도달하는 데 필요한 거리
		double distance_to_reach_x_grid;
		double distance_to_reach_y_grid;

		// 광선이 x축 또는 y축 방향의 격자선에서 다음 격자선까지 이동하는 데 필요한 거리
		// 광선의 성분 또는 벡터는 전혀 아니고 정말 순수하게 광선 상에서의 거리를 의미
		// 나중에 둘 중에 더 작은 값으로 진행하며 검사(교차해가면서 될수도?)
		double distance_to_next_x_grid = fabs(1 / raydir_x);
		double distance_to_next_y_grid = fabs(1 / raydir_y);
		double distance_player_to_wall;

		// x 또는 y의 진행 방향 (+1 또는 -1)
		int	sign_x;
		int sign_y;

		// 
		int hit = 0; // 충돌 여부 
		int direction_of_wall; // 충돌한 벽의 수직 혹은 수평?

		if (raydir_x < 0) // 광선의 x벡터 성분이 음수인 경우
		{
			sign_x = -1;
			distance_to_reach_x_grid = (data->player.pos_x - current_grid_x) * distance_to_next_x_grid;
		}
		else // 광선의 x벡터 성분이 양수인 경우
		{
			sign_x = 1;
			distance_to_reach_x_grid = (data->player.pos_x + 1.0 - current_grid_x) * distance_to_next_x_grid;
		}
		if (raydir_y < 0) // 광선의 y벡터 성분이 음수인 경우
		{
			sign_y = -1;
			distance_to_reach_y_grid = (data->player.pos_y - current_grid_y) * distance_to_next_y_grid;
		}
		else // 광선의 y벡터 성분이 양수인 경우
		{
			sign_y = 1;
			distance_to_reach_x_grid = (data->player.pos_y + 1.0 - current_grid_y) * distance_to_next_y_grid;
		}

		// 이제 광선상 진행하면서 검사
		while (hit == 0)
		{
			if (distance_to_reach_x_grid < distance_to_reach_y_grid)
			{
				distance_to_reach_x_grid += distance_to_next_x_grid; // 다음, 그 다음 축 그리드까지 얼마나 걸리는지 업데이트
				current_grid_x += sign_x;
				direction_of_wall = VERTICAL; // 이 상황에서 벽과 충돌한다면 그것은 벽의 수직 방향(동, 서)
			}
			else
			{
				distance_to_reach_x_grid += distance_to_next_x_grid; // 다음, 그 다음 축 그리드까지 얼마나 걸리는지 업데이트
				current_grid_y += sign_x;
				direction_of_wall = HORIZONTAL; // 이 상황에서 벽과 충돌한다면 그것은 벽의 수직 방향(동, 서)
			}
			// 한 단위 진행하고 충돌체크
			if (worldMap[current_grid_x][current_grid_y] > 0)
				hit = TRUE;
		}
		
		// 충돌했을경우, 벽의 방향에 따라 플레이어-벽 사이의 직선거리 계산
		// 왜 하냐면 나중에 벽 높이를 얼마나 줄것인지 계산할떄 필요함
		if (direction_of_wall == VERTICAL)
			distance_player_to_wall = (current_grid_x - data->player.pos_x + (1 - sign_x) / 2) / raydir_x;
		else
			distance_player_to_wall = (current_grid_x - data->player.pos_y + (1 - sign_y) / 2) / raydir_y;
		
		// 해당 점(도트)가 플레이어의 카메라 평면으로부터 얼마나 먼지에 따라서 높이(가상의 z축) 어디에 찍히게 할지
		int line_height = (int)(height / distance_player_to_wall);

		// 현재 카메라 상 x의 세로 도트 찍기 시작점을 구한다고 보면 됨
		int draw_top_pixel = height / 2 + (-1) * (line_height / 2);
		if (draw_top_pixel < 0)
			draw_top_pixel = 0;
		int draw_end_pixel = height / 2 + (line_height / 2);
		if (draw_end_pixel >= height)
			draw_end_pixel = height - 1;
		
		// 텍스쳐? 이건 뭔지 모르겟
		int worldMap[current_grid_x][current_grid_y];

		// 이것도 뭔지 모르겟음
		double wall_x;
		if (direction_of_wall == VERTICAL)
			wall_x = data->player.pos_y + distance_player_to_wall * raydir_x;
	}
}
