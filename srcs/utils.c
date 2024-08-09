/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:07:19 by dongwook          #+#    #+#             */
/*   Updated: 2024/08/09 21:08:52 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void *ft_memset(void *ptr, int value, int num)
{
    unsigned char *p = (unsigned char *)ptr;
    int i = 0;

    while (i < num)
    {
        p[i] = (unsigned char)value;
        i++;
    }

    return ptr;
}
