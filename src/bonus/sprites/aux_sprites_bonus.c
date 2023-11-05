/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_sprites_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 20:43:45 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/11/05 20:47:58 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3D_bonus.h"

int	on_limits(t_data *data, int x, int y)
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

void	add_sprite(t_data *data, int x, int y, char c)
{
	data->sprites[data->n_sprites].pos.x = ((x + 1)
			* data->cl_size) + data->cl_size / 2;
	data->sprites[data->n_sprites].pos.y = ((y + 1)
			* data->cl_size) + data->cl_size / 2;
	data->sprites[data->n_sprites].type = c;
	data->n_sprites++;
}
