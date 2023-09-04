#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/inc/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <limits.h>
# include <math.h>

typedef struct s_point
{
	float		x;
	float		y;
}	t_point;

typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*screen;
	t_point		ply_pos;
	float		ply_angle;
	float		ply_speed;
	char		*map_name;
	char		**map;
}	t_data;

//provisionales
void	create_test_map(t_data *data, int width, int heigth);

#endif