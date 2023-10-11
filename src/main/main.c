/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:54:21 by aoropeza          #+#    #+#             */
/*   Updated: 2023/10/11 05:42:27 by fgalan-r         ###   ########.fr       */
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

	data->width = 1200;		//data->cl_size * (data->level.size_x + 1);
	data->height = 720;		//data->cl_size * (data->level.size_y + 2);
	data->radian_conver = 3.1415926536 / 180;
//	data->ply_angle = 270;
	data->ply_speed = 2;
	data->ply_turn_speed = 1;
	data->horizont = data->height / 2;
	data->wall_height = 35;
	//open window
	data->mlx = mlx_init(data->width, data->height, "cub3D", true);
	draw_background(data, data->width, data->height);
	//creating images
	texture = mlx_load_png("./assets/png/wall.png");
	data->wall = mlx_texture_to_image(data->mlx, texture);
	//draw map 2d
	//draw_map(data, data->level.size_x, data->level.size_y, data->cl_size);
	//create rays
	data->angle_vision = 60;
	create_rays(data);
	//create player screen
	data->screen = mlx_new_image(data->mlx, data->width, data->height);
	mlx_image_to_window(data->mlx, data->screen, 0, 0);
	//minimap
	create_minimap(data, 15);
	mlx_image_to_window(data->mlx, data->minimap, 32, 32);
	//draw_cell(data->minimap, init, 10, color);
}

void	init_img(t_data *data)
{
	mlx_texture_t	*texture;

	data->level.no_path = delete_nl(data->level.no_path);
	data->level.so_path = delete_nl(data->level.so_path);
	data->level.ea_path = delete_nl(data->level.ea_path);
	data->level.we_path = delete_nl(data->level.we_path);
	if (check_img(&data->level) == -1)
		exit_error(data, "Error\nInvalid image path\n", 2);
	texture = mlx_load_png(data->level.no_path);
	data->img.no_wall = mlx_texture_to_image(data->mlx, texture);
	free(texture);
	texture = mlx_load_png(data->level.so_path);
	data->img.so_wall = mlx_texture_to_image(data->mlx, texture);
	free(texture);
	texture = mlx_load_png(data->level.ea_path);
	data->img.ea_wall = mlx_texture_to_image(data->mlx, texture);
	free(texture);
	texture = mlx_load_png(data->level.we_path);
	data->img.we_wall = mlx_texture_to_image(data->mlx, texture);
	free(texture);
}

int	main(int argc, char **argv)
{
	//atexit(ft_leaks);
	t_data	data;

	if (argc == 1)
	{
		ft_putstr_fd("Error\nMissing parameters\n", 2);
		return (2);
	}
	ft_bzero(&data, sizeof(t_data));
	data.cl_size = 64;
	init_map(&data, &data.level, argv[1]);
	init_data(&data);
	init_img(&data);
	mlx_loop_hook(data.mlx, &hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	printf("x: %d, y: %d\n", data.level.size_x, data.level.size_y);
	free_level(&data, &data.level);
	free(data.rays);

	return (0);
}
