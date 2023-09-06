#include "../../inc/cub3D.h"

void	clear_image(mlx_image_t *image)
{
	image->pixels = ft_calloc(image->width * image->height, sizeof(int));
}

void	draw_player(t_data *data)
{
	clear_image(data->screen);
	mlx_put_pixel(data->screen, data->ply_pos.x, 
		data->ply_pos.y, 0xFF66FF);
	
}