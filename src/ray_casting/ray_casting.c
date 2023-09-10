/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 20:22:01 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/09/10 14:22:49 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

// increment: separacion en radianes entre cado uno de los rayos
void	create_rays(t_data *data)
{
	data->num_rays = data->width;
	data->increment = (float)data->angle_vision / (float)data->width 
		* data->radian_conver;
	data->rays = malloc(sizeof(t_ray) * data->width);
	angle_rays(data);
}

void	angle_rays(t_data *data)
{
	int	i;

	i = 1;
	data->rays[0].angle = (data->ply_angle - data->angle_vision / 2) 
		* data->radian_conver;
	while (i < data->width)
	{
		data->rays[i].angle = data->rays[i -1].angle + data->increment;
		i++;
	}
}
