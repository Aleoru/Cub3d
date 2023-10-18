/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 03:18:17 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/10/18 18:23:28 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	draw_minimap(t_data *data, int size, int color)
{
	t_point	init;
	int		x;
	int		y;

	y = 0;
	while (y < data->level.size_y + 1)
	{
		x = 0;
		while (x < data->level.size_x)
		{
			if (data->map[y][x] == '1')
			{
				init.x = x * size;
				init.y = y * size;
				draw_cell(data->minimap, init, size, color);
			}
			x++;
		}
		y++;
	}
}

void	draw_player_minimap(t_data *data, int size)
{
	t_point	pos;
	int		color;

	color = 0xFF00FFFF;
	pos.x = (data->ply_pos.x / size) - (int)size / 2;
	pos.y = (data->ply_pos.y / size) - (int)size / 2;
	clear_image(data->ply_minimap);
	draw_cell(data->ply_minimap, pos, (int)size / 2, color);
}

void	create_minimap(t_data *data, int cell_size)
{
	int		c;
	int		w;
	int		h;

	w = data->level.size_x * cell_size;
	h = data->level.size_y * (cell_size + 1);
	c = 0x000000FF;
	data->minimap = mlx_new_image(data->mlx, w, h);
	data->ply_minimap = mlx_new_image(data->mlx, w, h);
	draw_minimap(data, cell_size, c);
	mlx_image_to_window(data->mlx, data->minimap, 16, 16);
	mlx_image_to_window(data->mlx, data->ply_minimap, 16, 16);
}
