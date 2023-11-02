/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_of_view_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 04:22:29 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/11/02 20:36:19 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3D_bonus.h"

int	get_color(mlx_image_t *img, int p)
{
	int	c;

	c = img->pixels[p] << 24 | img->pixels[p + 1] << 16 | img->pixels[p + 2]
		<< 8 | img->pixels[p + 3];
	return (c);
}

mlx_image_t	*get_texture(t_data *data, int ray)
{
	if (data->rays[ray].texture == NORTH)
		return (data->img.so_wall);
	else if (data->rays[ray].texture == SOUTH)
		return (data->img.no_wall);
	else if (data->rays[ray].texture == EAST)
		return (data->img.we_wall);
	else if (data->rays[ray].texture == WEST)
		return (data->img.ea_wall);
	return (0);
}

void	height_calculation(t_data *data, int ray)
{
	t_point	init;
	t_point	end;
	int		dist;

	init.x = data->num_rays - (ray + 1);
	end.x = data->num_rays - (ray + 1);
	data->rays[ray].h_fov = (int)((data->wall_height
				/ data->rays[ray].distance) * data->rays[ray].dis_fov);
	init.y = data->horizont + (data->rays[ray].h_fov / 2);
	end.y = init.y - data->rays[ray].h_fov;
	if (data->rays[ray].distance != -1)
	{
		dist = init.y - end.y;
		draw_big(data, ray, dist, init);
		draw_small(data, ray, dist, init);
	}
}

float	hypotenuse(float a, float b)
{
	float	hipotenuse;

	hipotenuse = sqrt((a * a) + (b * b));
	return (hipotenuse);
}

void	calculate_hipotenuses(t_data *data)
{
	int		i;
	float	side_adj;
	float	side_opp;

	side_opp = data->width / 2;
	side_adj = side_opp / tan((data->angle_vision / 2) * data->radian_conver);
	i = 0;
	while (i < data->width / 2)
	{
		data->rays[i].dis_fov = hypotenuse(side_adj, (data->width / 2) - i);
		data->rays[data->width - i].dis_fov = hypotenuse(side_adj,
				(data->width / 2) - i);
		i++;
	}
	data->rays[i].dis_fov = side_adj;
}
