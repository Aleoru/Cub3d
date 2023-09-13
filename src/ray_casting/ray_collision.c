/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 03:49:41 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/09/13 19:17:35 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static float	ray_v_collision(t_data *data, int ray)
{
	float	dist;
	float	h;
	int		next;

	if (data->rays[ray].y_dir == 1)
	{
		next = (data->ply_pos.y / data->map_cell_size) * data->map_cell_size;
		h = data->ply_pos.y;
	}
	return (dist);
}

static float	ray_h_collision(t_data *data, int ray)
{
	float	dist;

	return (dist);
}

void	ray_collision(t_data *data, int ray)
{
	float	v_collision;
	float	h_collision;

	v_collision = ray_v_coll(data, ray);
	h_collision = ray_h_coll(data, ray);
	if (v_collision > h_collision)
		data->rays[ray].distance = h_collision;
	else
		data->rays[ray].distance = v_collision;
}
