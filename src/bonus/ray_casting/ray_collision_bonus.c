/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 03:49:41 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/11/05 21:02:57 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3D_bonus.h"

int	w_coll(t_data *data, float x, float y)
{
	int		x_cell;
	int		y_cell;

	x_cell = (int)(x / data->cl_size);
	y_cell = (int)(y / data->cl_size);
	if (x_cell > data->level.size_x || x_cell < 0
		|| y_cell > data->level.size_y || y_cell < 0)
		return (1);
	if (data->map[y_cell][x_cell] == '1')
		return (1);
	else if (data->map[y_cell][x_cell] == 'D')
		return (2);
	return (0);
}

static void	read_dir(t_data *data, int ray, float v, float h)
{
	if (v > h)
	{
		if (data->rays[ray].is_door == 1)
			data->rays[ray].texture = DOOR;
		else if (data->rays[ray].x_dir == -1)
			data->rays[ray].texture = WEST;
		else
			data->rays[ray].texture = EAST;
		data->rays[ray].pixel = (int)data->rays[ray].dest.y % data->cl_size;
	}
	else
	{
		if (data->rays[ray].is_door == 1)
			data->rays[ray].texture = DOOR;
		else if (data->rays[ray].y_dir == -1)
			data->rays[ray].texture = SOUTH;
		else
			data->rays[ray].texture = NORTH;
		data->rays[ray].pixel = (int)data->rays[ray].dest.x % data->cl_size;
	}
}

void	ray_collision(t_data *data, int ray)
{
	float	v_collision;
	float	h_collision;

	data->rays[ray].h_door = 0;
	data->rays[ray].v_door = 0;
	data->rays[ray].is_door = 0;
	v_collision = ray_v_collision(data, ray);
	h_collision = ray_h_collision(data, ray);
	if (v_collision > h_collision && h_collision != -1)
	{
		data->rays[ray].dest.x = data->rays[ray].aux.x;
		data->rays[ray].dest.y = data->rays[ray].aux.y;
		data->rays[ray].distance = h_collision;
		if (data->rays[ray].h_door == 1)
			data->rays[ray].is_door = 1;
	}
	else
	{
		data->rays[ray].distance = v_collision;
		if (data->rays[ray].v_door == 1)
			data->rays[ray].is_door = 1;
	}
	read_dir(data, ray, v_collision, h_collision);
}
