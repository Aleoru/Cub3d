/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_collision.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 23:31:52 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/09/24 23:32:12 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h" 

float	ray_h_collision(t_data *data, int ray)
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