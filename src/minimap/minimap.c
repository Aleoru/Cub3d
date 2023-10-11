/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 03:18:17 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/10/11 18:08:42 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	create_minimap(t_data *data, int cell_size)
{
	t_point	init;
	int		x;
	int		y;
	int		c;

	c = 0x000000FF;
	data->minimap = mlx_new_image(data->mlx, data->level.size_x
			* cell_size, data->level.size_y * (cell_size + 1));
	y = 0;
	while (y < data->level.size_y + 1)
	{
		x = 0;
		while (x < data->level.size_x)
		{
			if (data->map[y][x] == '1')
			{
				init.x = x * cell_size;
				init.y = y * cell_size;
				draw_cell(data->minimap, init, cell_size, c);
			}
			x++;
		}
		y++;
	}
}
