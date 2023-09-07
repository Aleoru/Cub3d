#include "../../inc/cub3D.h"

void	clear_image(mlx_image_t *image)
{
	ft_memset(image->pixels, 0, image->width * image->height * sizeof(int));
}

void	draw_player(t_data *data)
{
	t_point	ver[4];
	int		dis;

	dis = 10;
	ver[0].x = data->ply_pos.x - dis;
	ver[0].y = data->ply_pos.y - dis;
	ver[2].x = data->ply_pos.x + dis;
	ver[2].y = data->ply_pos.y + dis;
	ver[1].x = data->ply_pos.x + dis;
	ver[1].y = data->ply_pos.y - dis;
	ver[3].x = data->ply_pos.x - dis;
	ver[3].y = data->ply_pos.y + dis;
	clear_image(data->screen);
	draw_poli(data->screen, ver, 4, 0xdc6400ff);
	mlx_put_pixel(data->screen, data->ply_pos.x,
		data->ply_pos.y, 0xFF66FF);
}
