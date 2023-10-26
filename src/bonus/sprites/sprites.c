/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:10:43 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/10/26 07:54:40 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3D_bonus.h"

//crea las imagenes utilizadas por los sprites en memoria
void	upload_sprite_images(t_data *data)
{
	(void)data;
}

//en la lectura del mapa, segun el caracter, inicializa los paremetros del t_sprite
void	add_sprite(t_data *data, int x, int y, char c)
{
	data->sprites[data->n_sprites].pos.x = ((x + 1) * data->cl_size) + data->cl_size / 2;
	data->sprites[data->n_sprites].pos.y = ((y + 1) * data->cl_size) + data->cl_size / 2;
	printf("read sprite:%c, sprites:%d, x:%f, y:%f\n", c, data->n_sprites, 
		data->sprites[data->n_sprites].pos.x,  data->sprites[data->n_sprites].pos.y);
	data->n_sprites++;
}

//en caso de ser visible, donde se dibujara el centro del sprite
int		pixel_origin(t_data	*data)
{
	(void)data;
	return (1);
}

//calculo del angulo entre el jugador y el sprite, si es un angulo entre los de su campo de visión es visible
//arcotangente = co / ca
int		sprite_is_visible(t_data *data, int sprite)
{
	float	angle;
	float	co;
	float	ca;
	int		i;

	ca = data->ply_pos.x - data->sprites[sprite].pos.x;
	co = data->ply_pos.y - data->sprites[sprite].pos.y;
	angle = atan(co/ca); // * data->radian_conver;
	printf("ray: %d,angle:%f\n", sprite, angle);
	i = 0;
	while (i < data->num_rays)
	{
		if (data->rays[i].angle == angle)
		{
			printf("sprite:%d is on field of vision\n", sprite);
			return (1);
		}
		i++;
	}
	return (0);
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
}