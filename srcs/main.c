/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 20:39:24 by dongwook          #+#    #+#             */
/*   Updated: 2024/08/09 22:56:09 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(void)
{
	t_data  *data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	ft_memset(data, 0, sizeof(t_data));
	if (init_data(&data) != TRUE) // 완료
		return (1);
	if (cub3d_get_texture(&data) != TRUE) // 완료
		return (1);
	if (cub3_mlx_create_window(&data) != TRUE) // 완료
		return (1);
	if (cub3_mlx_loop(&data) != TRUE) // 하는 중
		return (1);
	return (0);
}
