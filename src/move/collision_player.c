/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_player.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:42:59 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/09/08 12:04:28 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

int	collision_player(t_data *data, float x, float y)
{
	int		x_cell;
	int		y_cell;

	x_cell = (int)(x / data->map_cell_size);
	y_cell = (int)(y / data->map_cell_size);
	printf("debug collision x:%d, y:%d \n", x_cell, y_cell);
	if (data->map[y_cell][x_cell] == '1')
		return (1);
	return (0);
}
