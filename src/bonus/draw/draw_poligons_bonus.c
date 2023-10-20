/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_poligons_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:42:28 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/10/20 19:42:59 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3D_bonus.h"

void	draw_line(mlx_image_t *image, t_point begin, t_point end, int color)
{
	float	delta_x;
	float	delta_y;
	float	pixel_x;
	float	pixel_y;
	int		pixels;

	delta_x = end.x - begin.x;
	delta_y = end.y - begin.y;
	pixels = sqrt((delta_x * delta_x) + (delta_y * delta_y));
	delta_x = delta_x / pixels;
	delta_y = delta_y / pixels;
	pixel_x = begin.x;
	pixel_y = begin.y;
	while (pixels > 0)
	{
		mlx_put_pixel(image, pixel_x, pixel_y, color);
		pixel_x += delta_x;
		pixel_y += delta_y;
		pixels--;
	}
}

void	draw_circle(mlx_image_t *image, t_point center, int radius, int color)
{
	float	angle;
	float	radians;
	float	sine;
	float	cosine;
	float	increment;

	angle = 0;
	increment = 360 / (2 * 3.1415 * radius);
	while (angle < 360)
	{
		radians = angle * (3.1415 / 180);
		sine = sin(radians);
		cosine = cos(radians);
		mlx_put_pixel(image, center.x + cosine * radius,
			center.y + sine * radius, color);
		angle += increment;
	}
}

void	draw_poli(mlx_image_t *img, t_point *vertices, int vrt_num, int color)
{
	int		i;

	i = 0;
	while (i < vrt_num - 1)
	{
		draw_line(img, vertices[i], vertices[i + 1], color);
		i++;
	}
	draw_line(img, vertices[vrt_num - 1], vertices[0], color);
}

void	draw_cell(mlx_image_t *img, t_point init, int size, int color)
{
	int		y;
	int		x;
	int		color2;

	color2 = 0x666666FF;
	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			if (y == 0 || x == 0)
				mlx_put_pixel(img, (int)init.x + x, (int)init.y + y, color2);
			else
				mlx_put_pixel(img, (int)init.x + x, (int)init.y + y, color);
			x++;
		}
		y++;
	}
}
