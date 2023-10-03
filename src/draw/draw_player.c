/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:42:08 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/10/03 08:22:36 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	clear_image(mlx_image_t *image)
{
	ft_memset(image->pixels, 0, image->width * image->height * sizeof(int));
}

/* void	draw_rays(t_data *data)		//Borrar luego
{
	int		i;
	int		dis;
	int		c;
	t_point	end;

	i = 0;
	dis = 50;
	c = 0x66FF66FF;
	while (i < data->num_rays)
	{
		end.x = data->ply_pos.x + cos(data->rays[i].angle) * dis;
		end.y = data->ply_pos.y - sin(data->rays[i].angle) * dis;
		draw_line(data->screen, data->ply_pos, end, c);
		i++;
	}
} */

void	draw_rays2(t_data *data)
{
	int		i;
	//int		c;

	i = 0;
	//c = 0x66FF66FF;
	while (i < data->num_rays)
	{
/* 		if (data->rays[i].dest.x > 0 && data->rays[i].dest.x < data->width
			&& data->rays[i].dest.y > 0 && data->rays[i].dest.y < data->height)
			draw_line(data->screen, data->ply_pos, data->rays[i].dest, c); */
		height_calculation(data, i);
		i++;
	}
}

void	draw_player(t_data *data)
{
	//int		c;
	//int		dis;
	//t_point	dir;

	//c = 0x66FFFFFF;
	//dis = 15;
	clear_image(data->screen);
	//draw_circle(data->screen, data->ply_pos, dis, c);
	//mlx_put_pixel(data->screen, data->ply_pos.x, data->ply_pos.y, c);
	//dir.x = data->ply_pos.x + cos(data->ply_angle * data->radian_conver) * dis;
	//dir.y = data->ply_pos.y - sin(data->ply_angle * data->radian_conver) * dis;
	draw_rays2(data);
	//draw_line(data->screen, data->ply_pos, dir, c);
	//draw_line(data->screen, data->ply_pos, data->rays[319].dest, c);
}
