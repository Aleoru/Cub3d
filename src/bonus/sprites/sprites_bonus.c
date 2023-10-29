/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:10:43 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/10/29 02:43:41 by fgalan-r         ###   ########.fr       */
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
	printf("read sprite:%c, sprites:%d, x:%f, y:%f\n", c, data->n_sprites, 
		data->sprites[data->n_sprites].pos.x,  data->sprites[data->n_sprites].pos.y);
	if (c == 'A')
		data->sprites[data->n_sprites].img = data->sprite_a;
	else if (c == 'B')
		data->sprites[data->n_sprites].img = data->sprite_b;
	else if (c == 'C')
		data->sprites[data->n_sprites].img = data->sprite_c;
	data->n_sprites++;
}

//en caso de ser visible, donde se dibujara el centro del sprite
int		pixel_origin(t_data	*data)
{
	(void)data;
	return (1);
}

static int		size_sprite(t_data *data, int sprite, int ray)
{
	int		size;

	size = (int)(data->wall_height 
		/ data->sprites[sprite].dist * data->rays[ray].dis_fov); 
	return (size);
}

//calculo del angulo entre el jugador y el s prite, si es un angulo entre los de su campo de visión es visible
//arcotangente = co / ca
int		sprite_is_visible(t_data *data, int sprite)
{
	float	angle;
	float	co;
	float	ca;
	int		i;

	ca = data->sprites[sprite].pos.x - data->ply_pos.x;
	co = data->ply_pos.y - data->sprites[sprite].pos.y; //invertir en la Y
	//angle = atan(co/ca); // * data->radian_conver;
	angle = normalized_radians(atan2(co, ca)); // * data->radian_conver;
	//printf("ray: %d,angle:%f\n", sprite, angle);
	i = 0;
	while (i < data->num_rays)
	{
		//printf("angle[%d]:%f\n",i , data->rays[i].angle);
		if ((int)data->rays[i].angle * 1000 == (int)angle * 1000)
		{
			printf("----->  sprite:%d view on ray: %d\n", sprite, i);
			data->sprites[sprite].dist = hypotenuse(ca, co);
			data->sprites[sprite].size = size_sprite(data, sprite, i);
			data->sprites[sprite].init.x = i - (data->sprites[sprite].size / 2);
			data->sprites[sprite].init.y = data->horizont
				 + (data->sprites[sprite].size / 2);
			draw_sprite(data, sprite);
			printf("sprite size: %d\n", data->sprites[sprite].size);
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