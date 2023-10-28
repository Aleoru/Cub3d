/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:54:21 by aoropeza          #+#    #+#             */
/*   Updated: 2023/10/28 03:00:16 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3D_bonus.h"

/* void	ft_leaks(void)
{
	system("leaks -q 'cub3D'");
} */

void	init_data(t_data *data)
{
	data->width = 1200;
	data->height = 720;
	data->radian_conver = 3.1415926536 / 180;
	data->ply_inputs.m_turn_right = 0;
	data->ply_inputs.m_turn_left = 0;
	data->ply_speed = 2;
	data->ply_turn_speed = 2;
	data->horizont = data->height / 2;
	data->wall_height = 32;
	data->mlx = mlx_init(data->width, data->height, "cub3D", true);
	draw_background(data, data->width, data->height);
	data->angle_vision = 60;
	create_rays(data);
	data->screen = mlx_new_image(data->mlx, data->width, data->height);
	mlx_image_to_window(data->mlx, data->screen, 0, 0);
	create_minimap(data, 8);
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
	mlx_delete_texture(texture);
	texture = mlx_load_png(data->level.so_path);
	data->img.so_wall = mlx_texture_to_image(data->mlx, texture);
	mlx_delete_texture(texture);
	texture = mlx_load_png(data->level.ea_path);
	data->img.ea_wall = mlx_texture_to_image(data->mlx, texture);
	mlx_delete_texture(texture);
	texture = mlx_load_png(data->level.we_path);
	data->img.we_wall = mlx_texture_to_image(data->mlx, texture);
	mlx_delete_texture(texture);
	upload_sprite_images(data);
}

//	atexit(ft_leaks);
int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 1)
	{
		ft_putstr_fd("Error\nMissing parameters\n", 2);
		return (2);
	}
	ft_bzero(&data, sizeof(t_data));
	data.cl_size = 32;
	data.n_sprites = 0;
	data.sprites = malloc(sizeof(t_sprite) * 10);
	init_map(&data, &data.level, argv[1]);
	init_data(&data);
	init_img(&data);
	mlx_set_cursor_mode(data.mlx, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(data.mlx, data.width / 2, data.height / 2);
	mlx_loop_hook(data.mlx, &hook, &data);
	mlx_cursor_hook(data.mlx, &cursor_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	free_level(&data, &data.level);
	free(data.rays);
	free(data.sprites);
	return (0);
}
