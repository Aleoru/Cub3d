/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:54:21 by aoropeza          #+#    #+#             */
/*   Updated: 2023/09/25 19:29:53 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	ft_leaks(void)
{
	system("leaks -q 'cub3D'");
}

void	init_data(t_data *data)
{
	mlx_texture_t	*texture;

	data->map_cell_size = 64;
	data->width = data->map_cell_size * (data->level.size_x + 1);
	data->height = data->map_cell_size * (data->level.size_y + 2);
	data->radian_conver = 3.1415926536 / 180;
	//create map
 	//create_test_map(data, 10, 10);
	//player data
/* 	data->ply_pos.x = 100.5;
	data->ply_pos.y = 100.5; */
	data->ply_angle = 60;
	data->ply_speed = 1;
	data->ply_turn_speed = 1;
	//open window
	data->mlx = mlx_init(data->width, data->height, "cub3D", true);
	//creating images
	texture = mlx_load_png("./assets/png/wall.png");
	data->wall = mlx_texture_to_image(data->mlx, texture);
	//draw map 2d
	draw_map(data, data->level.size_x, data->level.size_y, data->map_cell_size);
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

	if (argc == 1)	//Añadir exit_error
		return (0);
	ft_bzero(&data, sizeof(t_data));
	init_map(&data, &data.level, argv[1]);
	init_data(&data);
	mlx_loop_hook(data.mlx, &hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	//free(data.rays);

	return (0);
}
