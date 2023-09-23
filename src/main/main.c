#include "../../inc/cub3D.h"

void	init_data(t_data *data)
{
	mlx_texture_t	*texture;

	data->width = 640;
	data->height = 640;
	data->radian_conver = 3.1415926536 / 180;
	//create map
	data->map_cell_size = 64;
 	create_test_map(data, 10, 10);
	//player data
	data->ply_pos.x = 100.5;
	data->ply_pos.y = 100.5;
	data->ply_angle = 60;
	data->ply_speed = 1;
	data->ply_turn_speed = 1;
	//open window
	data->mlx = mlx_init(data->width, data->height, "cub3D", true);
	//creating images
	texture = mlx_load_png("./png/wall.png");
	data->wall = mlx_texture_to_image(data->mlx, texture);
	//draw map 2d
	draw_map(data, 10, 10, 64);
	//create rays
	data->angle_vision = 60;
	create_rays(data);
	//create player screen
	data->screen = mlx_new_image(data->mlx, data->width, data->height);
	mlx_image_to_window(data->mlx, data->screen, 0, 0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	(void)argc;
	(void)argv;
	init_data(&data);
	float debug;
	debug = -36 * tan(135 * data.radian_conver);
	printf("debug: %f\n", debug);
	mlx_loop_hook(data.mlx, &hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	//free(data.rays);

	return (0);
}
