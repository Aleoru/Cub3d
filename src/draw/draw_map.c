/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:42:37 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/09/25 19:26:23 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	draw_map(t_data *data, int width, int heigth, int size)
{
	int	y;
	int	x;

	y = 1;
	while (y <= heigth)
	{
		x = 1;
		while (x <= width)
		{
			if (data->map[y][x] == '1')
				mlx_image_to_window(data->mlx, data->wall, x * size, y * size);
			if (data->map[y][x] == 'N')
			{
				data->ply_pos.x = x * size + size / 2;
				data->ply_pos.y = y * size + size / 2;
			}
			x++;
		}
		y++;
	}
}
