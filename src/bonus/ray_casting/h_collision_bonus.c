/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_collision_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 23:31:52 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/11/05 21:02:50 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3D_bonus.h"

static float	h_coll_right(t_data *data, int ray)
{
	t_point	init;
	float	h;
	float	w;
	int		next;

	init.x = data->ply_pos.x;
	init.y = data->ply_pos.y;
	while (w_coll(data, init.x, init.y) == 0)
	{
		next = (init.x / data->cl_size);
		w = ((next + 1) * data->cl_size) - init.x;
		h = w * tan(data->rays[ray].angle);
		data->rays[ray].aux.x = init.x + w;
		data->rays[ray].aux.y = init.y - h;
		init.x = data->rays[ray].aux.x;
		init.y = data->rays[ray].aux.y;
	}
	if (w_coll(data, init.x, init.y) == 2)
		data->rays[ray].h_door = 1;
	h = data->ply_pos.y - data->rays[ray].aux.y;
	w = data->ply_pos.x - data->rays[ray].aux.x;
	return (sqrt((w * w) + (h * h)));
}

static float	h_coll_left(t_data *data, int ray)
{
	t_point	init;
	float	h;
	float	w;
	int		next;

	init.x = data->ply_pos.x;
	init.y = data->ply_pos.y;
	while (w_coll(data, init.x - 1, init.y) == 0)
	{
		next = (init.x / data->cl_size);
		w = (next * data->cl_size) - init.x;
		if (w == 0)
			w = data->cl_size * -1;
		h = w * tan(data->rays[ray].angle);
		data->rays[ray].aux.x = init.x + w;
		data->rays[ray].aux.y = init.y - h;
		init.x = data->rays[ray].aux.x;
		init.y = data->rays[ray].aux.y;
	}
	if (w_coll(data, init.x - 1, init.y) == 2)
		data->rays[ray].h_door = 1;
	h = data->ply_pos.y - data->rays[ray].aux.y;
	w = data->ply_pos.x - data->rays[ray].aux.x;
	return (sqrt((w * w) + (h * h)));
}

float	ray_h_collision(t_data *data, int ray)
{
	if (data->rays[ray].x_dir == 1)
		return (h_coll_right(data, ray));
	else if (data->rays[ray].x_dir == -1)
		return (h_coll_left(data, ray));
	return (-1);
}
