/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_player_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:42:59 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/11/05 21:11:08 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3D_bonus.h"

static int	collision_point(t_data *data, float x, float y)
{
	int		x_cell;
	int		y_cell;

	x_cell = (int)(x / data->cl_size);
	y_cell = (int)(y / data->cl_size);
	if (data->map[y_cell][x_cell] == 'D')
	{
		data->map[y_cell][x_cell] = '0';
		data->open_door = 1;
		data->door_x = x_cell;
		data->door_y = y_cell;
	}
	if (data->map[y_cell][x_cell] == '1')
		return (1);
	return (0);
}

int	collision_player(t_data *data, float x, float y)
{
	int	range;

	range = 2;
	if (collision_point(data, x + range, y))
		return (1);
	else if (collision_point(data, x - range, y))
		return (1);
	else if (collision_point(data, x, y + range))
		return (1);
	else if (collision_point(data, x, y - range))
		return (1);
	return (0);
}

int	outside_door(t_data *data, float x, float y)
{
	int		x_cell;
	int		y_cell;

	if (data->open_door == 1)
	{
		x_cell = (int)(x / data->cl_size);
		y_cell = (int)(y / data->cl_size);
		if (x_cell == data->door_x && y_cell == data->door_y)
			return (0);
	}
	return (1);
}
