#include "../../inc/cub3D.h"

static void process_inputs(t_data *data)
{
	data->ply_x_axis = data->ply_inputs.right - data->ply_inputs.left;
	data->ply_y_axis = data->ply_inputs.down - data->ply_inputs.up;
	data->ply_turn_dir = data->ply_inputs.turn_right - data->ply_inputs.turn_left;
}

static void convert_radians(t_data *data)
{
	data->ply_angle += data->ply_turn_dir;
	if (data->ply_angle > 359)
		data->ply_angle = 0;
	else if (data->ply_angle < 0)
		data->ply_angle = 359;
	data->ply_radians = data->ply_angle * data->radian_conversion;
	printf("angle:%1f\n", data->ply_angle); 
}

void	move_player(t_data *data)
{
	t_point		new;

	process_inputs(data);
	convert_radians(data);
	new.x = cos(data->ply_radians) * data->ply_speed * data->ply_y_axis;
	new.y = sin(data->ply_radians) * data->ply_speed * data->ply_y_axis;
	//collision
	data->ply_pos.x += new.x;
	data->ply_pos.y += new.y;

}