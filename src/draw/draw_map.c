#include "../../inc/cub3D.h"

void	draw_map(t_data *data, int width, int heigth, int size)
{
	int y;
	int x;

	y = 0;
	while (y < heigth)
	{
		x = 0;
		while (x < width)
		{
			if (data->map[y][x] == '1')
				mlx_image_to_window(data->mlx, data->wall, x * size, y * size);
			x++;
		}
		y++;
	}
}