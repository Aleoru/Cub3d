/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:42:08 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/10/26 06:09:01 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3D_bonus.h"

void	clear_image(mlx_image_t *image)
{
	ft_memset(image->pixels, 0, image->width * image->height * sizeof(int));
}

static void	draw_rays(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->num_rays)
	{
		height_calculation(data, i);
		i++;
	}
}

void	draw_screen(t_data *data)
{
	clear_image(data->screen);
	draw_rays(data);
	draw_sprites(data);
	draw_player_minimap(data, 4);
}

void	draw_big(t_data *data, int ray, int dist, t_point init)
{
	int		x;
	int		pixel;
	int		color;
	float	f_init;
	float	factor;

	x = 0;
	pixel = ((data->cl_size * data->cl_size) - data->cl_size
			+ data->rays[ray].pixel) * 4;
	color = get_color(get_texture(data, ray), pixel);
	f_init = (float)dist / data->cl_size;
	factor = f_init;
	while (x <= dist && f_init >= 1)
	{
		if (init.y - x >= 0 && init.y - x < data->height)
			mlx_put_pixel(data->screen, init.x, init.y - x, color);
		if ((float)x >= factor)
		{
			factor += f_init;
			pixel = pixel - (data->cl_size * 4);
			color = get_color(get_texture(data, ray), pixel);
		}
		x++;
	}
}

void	draw_small(t_data *data, int ray, int dist, t_point init)
{
	int		x;
	int		pixel;
	int		color;
	float	f_init;
	float	factor;

	x = 0;
	pixel = ((data->cl_size * data->cl_size) - data->cl_size
			+ data->rays[ray].pixel) * 4;
	color = get_color(get_texture(data, ray), pixel);
	f_init = (float)dist / data->cl_size;
	factor = 0;
	while ((int)factor < data->cl_size && f_init < 1)
	{
		factor += f_init;
		if (init.y - x >= 0 && init.y - x <= data->height)
			mlx_put_pixel(data->screen, init.x, init.y - (int)factor, color);
		color = get_color(get_texture(data, ray), pixel);
		pixel = pixel - (data->cl_size * 4);
		if (pixel < 0)
			break ;
	}
}
