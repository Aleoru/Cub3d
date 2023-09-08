#include "../../inc/cub3D.h"

void	init_data(t_data *data)
{
	int				width;
	int				height;
	mlx_texture_t	*texture;

	width = 640;
	height = 640;
	data->radian_conversion = 3.1415926536 / 180;
	//create map
	data->map_cell_size = 64;
 	create_test_map(data, 10, 10);
	//player data
	data->ply_pos.x = 100;
	data->ply_pos.y = 100;
	data->ply_angle = 45;
	data->ply_speed = 1;
	data->ply_turn_speed = 1;
	//open window
	data->mlx = mlx_init(width, height, "cub3D", true);
	//creating images
	texture = mlx_load_png("./png/wall.png");
	data->wall = mlx_texture_to_image(data->mlx, texture);
	//draw map 2d
	draw_map(data, 10, 10, 64);
	//create player screen
	data->screen = mlx_new_image(data->mlx, width, height);
	mlx_image_to_window(data->mlx, data->screen, 0, 0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	(void)argc;
	(void)argv;
	init_data(&data);
	mlx_loop_hook(data.mlx, &hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (0);
}
