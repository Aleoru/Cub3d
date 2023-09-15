/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 03:49:41 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/09/15 05:26:37 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static float	ray_v_collision(t_data *data, int ray)
{
	float	dist;
	float	h;
	int		next;

	dist = 0;
	if (data->rays[ray].y_dir == 1)
	{
		next = (data->ply_pos.y / data->map_cell_size); //* data->map_cell_size;
		h = data->ply_pos.y - next * data->map_cell_size;
		printf("size:%d\n", data->map_cell_size);
		printf("ply_y:%f, next:%d, h:%f\n", data->ply_pos.y, next, h);
		dist = h / tan(data->rays[ray].angle);
		printf("dist:%f\n", dist);
		data->rays[ray].dest.x = data->ply_pos.x + dist;
		data->rays[ray].dest.y = data->ply_pos.y - h;
		printf("x:%f, y:%f\n", data->rays[ray].dest.x, data->rays[ray].dest.y);
		//draw_line(data->screen, data->ply_pos, data->rays[ray].dest, 0x66FF55FF);
	}
	return (dist);
}

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
