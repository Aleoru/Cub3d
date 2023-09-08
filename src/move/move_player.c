/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 10:31:38 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/09/08 12:03:42 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	process_inputs(t_data *data)
{
	data->ply_x_axis = data->ply_inputs.right - data->ply_inputs.left;
	//data->ply_y_axis = data->ply_inputs.down - data->ply_inputs.up;
	data->ply_y_axis = data->ply_inputs.up - data->ply_inputs.down;
	data->ply_turn_dir = data->ply_inputs.turn_left - data->ply_inputs.turn_right;
}

static void	convert_radians(t_data *data)
{
	data->ply_angle += data->ply_turn_dir * data->ply_turn_speed;
	if (data->ply_angle >= 360)
		data->ply_angle -= 360;
	else if (data->ply_angle < 0)
		data->ply_angle += 360;
	data->ply_radians = data->ply_angle * data->radian_conversion;
	//printf("angle:%.0f\n", data->ply_angle);
}

float	angle(t_data *data)
{
	data->ply_angle_mv = data->ply_angle;
	if (data->ply_y_axis == -1)
		data->ply_angle_mv += 180;
	if (data->ply_x_axis == 1)
		data->ply_angle_mv += -90;
	if (data->ply_x_axis == -1)
		data->ply_angle_mv += 90;
	return (data->ply_angle_mv * data->radian_conversion);
}

void	move_player(t_data *data)
{
	t_point		new;
	t_point		next;

	process_inputs(data);
	convert_radians(data);
	//new.x = cos(data->ply_radians) * data->ply_speed * data->ply_y_axis;
	//new.y = sin(data->ply_radians) * data->ply_speed * data->ply_y_axis;
	if (data->ply_y_axis != 0)
	{
		new.x = cos(angle(data)) * data->ply_speed;
		new.y = sin(angle(data)) * data->ply_speed;
		next.x = data->ply_pos.x + new.x;
		next.y = data->ply_pos.y - new.y;
		if (collision_player(data, next.x, next.y) == 0)
		{
			data->ply_pos.x += new.x;
			data->ply_pos.y -= new.y;
		}
	}
}
