/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_player.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:42:59 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/10/09 19:31:08 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static int	collision_point(t_data *data, float x, float y)
{
	int		x_cell;
	int		y_cell;

	x_cell = (int)(x / data->cell_size);
	y_cell = (int)(y / data->cell_size);
	if (data->map[y_cell][x_cell] == '1')
		return (1);
	return (0);
}

int	collision_player(t_data *data, float x, float y)
{
	int	range;

	range = 2;
	if (collision_point(data, x + range, y))
		return (1);
	else if (collision_point(data, x - range, y))
		return (1);
	else if (collision_point(data, x, y + range))
		return (1);
	else if (collision_point(data, x, y - range))
		return (1);
	return (0);
}

/* int	collision_player(t_data *data, float x, float y)
{
	int		x_cell;
	int		y_cell;

	x_cell = (int)(x / data->cell_size);
	y_cell = (int)(y / data->cell_size);
	if (data->map[y_cell][x_cell] == '1')
		return (1);
	return (0);
}
 */