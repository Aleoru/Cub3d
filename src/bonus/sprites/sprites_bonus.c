/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:10:43 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/11/05 19:16:27 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3D_bonus.h"

//crea las imagenes utilizadas por los sprites en memoria
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

//en la lectura del mapa, segun el caracter, inicializa los paremetros del t_sprite
void	add_sprite(t_data *data, int x, int y, char c)
{
	data->sprites[data->n_sprites].pos.x = ((x + 1) * data->cl_size) + data->cl_size / 2;
	data->sprites[data->n_sprites].pos.y = ((y + 1) * data->cl_size) + data->cl_size / 2;
	data->sprites[data->n_sprites].type = c;
	printf("read sprite:%c, sprites:%d, x:%f, y:%f\n", data->sprites[data->n_sprites].type, data->n_sprites,
		data->sprites[data->n_sprites].pos.x, data->sprites[data->n_sprites].pos.y);
	data->n_sprites++;
}

static int	size_sprite(t_data *data, int sprite, int ray)
{
	int		size;

	size = (int)(data->wall_height
			/ data->sprites[sprite].dist * data->rays[ray].dis_fov);
	return (size);
}

int	sprite_is_visible(t_data *data, int sprite)
{
	float	angle;
	float	co;
	float	ca;
	int		i;

	ca = data->sprites[sprite].pos.x - data->ply_pos.x;
	co = data->ply_pos.y - data->sprites[sprite].pos.y; //invertir en la Y
	angle = normalized_radians(atan2(co, ca)); // * data->radian_conver;
	//printf("ray: %d,angle:%f\n", sprite, angle);
	i = 0;
	while (i < data->num_rays)
	{
		data->sprites[sprite].pixel = 0;
		if ((int)data->rays[i].angle * 1000 == (int)angle * 1000)
		{
			//init_visible_sprite
			printf("----->  sprite:%d view on ray: %d\n", sprite, i);
			data->sprites[sprite].dist = hypotenuse(ca, co);
			data->sprites[sprite].size = size_sprite(data, sprite, i);
			data->sprites[sprite].init.x = i - (data->sprites[sprite].size / 2);
			//data->sprites[sprite].init.x = (data->width - i) - (data->sprites[sprite].size / 2);
			data->sprites[sprite].init.y = data->horizont
				 + (data->sprites[sprite].size / 2);
			data->sprites[sprite].scale = (float)data->sprites[sprite].size / data->cl_size;
			printf("sprite size: %d\n", data->sprites[sprite].size);
			return (1);
		}
		data->sprites[sprite].dist = -1;
		i++;
	}
	return (0);
}

static void	sort_by_distance(t_data *data)
{
	t_sprite	temp;
	float		dist;
	int			i;
	int			j;
	int			pos;

	j = 0;
	while (j < data->n_sprites)
	{
		i = j;
		dist = -1;
		pos = -1;
		while (i < data->n_sprites)
		{
			if (data->sprites[i].dist > dist)
			{
				dist = data->sprites[i].dist;
				pos = i;
			}
			i++;
		}
		if (pos != -1)
		{
			temp = data->sprites[j];
			data->sprites[j] = data->sprites[pos];
			data->sprites[pos] = temp;
		}
		j++;
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
	sort_by_distance(data);
	i = 0;
	while (i < data->n_sprites)
	{
		if (data->sprites[i].dist > -1)
			draw_sprite(data, i);
		i++;
	}
}

int		column_is_visible(t_data *data, int sprite, int column)
{
	int		ray;

	ray = data->sprites[sprite].init.x + column;
	//ray = data->width - (data->sprites[sprite].init.x + column);
	if (data->sprites[sprite].dist > data->rays[ray].distance)
		return (0);
	return (1);
}

int		on_limits(t_data *data, int x, int y)
{
	if (x >= 0 && x < data->width && y >= 0 && y < data->height)
		return (1);
	return (0);
}

mlx_image_t	*get_sprite_texture(t_data *data, int sprite)
{
	if (data->sprites[sprite].type == 'A')
		return (data->sprite_a);
	else if (data->sprites[sprite].type == 'B')
		return (data->sprite_b);
	else if (data->sprites[sprite].type == 'C')
		return (data->sprite_c);
	return (0);
}

void	draw_column(t_data *data, int sprite, int column)
{
	int		i;
	int		y;
	int		pixel;
	int		color;
	float	factor;

	i = 0;
	printf("here 1\n");
	pixel = ((data->cl_size * data->cl_size) - data->cl_size
			+ data->sprites[sprite].pixel) * 4;
	printf("pixel: %d\n", pixel);
	color = get_color(get_sprite_texture(data, sprite), pixel);
	printf("here 2\n");
	factor = 0;
	while (i <= data->sprites[sprite].size)
	{
		y =  (data->sprites[sprite].size - i) + data->sprites[sprite].init.y;
		//y = data->sprites[sprite].init.y + i;
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
		if (column_is_visible(data, sprite, column)) //columna: posicion x en pantalla
		{
			draw_column(data, sprite, column); //columna posicion x en pantalla
		}
		if ((float)i >= factor)
		{
			factor += data->sprites[sprite].scale;
			data->sprites[sprite].pixel++;
		}
		i++;
	}
}

/* void	draw_big(t_data *data, int ray, int dist, t_point init)
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
	while (x <= dist)
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
} */
