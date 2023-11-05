/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:10:43 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/11/05 20:52:24 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3D_bonus.h"

void	upload_sprite_images(t_data *data)
{
	mlx_texture_t	*t;

	t = mlx_load_png("./assets/png/sprite_a.png");
	data->sprite_a = mlx_texture_to_image(data->mlx, t);
	mlx_delete_texture(t);
	t = mlx_load_png("./assets/png/sprite_b.png");
	data->sprite_b = mlx_texture_to_image(data->mlx, t);
	mlx_delete_texture(t);
	t = mlx_load_png("./assets/png/sprite_c.png");
	data->sprite_c = mlx_texture_to_image(data->mlx, t);
	mlx_delete_texture(t);
}

static int	size_sprite(t_data *data, int sprite, int ray)
{
	int		size;

	size = (int)(data->wall_height
			/ data->sprites[sprite].dist * data->rays[ray].dis_fov);
	return (size);
}

static float	angle_vision(t_data *data, int s)
{
	float	angle;
	float	co;
	float	ca;

	ca = data->sprites[s].pos.x - data->ply_pos.x;
	co = data->ply_pos.y - data->sprites[s].pos.y;
	angle = normalized_radians(atan2(co, ca));
	data->sprites[s].dist = hypotenuse(ca, co);
	return (angle);
}

int	sprite_is_visible(t_data *data, int s)
{
	int		i;
	float	angle;

	angle = angle_vision(data, s);
	i = 0;
	while (i < data->num_rays)
	{
		data->sprites[s].pixel = 0;
		if ((int)data->rays[i].angle * 1000 == (int)angle * 1000)
		{
			data->sprites[s].size = size_sprite(data, s, i);
			data->sprites[s].init.x = i - (data->sprites[s].size / 2);
			data->sprites[s].init.y = data->horizont
				+ (data->sprites[s].size / 2);
			data->sprites[s].scale = (float)data->sprites[s].size
				/ data->cl_size;
			return (1);
		}
		data->sprites[s].dist = -1;
		i++;
	}
	return (0);
}

int	column_is_visible(t_data *data, int sprite, int column)
{
	int		ray;

	ray = data->sprites[sprite].init.x + column;
	if (data->sprites[sprite].dist > data->rays[ray].distance)
		return (0);
	return (1);
}
