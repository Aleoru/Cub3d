#include "../../inc/cub3D.h"

static void process_inputs(t_data *data)
{
	data->ply_x_axis = data->ply_inputs.right - data->ply_inputs.left;
	data->ply_y_axis = data->ply_inputs.down - data->ply_inputs.up;
	data->ply_turn_dir = data->ply_inputs.turn_right - data->ply_inputs.turn_left;
}

void	move_player(t_data *data)
{
	process_inputs(data);
	data->ply_pos.x += data->ply_speed * data->ply_x_axis;
	data->ply_pos.y += data->ply_speed * data->ply_y_axis;
}