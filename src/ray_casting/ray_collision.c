/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 03:49:41 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/09/16 04:30:38 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static int	wall_collision(t_data *data, float x, float y)
{
	int		x_cell;
	int		y_cell;

	x_cell = (int)(x / data->map_cell_size);
	y_cell = (int)(y / data->map_cell_size);
	if (data->map[y_cell][x_cell] == '1')
		return (1);
	return (0);
}

static float	ray_v_collision(t_data *data, int ray)
{
	t_point	init;
	float	dist;
	float	h;
	int		next;
	int		no_collision;

	no_collision = 1;
	init.x = data->ply_pos.x;
	init.y = data->ply_pos.y;
	dist = 0;
	if (data->rays[ray].y_dir == 1)
	{
		while (no_collision)
		{
			next = (init.y / data->map_cell_size);
			h = init.y - next * data->map_cell_size;
			if (h == 0)
				h = data->map_cell_size;
			//printf("size:%d\n", data->map_cell_size);
			//printf("ply_y:%f, next:%d, h:%f\n", init.y, next, h);
			dist = h / tan(data->rays[ray].angle);
			//printf("dist:%f\n", dist);
			data->rays[ray].dest.x = init.x + dist;
			data->rays[ray].dest.y = init.y - h;
			//printf("x:%f, y:%f\n", data->rays[ray].dest.x, data->rays[ray].dest.y);
			if (wall_collision(data, data->rays[ray].dest.x,
					data->rays[ray].dest.y - 1))
					no_collision = 0;
			else
			{
				init.x = data->rays[ray].dest.x;
				init.y = data->rays[ray].dest.y;
			}
		}
	}
	else if (data->rays[ray].y_dir == -1)
	{
		next = (init.y / data->map_cell_size);
		h = data->ply_pos.y - (next + 1) * data->map_cell_size;
		dist = h / tan(data->rays[ray].angle);
		data->rays[ray].dest.x = data->ply_pos.x + dist;
		data->rays[ray].dest.y = data->ply_pos.y - h;
		if (wall_collision(data, data->rays[ray].dest.x,
				data->rays[ray].dest.y))
			printf("collision down\n");
		else
			printf("no collision down\n");
	}

	return (dist);
}

/*
static float	ray_v_collision(t_data *data, int ray)
{
	t_point	init;
	float	dist;
	float	h;
	int		next;

	init.x = data->ply_pos.x;
	init.y = data->ply_pos.y;
	dist = 0;
	next = (data->ply_pos.y / data->map_cell_size);
	if (data->rays[ray].y_dir == 1)
	{
		h = data->ply_pos.y - next * data->map_cell_size;
		printf("size:%d\n", data->map_cell_size);
		printf("ply_y:%f, next:%d, h:%f\n", data->ply_pos.y, next, h);
		dist = h / tan(data->rays[ray].angle);
		printf("dist:%f\n", dist);
		data->rays[ray].dest.x = data->ply_pos.x + dist;
		data->rays[ray].dest.y = data->ply_pos.y - h;
		printf("x:%f, y:%f\n", data->rays[ray].dest.x, data->rays[ray].dest.y);
		if (wall_collision(data, data->rays[ray].dest.x,
				data->rays[ray].dest.y - 1))
			printf("collision up\n");
		else
			printf("no collision up\n");
	}
	else if (data->rays[ray].y_dir == -1)
	{
		h = data->ply_pos.y - (next + 1) * data->map_cell_size;
		dist = h / tan(data->rays[ray].angle);
		data->rays[ray].dest.x = data->ply_pos.x + dist;
		data->rays[ray].dest.y = data->ply_pos.y - h;
		if (wall_collision(data, data->rays[ray].dest.x,
				data->rays[ray].dest.y))
			printf("collision down\n");
		else
			printf("no collision down\n");
	}

	return (dist);
}
*/

static float	ray_h_collision(t_data *data, int ray)
{
	float	dist;

	(void)data;
	(void)ray;
	dist = 0;
	return (dist);
}

void	ray_collision(t_data *data, int ray)
{
	float	v_collision;
	float	h_collision;

	v_collision = ray_v_collision(data, ray);
	h_collision = ray_h_collision(data, ray);
	if (v_collision > h_collision)
		data->rays[ray].distance = h_collision;
	else
		data->rays[ray].distance = v_collision;
}
