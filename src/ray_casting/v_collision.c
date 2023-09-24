/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_collision.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 23:25:47 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/09/24 23:31:23 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h" 

float	ray_v_collision(t_data *data, int ray)
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