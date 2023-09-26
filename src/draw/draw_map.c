/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:42:37 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/09/26 19:39:59 by aoropeza         ###   ########.fr       */
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
			if (ft_strchr("NSEW\n", data->map[y][x]))
			{
				data->level.n_player++;
				if (data->level.n_player > 1)
					exit_error(data, "Error\nMore than one player on map\n", 2);
				data->ply_pos.x = x * size + size / 2;
				data->ply_pos.y = y * size + size / 2;
			}
			x++;
		}
		y++;
	}
}
