/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:42:37 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/10/20 19:43:02 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3D_bonus.h"

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
				data->ply_pos.x = x * size + size / 2;
				data->ply_pos.y = y * size + size / 2;
			}
			x++;
		}
		y++;
	}
}

void	draw_background(t_data *data, int width, int heigth)
{
	int	x;
	int	y;

	data->background = mlx_new_image(data->mlx, width, heigth);
	mlx_image_to_window(data->mlx, data->background, 0, 0);
	y = 0;
	while (y <= heigth / 2)
	{
		x = -1;
		while (++x < width)
			mlx_put_pixel(data->background, x, y, data->level.c_color);
		y++;
	}
	while (y > heigth / 2 && y < heigth)
	{
		x = -1;
		while (++x < width)
			mlx_put_pixel(data->background, x, y, data->level.f_color);
		y++;
	}
}
