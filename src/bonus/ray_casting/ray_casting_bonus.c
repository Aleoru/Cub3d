/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 20:22:01 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/10/20 20:26:28 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3D_bonus.h"

void	create_rays(t_data *data)
{
	data->num_rays = data->width;
	data->increment = (float)data->angle_vision / (float)data->width
		* data->radian_conver;
	data->rays = malloc(sizeof(t_ray) * data->width);
	calculate_hipotenuses(data);
	angle_rays(data);
}

float	normalized_radians(float radians)
{
	float	normalized;

	if (radians > (2 * 3.1415))
		normalized = radians - (2 * 3.1415);
	else if (radians < 0)
		normalized = radians + (2 * 3.1415);
	else
		normalized = radians;
	return (normalized);
}

void	ray_dir(t_data *data, int i)
{
	if (sin(data->rays[i].angle) > 0)
		data->rays[i].y_dir = 1;
	else if (sin(data->rays[i].angle) < 0)
		data->rays[i].y_dir = -1;
	else
		data->rays[i].y_dir = 0;
	if (cos(data->rays[i].angle) > 0)
		data->rays[i].x_dir = 1;
	else if (cos(data->rays[i].angle) < 0)
		data->rays[i].x_dir = -1;
	else
		data->rays[i].x_dir = 0;
}

void	angle_rays(t_data *data)
{
	int	i;

	i = 1;
	data->rays[0].angle = (data->ply_angle - data->angle_vision / 2)
		* data->radian_conver;
	ray_dir(data, 0);
	ray_collision(data, 0);
	while (i < data->width)
	{
		data->rays[i].angle = normalized_radians(data->rays[i -1].angle
				+ data->increment);
		ray_dir(data, i);
		ray_collision(data, i);
		i++;
	}
}
