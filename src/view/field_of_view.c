/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_of_view.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 04:22:29 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/09/30 04:45:39 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h" 

//a/b = c/d; a = c/d *b
void    height_calculation(t_data *data, int ray)
{
	t_point	init;
	t_point	end;
	int		c;

	c = 0x66FF66FF;
	init.x = ray;
	end.x = ray;
	data->rays[ray].h_fov = (int)((data->wall_height /  //data->rays[ray].height_wall / 
		data->rays[ray].distance) * data->rays[ray].dis_fov);
	init.y = data->horizont + (data->rays[ray].h_fov / 2);
	//printf("data horizont: %d\n", data->horizont);
	//printf("data horizont + h_fov / 2: %0.1f\n", data->wall_height);
	//printf("heigth_wall: %0.1f\n", init.y);
	//printf("h_fov: %d\n", data->rays[ray].h_fov);
	end.y = init.y - data->rays[ray].h_fov;
	//printf("ray: %d, init: %0.1f, %0.1f | ", ray, init.x, init.y);
	//printf(" ray: %d, end: %0.1f, %0.1f\n", ray, end.x, end.y);
	draw_line(data->screen, init, end, c);
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
			(data->width / 2) -i);
		i++;
	}
	data->rays[i].dis_fov = side_adj;
}
