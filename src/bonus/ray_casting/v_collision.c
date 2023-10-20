/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_collision.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 23:25:47 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/10/20 19:30:57 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3D_bonus.h" 

static float	v_coll_up(t_data *data, int ray)
{
	t_point	init;
	float	h;
	float	w;
	int		next;

	init.x = data->ply_pos.x;
	init.y = data->ply_pos.y;
	while (w_coll(data, init.x, init.y -1) == 0)
	{
		next = (init.y / data->cl_size);
		h = init.y - next * data->cl_size;
		if (h == 0)
			h = data->cl_size;
		w = h / tan(data->rays[ray].angle);
		data->rays[ray].dest.x = init.x + w;
		data->rays[ray].dest.y = init.y - h;
		init.x = data->rays[ray].dest.x;
		init.y = data->rays[ray].dest.y;
	}
	h = data->ply_pos.y - data->rays[ray].dest.y;
	w = data->ply_pos.x - data->rays[ray].dest.x;
	return (sqrt((w * w) + (h * h)));
}

static float	v_coll_down(t_data *data, int ray)
{
	t_point	init;
	float	h;
	float	w;
	int		next;

	init.x = data->ply_pos.x;
	init.y = data->ply_pos.y;
	while (w_coll(data, init.x, init.y) == 0)
	{
		next = (init.y / data->cl_size);
		h = init.y - (next + 1) * data->cl_size;
		w = h / tan(data->rays[ray].angle);
		data->rays[ray].dest.x = init.x + w;
		data->rays[ray].dest.y = init.y - h;
		init.x = data->rays[ray].dest.x;
		init.y = data->rays[ray].dest.y;
	}
	h = data->ply_pos.y - data->rays[ray].dest.y;
	w = data->ply_pos.x - data->rays[ray].dest.x;
	return (sqrt((w * w) + (h * h)));
}

float	ray_v_collision(t_data *data, int ray)
{
	if (data->rays[ray].y_dir == 1)
		return (v_coll_up(data, ray));
	else if (data->rays[ray].y_dir == -1)
		return (v_coll_down(data, ray));
	return (-1);
}
