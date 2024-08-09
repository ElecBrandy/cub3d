/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:00:16 by dongwook          #+#    #+#             */
/*   Updated: 2024/08/09 22:51:16 by dongwook         ###   ########.fr       */
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

#include "mlx.h"
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
	int			buf[WIN_H][WIN_W];
	int			re_buf;
} t_data;

/* init_data.c */
int init_data(t_data *data);

/* utils.c */
void *ft_memset(void *ptr, int value, int num);

int	worldMap[MAP_W][MAP_H] =
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

void	draw(t_data *data)
{
	for (int y = 0; y < WIN_H; y++)
	{
		for (int x = 0; x < WIN_W; x++)
		{
			data->img.data[y * WIN_W + x] = data->buf[y][x];
		}
	}
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, data->img.ptr, 0, 0);
}

void	calc(t_data *data)
{
	int x;

	x = 0;
	if (data->re_buf == 1)
	{
		for (int i = 0; i < WIN_H; i++)
		{
			for (int j = 0; j < WIN_W; j++)
			{
				data->buf[i][j] = 0;
			}
		}
	}
	while (x < WIN_W)
	{
		double camera_x = 2 * x / (double)WIN_W - 1;
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
		int hit_direction; // 충돌한 벽의 수직 혹은 수평?

		if (raydir_x < 0) {
			sign_x = -1;
			distance_to_reach_x_grid = (data->player.pos_x - current_grid_x) * distance_to_next_x_grid;
		} else {
			sign_x = 1;
			distance_to_reach_x_grid = (current_grid_x + 1.0 - data->player.pos_x) * distance_to_next_x_grid;
		}

		if (raydir_y < 0) {
			sign_y = -1;
			distance_to_reach_y_grid = (data->player.pos_y - current_grid_y) * distance_to_next_y_grid;
		} else {
			sign_y = 1;
			distance_to_reach_y_grid = (current_grid_y + 1.0 - data->player.pos_y) * distance_to_next_y_grid;
		}
		// 이제 광선상 진행하면서 검사
		while (hit == 0)
		{
			if (distance_to_reach_x_grid < distance_to_reach_y_grid)
			{
				distance_to_reach_x_grid += distance_to_next_x_grid; // 다음, 그 다음 축 그리드까지 얼마나 걸리는지 업데이트
				current_grid_x += sign_x;
				hit_direction = VERTICAL; // 이 상황에서 벽과 충돌한다면 그것은 벽의 수직 방향(동, 서)
			}
			else
			{
				distance_to_reach_y_grid += distance_to_next_y_grid; // 다음, 그 다음 축 그리드까지 얼마나 걸리는지 업데이트
				current_grid_y += sign_y;
				hit_direction = HORIZONTAL; // 이 상황에서 벽과 충돌한다면 그것은 벽의 수직 방향(동, 서)
			}
			// 한 단위 진행하고 충돌체크
			if (worldMap[current_grid_x][current_grid_y] > 0)
				hit = 1;
		}
		
		// 충돌했을경우, 벽의 방향에 따라 플레이어-벽 사이의 직선거리 계산
		// 왜 하냐면 나중에 벽 높이를 얼마나 줄것인지 계산할떄 필요함
		if (hit_direction == VERTICAL)
			distance_player_to_wall = (current_grid_x - data->player.pos_x + (1 - sign_x) / 2) / raydir_x;
		else
			distance_player_to_wall = (current_grid_y - data->player.pos_y + (1 - sign_y) / 2) / raydir_y;
		
		// 해당 점(도트)가 플레이어의 카메라 평면으로부터 얼마나 먼지에 따라서 높이(가상의 z축) 어디에 찍히게 할지
		int line_height = (int)(WIN_H / distance_player_to_wall);

		// 현재 카메라 상 x의 세로 도트 찍기 시작점을 구한다고 보면 됨
		int draw_start_pixel = (WIN_H / 2) + (-1 *line_height / 2);
		if (draw_start_pixel < 0)
			draw_start_pixel = 0;
		int draw_end_pixel = (WIN_H  / 2) + (line_height / 2);
		if (draw_end_pixel >= WIN_H)
			draw_end_pixel = WIN_H  - 1;

		// wall_x : 실제로 벽이 광선과 충돌한 지점(점)의 x 또는 y 좌표
		double wall_x;
		if (hit_direction == VERTICAL) // 수직방향과 충돌했을경우
		{
			wall_x = data->player.pos_y + distance_player_to_wall * raydir_y;
			/*
				플레이어의 현재 좌표 + (카메라평면에서벽까지거리 * 광선벡터)
				닮음비로 풀수도있음
			*/
		} 
		else // 수평방향과 충돌했을경우
		{
			wall_x = data->player.pos_x + distance_player_to_wall * raydir_x;
		}
		/*
			아래 연산을 통해 wall_x의 소수점 부분만 남긴다.
			여기서 wall_x는 최종적으로 0부터 1 사이 값이 됨. 즉 벽 너비를 0~1이라고 했을때,
			광선과 벽이 충돌한 지점이 해당 벽에서의 상대적 위치(텍스처 그릴때 써야함)를 기록
		*/
		wall_x = wall_x - floor(wall_x);

		/*
			아래는 텍스쳐 방향에 관련된거같은데 껐다켜보면서 비교해봐야이해될거같음 ㅠ
		*/
		int texture_x = (int)(wall_x * (double)TEX_W);
		if (hit_direction == VERTICAL && raydir_x > 0)
			texture_x = TEX_W - texture_x - 1;
		if (hit_direction == HORIZONTAL && raydir_y < 0)
			texture_x = TEX_W - texture_x - 1;
		
		/*
			TEX_H : 텍스쳐 이미지의 총 수직 픽셀 수. 즉, 텍스처 이미지의 전체 높이
			line_height : 화면상 그려질 선 높이
			step : 텍스러의 한 픽셀이 스크린상에서 몇 픽셀로 그려져야하는지
			1.0 명시적 형변환 or 부동소수점계산
		*/
		double step = 1.0 * TEX_H / line_height;


	/*
		draw_start_pixel : 화면에 그려질 벽의 시작지점
		결국 아래식은 "화면에 그려질 벽의 시작지점"이 화면 중앙에 대해 얼마나
		상위에 위치하는지 나타냄.
		거기에 line_height / 2를 더해서 실제로 텍스처가 그려질 시작높이를 조정함
		그런데 생각보니까 그냥 0 시작 아닌가?
		0으로 초기화해서 해보고 문제생기면 바꾸기
	*/
		double texture_pos = (draw_start_pixel - WIN_H / 2 + line_height / 2) * step;
		// double texture_pos = 0;
		
		// 아래는 텍스쳐(세로 한줄) 채워넣기 나중에 수정
				// 텍스쳐? 이건 뭔지 모르겟
		int texture_type = worldMap[current_grid_x][current_grid_y];

		int y = draw_start_pixel;
		while (y < draw_end_pixel)
		{
			// texY 계산 및 범위 체크
			int texY = (int)texture_pos & (TEX_H - 1);
			if (texY < 0 || texY >= TEX_H) {
				printf("Error: texY out of bounds! texY: %d, TEX_H: %d\n", texY, TEX_H);
				break; // texY가 유효 범위를 벗어나면 루프를 종료
			}

			texture_pos += step;

			// texture_x와 texY의 조합으로 인덱스 계산 및 범위 체크
			int index = TEX_H * texY + texture_x;
			if (index < 0 || index >= (TEX_H * TEX_W)) {
				printf("Error: Texture index out of bounds! index: %d, max index: %d\n", index, (TEX_H * TEX_W) - 1);
				break; // 인덱스가 유효 범위를 벗어나면 루프를 종료
			}

			int color = data->texture[texture_type][index];

			// hit_direction에 따른 색상 처리
			if (hit_direction == 1)
				color = (color >> 1) & 8355711;

			// 화면 버퍼에 색상 적용
			data->buf[y][x] = color;
			data->re_buf = 1;

			// 다음 픽셀로 이동
			y++;
		}

		x++;
	}
}



int main_loop(t_data *data)
{
	calc(data);
	draw(data);
	return (0);
}

int key_press(int key, t_data *data)
{
    if (key == K_W)
    {
        if (!worldMap[(int)(data->player.pos_x + data->player.vec_x * data->player.move_speed)][(int)(data->player.pos_y)])
            data->player.pos_x += data->player.vec_x * data->player.move_speed;
        if (!worldMap[(int)(data->player.pos_x)][(int)(data->player.pos_y + data->player.vec_y * data->player.move_speed)])
            data->player.pos_y += data->player.vec_y * data->player.move_speed;
    }
    // Move backwards if no wall behind you
    if (key == K_S)
    {
        if (!worldMap[(int)(data->player.pos_x - data->player.vec_x * data->player.move_speed)][(int)(data->player.pos_y)])
            data->player.pos_x -= data->player.vec_x * data->player.move_speed;
        if (!worldMap[(int)(data->player.pos_x)][(int)(data->player.pos_y - data->player.vec_y * data->player.move_speed)])
            data->player.pos_y -= data->player.vec_y * data->player.move_speed;
    }
    // Rotate to the right
    if (key == K_D)
    {
        double oldDirX = data->player.vec_x;
        data->player.vec_x = data->player.vec_x * cos(-data->player.rotate_speed) - data->player.vec_y * sin(-data->player.rotate_speed);
        data->player.vec_y = oldDirX * sin(-data->player.rotate_speed) + data->player.vec_y * cos(-data->player.rotate_speed);
    }
    // Rotate to the left
    if (key == K_A)
    {
        double oldDirX = data->player.vec_x;
        data->player.vec_x = data->player.vec_x * cos(data->player.rotate_speed) - data->player.vec_y * sin(data->player.rotate_speed);
        data->player.vec_y = oldDirX * sin(data->player.rotate_speed) + data->player.vec_y * cos(data->player.rotate_speed);
    }
    if (key == K_ESC)
        exit(0);
    mlx_clear_window(data->mlx.ptr, data->mlx.win);
    main_loop(data);
    return (0);
}

void	load_image(t_data *data, t_img *tmp, int *texture, char *path)
{
	tmp->ptr = mlx_xpm_file_to_image(data->mlx.ptr, path, &tmp->img_width, &tmp->img_height);
	tmp->data = (int *)mlx_get_data_addr(tmp->ptr, &tmp->bpp, &tmp->size_line, &tmp->endian);
	for (int y = 0; y < tmp->img_height; y++)
	{
		for (int x = 0; x < tmp->img_width; x++)
		{
			texture[tmp->img_width * y + x] = tmp->data[tmp->img_width * y + x];
		}
	}
	mlx_destroy_image(data->mlx.ptr, tmp->ptr);
}

// 텍스처 로딩 함수: 모든 텍스처를 초기화하고 로드합니다.
void load_texture(t_data *data)
{
	t_img	tmp;

    load_image(data, &tmp, data->texture[0], "./files/textures/eagle.xpm");
    load_image(data, &tmp, data->texture[1], "./files/textures/redbrick.xpm");
    load_image(data, &tmp, data->texture[2], "./files/textures/purplestone.xpm");
    load_image(data, &tmp, data->texture[3], "./files/textures/greystone.xpm");
    load_image(data, &tmp, data->texture[4], "./files/textures/bluestone.xpm");
    load_image(data, &tmp, data->texture[5], "./files/textures/mossy.xpm");
    load_image(data, &tmp, data->texture[6], "./files/textures/wood.xpm");
    load_image(data, &tmp, data->texture[7], "./files/textures/colorstone.xpm");
}

int main(void)
{
	t_data data;
	// double time_of_current_frame = 0;
	// double time_of_previous_frame = 0;
	
	// mlx 초기화
	data.mlx.ptr = mlx_init();
	
	// 플레이어 초기화
	data.player.pos_x = 22.0;
	data.player.pos_y = 11.5;
	data.player.vec_x = -1.0;
	data.player.vec_y = 0.0;
	data.player.move_speed = 0.05;
	data.player.rotate_speed = 0.05;

	// 카메라 초기화
	data.camera.vec_x = 0.0;
	data.camera.vec_y = 0.66;

	data.re_buf = 0;

	// 버퍼 초기화
	for (int i = 0; i < WIN_H; i++) {
		for (int j = 0; j < WIN_W; j++) {
			data.buf[i][j] = 0;
		}
	}

	//텍스쳐 할당
	if (!(data.texture = (int **)malloc(sizeof(int *) * 8)))
		return (-1);
	for (int i = 0; i < 8; i++)
	{
		if (!(data.texture[i] = (int *)malloc(sizeof(int) * (TEX_H * TEX_W))))
			return (-1);
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < TEX_H * TEX_W; j++)
		{
			data.texture[i][j] = 0;
		}
	}
	
	load_texture(&data);

	// 창 새로 만들기
	data.mlx.win = mlx_new_window(data.mlx.ptr, WIN_W, WIN_H, "mlx");
	data.img.ptr = mlx_new_image(data.mlx.ptr, WIN_W, WIN_H);
	data.img.data = (int *)mlx_get_data_addr(data.img.ptr, &data.img.bpp, &data.img.size_line, &data.img.endian);

	// 무한루프
	mlx_loop_hook(data.mlx.ptr, &main_loop, &data);

	mlx_hook(data.mlx.win, KEY_PRESS_EVENT, 0, &key_press, &data);

	// 무한루프(mlx 대기)
	mlx_loop(data.mlx.ptr);
	return (0);
}
