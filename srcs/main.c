/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:00:16 by dongwook          #+#    #+#             */
/*   Updated: 2024/08/06 16:33:58 by dongwook         ###   ########.fr       */
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

#include "cud3d.h"

typedef struct s_player
{
	int pos_x;
	int pos_y;
	int vec_x;
	int vec_y;
}	t_player;

typedef struct s_camera
{
	int vec_x;
	int vec_y;
}	t_camera;

int main(void)
{
	t_player player;
	t_camera cam;

	// 플레이어
	player.pos_x = 22;
	player.pos_y = 12;
	player.vec_x = -1;
	player.vec_y = 0;

	// 카메라
	cam.vec_x = 0;
	cam.vex_y = 0;
	


	return (0);
}