/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 20:36:51 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/11/05 20:58:10 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3D_bonus.h"

static void	sort_by_distance(t_data *data, float dist, int pos)
{
	t_sprite	temp;
	int			i;
	int			j;

	j = -1;
	while (++j < data->n_sprites)
	{
		i = j - 1;
		dist = -1;
		pos = -1;
		while (++i < data->n_sprites)
		{
			if (data->sprites[i].dist > dist)
			{
				dist = data->sprites[i].dist;
				pos = i;
			}
		}
		if (pos != -1)
		{
			temp = data->sprites[j];
			data->sprites[j] = data->sprites[pos];
			data->sprites[pos] = temp;
		}
	}
}

void	draw_sprites(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->n_sprites)
	{
		sprite_is_visible(data, i);
		i++;
	}
	sort_by_distance(data, -1, -1);
	i = 0;
	while (i < data->n_sprites)
	{
		if (data->sprites[i].dist > -1)
			draw_sprite(data, i);
		i++;
	}
}

void	draw_column(t_data *data, int sprite, int column)
{
	int		i;
	int		y;
	int		pixel;
	int		color;
	float	factor;

	i = 0;
	pixel = ((data->cl_size * data->cl_size) - data->cl_size
			+ data->sprites[sprite].pixel) * 4;
	color = get_color(get_sprite_texture(data, sprite), pixel);
	factor = 0;
	while (i <= data->sprites[sprite].size)
	{
		y = (data->sprites[sprite].size - i) + data->sprites[sprite].init.y;
		if (on_limits(data, column, y) && color != 0)
			mlx_put_pixel(data->screen, column, y, color);
		if ((float)i >= factor)
		{
			factor += data->sprites[sprite].scale;
			color = get_color(get_sprite_texture(data, sprite), pixel);
			pixel = pixel - (data->cl_size * 4);
		}
		i++;
	}
}

void	draw_sprite(t_data *data, int sprite)
{
	int		i;
	int		column;
	float	factor;

	i = 0;
	factor = 0;
	while (i < data->sprites[sprite].size)
	{
		column = data->sprites[sprite].init.x + i;
		if (column_is_visible(data, sprite, column))
		{
			draw_column(data, sprite, column);
		}
		if ((float)i >= factor)
		{
			factor += data->sprites[sprite].scale;
			data->sprites[sprite].pixel++;
		}
		i++;
	}
}
