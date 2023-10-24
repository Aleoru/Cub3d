/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:10:43 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/10/24 16:08:14 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3D_bonus.h"

//crea las imagenes utilizadas por los sprites en memoria
void	upload_sprite_images(t_data *data)
{

}

//en la lectura del mapa, segun el caracter, inicializa los paremetros del t_sprite
void	load_sprite(t_data *data, char c)
{
	
}

//en caso de ser visible, donde se dibujara el centro del sprite
int		pixel_origin(t_data	*data)
{

}

//calculo del angulo entre el jugador y el sprite, si es un angulo entre los de su campo de visión es visible
//arcotangente = co / ca
int		sprite_is_visible(t_data *data, int sprite)
{
	float	angle;
	float	co;
	float	ca;

	ca = data->ply_pos.x - data->sprites[sprite].pos.x;
	co = data->ply_pos.y - data->sprites[sprite].pos.y;
	angle = atan(co/ca) * data->radian_conver;
	//encontrar la coincidencia en el campo de vision
	return (0);
}