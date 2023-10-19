/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:42:43 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/10/19 18:58:39 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	reset_inputs(t_data *data)
{
	data->ply_inputs.up = 0;
	data->ply_inputs.down = 0;
	data->ply_inputs.left = 0;
	data->ply_inputs.right = 0;
	data->ply_inputs.turn_left = 0;
	data->ply_inputs.turn_right = 0;
}

void	hook(void *param)
{
	t_data	*data;

	data = param;
	reset_inputs(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		data->ply_inputs.up = 1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		data->ply_inputs.down = 1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		data->ply_inputs.left = 1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		data->ply_inputs.right = 1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->ply_inputs.turn_left = 1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->ply_inputs.turn_right = 1;
	move_player(data);
	draw_screen(data);
}

void	cursor_hook(double xdelta, double ydelta, void *param)
{
	t_data	*data;

	data = param;
	(void)ydelta;
	data->ply_inputs.m_turn_right = 0;
	data->ply_inputs.m_turn_left = 0;
	if (xdelta < (data->width / 2) - 10)
	{
		data->ply_inputs.m_turn_left = 1;
		puts("Sliiiide to the left!");
	}
	else if (xdelta > (data->width / 2) + 10)
	{
		data->ply_inputs.m_turn_right = 1;
		puts("Sliiiide to the right!");
	}
	else
	{
		data->ply_inputs.m_turn_left = 0;
		data->ply_inputs.m_turn_right = 0;
	}
	mlx_set_mouse_pos(data->mlx, data->width / 2, data->height / 2);
}
