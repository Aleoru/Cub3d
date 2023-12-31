/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 10:31:38 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/11/07 19:09:45 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3D_bonus.h"

static void	process_inputs(t_data *data)
{
	data->ply_x_axis = data->ply_inputs.left - data->ply_inputs.right;
	data->ply_y_axis = data->ply_inputs.up - data->ply_inputs.down;
	data->ply_turn_dir = (data->ply_inputs.turn_left
			+ data->ply_inputs.m_turn_left)
		- (data->ply_inputs.turn_right
			+ data->ply_inputs.m_turn_right);
	if (data->ply_turn_dir > 0)
		data->ply_turn_dir = 1;
	else if (data->ply_turn_dir < 0)
		data->ply_turn_dir = -1;
}

static void	angle_move(t_data *data)
{
	data->ply_angle_mv = data->ply_angle;
	if (data->ply_y_axis == 1)
	{
		if (data->ply_x_axis == 1)
			data->ply_angle_mv += 45;
		else if (data->ply_x_axis == -1)
			data->ply_angle_mv += -45;
	}
	else if (data->ply_y_axis == -1)
	{
		if (data->ply_x_axis == 1)
			data->ply_angle_mv += 135;
		else if (data->ply_x_axis == -1)
			data->ply_angle_mv += -135;
		else
			data->ply_angle_mv += 180;
	}
	else if (data->ply_y_axis == 0)
	{
		if (data->ply_x_axis == 1)
			data->ply_angle_mv += 90;
		else if (data->ply_x_axis == -1)
			data->ply_angle_mv += -90;
	}
}

void	checker_point_pos(t_data *data, float range)
{
	t_point	new;

	new.x = cos(data->ply_radians) * range;
	new.y = sin(data->ply_radians) * range;
	data->check_point.x = data->ply_pos.x + new.x;
	data->check_point.y = data->ply_pos.y - new.y;
}

static void	convert_radians(t_data *data)
{
	data->ply_angle += data->ply_turn_dir * data->ply_turn_speed;
	if (data->ply_angle >= 360)
		data->ply_angle -= 360;
	else if (data->ply_angle < 0)
		data->ply_angle += 360;
	angle_move(data);
	data->ply_radians = data->ply_angle_mv * data->radian_conver;
	angle_rays(data);
}

void	move_player(t_data *data)
{
	t_point		new;
	t_point		next;

	process_inputs(data);
	convert_radians(data);
	if (data->ply_y_axis != 0 || data->ply_x_axis != 0)
	{
		new.x = cos(data->ply_radians) * data->ply_speed;
		new.y = sin(data->ply_radians) * data->ply_speed;
		next.x = data->ply_pos.x + new.x;
		next.y = data->ply_pos.y - new.y;
		checker_point_pos(data, 31);
		if (collision_player(data, next.x, next.y) == 0)
		{
			data->ply_pos.x += new.x;
			data->ply_pos.y -= new.y;
			if (data->open_door == 1
				&& outside_door(data, data->ply_pos.x, data->ply_pos.y))
			{
				data->map[data->door_y][data->door_x] = 'D';
				data->open_door = 0;
			}
		}
	}
}
