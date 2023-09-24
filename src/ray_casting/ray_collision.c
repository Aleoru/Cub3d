/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 03:49:41 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/09/24 20:08:26 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static int	w_coll(t_data *data, float x, float y)
{
	int		x_cell;
	int		y_cell;

	if (x > data->width || x < 0 || y > data->height || y < 0)
		return (1);
	x_cell = (int)(x / data->map_cell_size);
	y_cell = (int)(y / data->map_cell_size);
	if (data->map[y_cell][x_cell] == '1')
		return (1);
	return (0);
}

static float	ray_v_collision(t_data *data, int ray)
{
	t_point	init;
	float	h;
	float	w;
	int		next;
	int		no_collision;

	no_collision = 1;
	init.x = data->ply_pos.x;
	init.y = data->ply_pos.y;
	w = 0;
	if (data->rays[ray].y_dir == 1)
	{
		while (no_collision)
		{
			next = (init.y / data->map_cell_size);
			h = init.y - next * data->map_cell_size;
			if (h == 0)
				h = data->map_cell_size;
			w = h / tan(data->rays[ray].angle);
			data->rays[ray].dest.x = init.x + w;
			data->rays[ray].dest.y = init.y - h;
			if (w_coll(data, data->rays[ray].dest.x, data->rays[ray].dest.y -1))
				no_collision = 0;
			else
			{
				init.x = data->rays[ray].dest.x;
				init.y = data->rays[ray].dest.y;
			}
		}
		h = data->ply_pos.y - data->rays[ray].dest.y;
		w = data->ply_pos.x - data->rays[ray].dest.x;
		return (sqrt((w * w) + (h * h)));
	}
	else if (data->rays[ray].y_dir == -1)
	{
		while (no_collision)
		{
			next = (init.y / data->map_cell_size);
			h = init.y - (next + 1) * data->map_cell_size;
			w = h / tan(data->rays[ray].angle);
			data->rays[ray].dest.x = init.x + w;
			data->rays[ray].dest.y = init.y - h;
			if (w_coll(data, data->rays[ray].dest.x, data->rays[ray].dest.y))
				no_collision = 0;
			else
			{
				init.x = data->rays[ray].dest.x;
				init.y = data->rays[ray].dest.y;
			}
		}
		h = data->ply_pos.y - data->rays[ray].dest.y;
		w = data->ply_pos.x - data->rays[ray].dest.x;
		return (sqrt((w * w) + (h * h)));
	}
	return (-1);
}

static float	ray_h_collision(t_data *data, int ray)
{
	t_point	init;
	float	h;
	float	w;
	int		next;
	int		no_collision;

	no_collision = 1;
	init.x = data->ply_pos.x;
	init.y = data->ply_pos.y;
	w = 0;
	if (data->rays[ray].x_dir == 1)
	{
		while (no_collision)
		{
			next = (init.x / data->map_cell_size);
			w = ((next + 1) * data->map_cell_size) - init.x;
			h = w * tan(data->rays[ray].angle);
			data->rays[ray].aux.x = init.x + w;
			data->rays[ray].aux.y = init.y - h;
			if (w_coll(data, data->rays[ray].aux.x, data->rays[ray].aux.y))
				no_collision = 0;
			else
			{
				init.x = data->rays[ray].aux.x;
				init.y = data->rays[ray].aux.y;
			}
		}
		h = data->ply_pos.y - data->rays[ray].aux.y;
		w = data->ply_pos.x - data->rays[ray].aux.x;
		return (sqrt((w * w) + (h * h)));
	}
	else if (data->rays[ray].x_dir == -1)
	{
		while (no_collision)
		{
			next = (init.x / data->map_cell_size);
			w = (next * data->map_cell_size) - init.x;
			if (w == 0)
				w = data->map_cell_size * -1;
			h = w * tan(data->rays[ray].angle);
			data->rays[ray].aux.x = init.x + w;
			data->rays[ray].aux.y = init.y - h;
			if (w_coll(data, data->rays[ray].aux.x - 1, data->rays[ray].aux.y))
				no_collision = 0;
			else
			{
				init.x = data->rays[ray].aux.x;
				init.y = data->rays[ray].aux.y;
			}
		}
		h = data->ply_pos.y - data->rays[ray].aux.y;
		w = data->ply_pos.x - data->rays[ray].aux.x;
		return (sqrt((w * w) + (h * h)));
	}
	return (-1);
}

void	ray_collision(t_data *data, int ray)
{
	float	v_collision;
	float	h_collision;

	v_collision = ray_v_collision(data, ray);
	h_collision = ray_h_collision(data, ray);
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

