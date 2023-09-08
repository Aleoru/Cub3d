/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 20:22:01 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/09/08 20:45:05 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	create_rays(t_data *data)
{
	int		i;
	float	angle;
	float	increment;

	i = 0;
	increment = data->angle_vision / data->width;
	angle = data->ply_angle - data->angle_vision / 2;
	data->rays = malloc(sizeof(t_ray) * data->width);

}
