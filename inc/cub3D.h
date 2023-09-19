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

# define NORTH 1
# define SOUTH 2
# define EAST 3
# define WEST 4

typedef struct s_point
{
	float		x;
	float		y;
}	t_point;

typedef struct s_inputs
{
	int			right;
	int			left;
	int			up;
	int			down;
	int			turn_right;
	int			turn_left;
}	t_inputs;

typedef struct s_ray
{
	t_point		dest;
	t_point		init;
	float		distance;
	float		angle;
	int			x_dir;
	int			y_dir;
	int			pixel;
	int			texture;
}	t_ray;

typedef struct s_data
{
	//ventana
	mlx_t		*mlx;
	mlx_image_t	*screen;
	int			width;
	int			height;
	//player
	t_point		ply_pos;
	t_point		ply_cell;
	t_inputs	ply_inputs;
	float		ply_angle;
	float		ply_angle_mv;
	float		ply_radians;
	float		ply_speed;
	float		ply_turn_speed;
	int			ply_x_axis;
	int			ply_y_axis;
	int			ply_turn_dir;
	//mapa
	mlx_image_t	*map_image;
	char		*map_name;
	char		**map;
	int			map_cell_size;
	//png
	mlx_image_t	*wall;
	//ray casting
	float		radian_conver;
	float		increment;
	t_ray		*rays;
	int			num_rays;
	int			angle_vision;
}	t_data;

//provisionales
void	create_test_map(t_data *data, int width, int heigth);
void	draw_map(t_data *data, int width, int heigth, int size);

//dibujo
void	draw_line(mlx_image_t *image, t_point begin, t_point end, int color);
void	draw_circle(mlx_image_t *image, t_point center, int radius, int color);
void	draw_poli(mlx_image_t *img, t_point *vertices, int vrt_num, int color);
void	clear_image(mlx_image_t *image);
void	draw_player(t_data *data);

//hook
void	hook(void *param);

//move
void	move_player(t_data *data);
int		collision_player(t_data *data, float x, float y);

//ray casting
float	normalized_radians(float radians);
void	create_rays(t_data *data);
void	angle_rays(t_data *data);
void	ray_collision(t_data *data, int ray);

#endif
