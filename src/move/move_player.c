#include "../../inc/cub3D.h"

static void	process_inputs(t_data *data)
{
	data->ply_x_axis = data->ply_inputs.right - data->ply_inputs.left;
	//data->ply_y_axis = data->ply_inputs.down - data->ply_inputs.up;
	data->ply_y_axis = data->ply_inputs.up - data->ply_inputs.down;
	data->ply_turn_dir = data->ply_inputs.turn_right
		- data->ply_inputs.turn_left;
}

static void	convert_radians(t_data *data)
{
	data->ply_angle += data->ply_turn_dir;
	if (data->ply_angle > 359)
		data->ply_angle = 0;
	else if (data->ply_angle < 0)
		data->ply_angle = 359;
	data->ply_radians = data->ply_angle * data->radian_conversion;
	printf("angle:%3f\n", data->ply_angle);
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

	process_inputs(data);
	convert_radians(data);
	//new.x = cos(data->ply_radians) * data->ply_speed * data->ply_y_axis;
	//new.y = sin(data->ply_radians) * data->ply_speed * data->ply_y_axis;
	if (data->ply_y_axis != 0)
	{
		new.x = cos(angle(data)) * data->ply_speed;
		new.y = sin(angle(data)) * data->ply_speed;
		data->ply_pos.x += new.x;
		data->ply_pos.y -= new.y;
	}
	//collision
}
