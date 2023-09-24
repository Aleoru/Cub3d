#include "../../inc/cub3D.h"

static	void	reserve_memory_map(t_data *data, int width, int heigth)
{
	int		i;

	i = 0;
	data->map = malloc(sizeof(char *) * heigth +1);
	while (i < heigth)
	{
		data->map[i] = malloc(sizeof(char) * width +1);
		data->map[i][width] = '\0';
		i++;
	}
	data->map[i] = malloc(sizeof(char) * 1);
	data->map[i][0] = '\0';
}

void	create_test_map(t_data *data, int width, int heigth)
{
	int		x;
	int		y;

	reserve_memory_map(data, width, heigth);
	y = 0;
	while (y < heigth)
	{
		x = 0;
		while (x < width)
		{
			if (y == 0 || y == heigth -1 || x == 0 || x == width -1)
				data->map[y][x] = '1';
			else
				data->map[y][x] = '0';
			x++;
		}
		y++;
	}
	data->map[3][3] = '1';
	data->map[4][3] = '1';
	data->map[5][3] = '1';
	data->map[2][2] = '1';
	data->map[7][6] = '1';
	data->map[6][6] = '1';
	data->map[2][5] = '1';
	data->map[2][6] = '1';
}
