/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 03:49:41 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/09/13 04:20:42 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static float	ray_v_collision(t_data, int ray)
{
	float	dist;

	return (dist);
}

static float	ray_h_collision(t_data, int ray)
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