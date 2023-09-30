/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 03:49:41 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/09/30 19:57:28 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

int	w_coll(t_data *data, float x, float y)
{
	int		x_cell;
	int		y_cell;

	if (x > data->width || x < 0 || y > data->height || y < 0)
		return (1);
	x_cell = (int)(x / data->cell_size);
	y_cell = (int)(y / data->cell_size);
	if (data->map[y_cell][x_cell] == '1')
		return (1);
	return (0);
}

void	ray_collision(t_data *data, int ray)
{
	float	v_collision;
	float	h_collision;

	v_collision = ray_v_collision(data, ray);
	h_collision = ray_h_collision(data, ray);
	if (v_collision > h_collision)
	{
		if (data->rays[ray].x_dir == -1)
			data->rays[ray].texture = NORTH;
		else
			data->rays[ray].texture = SOUTH;
	}
	else
	{
		if (data->rays[ray].y_dir == -1)
			data->rays[ray].texture = WEST;
		else
			data->rays[ray].texture = EAST;
	}
	if (v_collision > h_collision && h_collision != -1)
	{
		data->rays[ray].dest.x = data->rays[ray].aux.x;
		data->rays[ray].dest.y = data->rays[ray].aux.y;
		data->rays[ray].distance = h_collision;
	}
	else
	{
		data->rays[ray].distance = v_collision;
	}
}

