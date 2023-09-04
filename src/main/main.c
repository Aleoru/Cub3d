#include "../../inc/cub3D.h"

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_data data;
	int		width = 640;
	int		height = 640;
	
	data.mlx = mlx_init(width, height, "cub3D", true);
	create_test_map(&data, 10, 10);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (0);
}