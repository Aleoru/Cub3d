/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_of_view.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 04:22:29 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/10/09 19:04:36 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static int	get_color(mlx_image_t *img, int p)
{
	int	c;

	c = img->pixels[p] << 24 | img->pixels[p + 1] << 16 | img->pixels[p + 2]
		<< 8 | img->pixels[p + 3];
	return (c);
}

static int	get_texture(t_data *data, int ray)
{
	if (data->rays[ray].texture == NORTH)
		return (0x33F6FFFF);	// Azul
	else if (data->rays[ray].texture == SOUTH)
		return (0x66FF66FF);	// verde
	else if (data->rays[ray].texture == EAST)
		return (0x9C33FFFF);	// Morado
	else if (data->rays[ray].texture == WEST)
		return (0xDDFF33FF);	// Amarillo
	return (0);
}

//a/b = c/d; a = c/d *b
void    height_calculation(t_data *data, int ray)
{
	t_point	init;
	t_point	end;
	int		c;

	c = get_texture(data, ray);
	init.x = ray;
	end.x = ray;
	data->rays[ray].h_fov = (int)((data->wall_height /
		data->rays[ray].distance) * data->rays[ray].dis_fov);
	init.y = data->horizont + (data->rays[ray].h_fov / 2);
	end.y = init.y - data->rays[ray].h_fov;
	if (data->rays[ray].distance != -1)
	{
		int		p;
		int 	x;
		int		d;
		float	f_init;
		float	f;
		float	r;

		p = ((data->cell_size * data->cell_size) - data->cell_size + data->rays[ray].pixel) * 4;
		d = init.y - end.y;
		c = get_color(data->img.we_wall, p);
		f_init = (float)d / data->cell_size;
		f = f_init;
		r = 0;
		x = 0;
		while (x <= d && f_init >= 1)
		{
			if (init.y - x >= 0 && init.y - x <= data->height)
				mlx_put_pixel(data->screen, init.x, init.y - x, c);
			if ((float)x > f)
			{
				f += f_init;
				c = get_color(data->img.ea_wall, p);
				p = p - (data->cell_size * 4);
			}
			x++;
		}
		x = 0;
		while ((int)r < data->cell_size && f_init < 1)
		{
			if (ray == data->width / 2)
				printf("f_init: %f, r: %f\n", f_init, r);
			p = p - (data->cell_size * 4);
			if (p < 0)
				break ;
			c = get_color(data->img.ea_wall, p);
			r += f_init;
			if (init.y - x >= 0 && init.y - x <= data->height)
				mlx_put_pixel(data->screen, init.x, init.y - (int)r, c);

		}
		if (ray == data->width / 2)
				printf("---------------------------------\n");
	}
}

/* void    height_calculation(t_data *data, int ray)
{
	t_point	init;
	t_point	end;
	int		c;

	c = get_texture(data, ray);
	init.x = ray;
	end.x = ray;
	data->rays[ray].h_fov = (int)((data->wall_height /
		data->rays[ray].distance) * data->rays[ray].dis_fov);
	init.y = data->horizont + (data->rays[ray].h_fov / 2);
	//printf("data horizont: %d\n", data->horizont);
	//printf("ray distance: %0.1f\n", data->rays[ray].distance);
	//printf("data horizont + h_fov / 2: %0.1f\n", data->wall_height);
	//printf("heigth_wall: %0.1f\n", init.y);
	//printf("h_fov: %d\n", data->rays[ray].h_fov);
	end.y = init.y - data->rays[ray].h_fov;
	//printf("ray: %d, init: %0.1f, %0.1f | ", ray, init.x, init.y);
	//printf(" ray: %d, end: %0.1f, %0.1f\n", ray, end.x, end.y);
	if (data->rays[ray].distance != -1)
	{
		int		p;
		int 	x;
		int 	y;
		int		d;
		float	f_init;
		float	f;

		p = ((data->cell_size * data->cell_size) - data->cell_size + data->rays[ray].pixel) * 4;
		d = init.y - end.y;
		c = get_color(data->img.we_wall, p);
		f_init = (float)d / data->cell_size;
		f = f_init;
		x = 0;
		y = 0;
		float	r = 1 / f_init;
		while (x <= d)
		{
			if (init.y - x >= 0 && init.y - x <= data->height)
				mlx_put_pixel(data->screen, init.x, init.y - x, c);
			if (f_init >= 1 && (float)x > f)
			{
				f += f_init;
				c = get_color(data->img.ea_wall, p);
				p = p - (data->cell_size * 4);
			}
			else if (f_init < 1)
			{
				f += f_init;
				c = get_color(data->img.ea_wall, p);
				if (r < 2)
					r = 2;
				p = p - ((data->cell_size * 4) * (int)r);
				if (ray == data->width / 2)
					printf("%d => %0.1f : %d > %0.1f - %d cambio\n", y, f_init, x, f, d);
				y++;
			}
			//printf("p = %d\n", p);
			x++;
		}
		if (ray == data->width / 2)
			printf("---------------------------------\n");
		//printf("%0.1f < %d\n", f, d);
		//draw_line(data->screen, init, end, c);
	}
} */

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
			(data->width / 2) -i);
		i++;
	}
	data->rays[i].dis_fov = side_adj;
}
