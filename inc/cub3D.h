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

# define NO "NO"
# define SO "SO"
# define EA "EA"
# define WE "WE"
# define F "F"
# define C "C"
# define ELEM 6

typedef struct s_point
{
	float		x;
	float		y;
}	t_point;

typedef struct s_level
{
	char	*path;
	int		fd;
	char	*no_path;
	char	*so_path;
	char	*ea_path;
	char	*we_path;
	int		f_color;
	int		c_color;
	char	**map;
	int		size_x;
	int		size_y;
}	t_level;

typedef struct s_data
{
	//ventana
	mlx_t		*mlx;
	mlx_image_t	*screen;
	//player
	t_point		ply_pos;
	t_point		ply_cell;
	float		ply_angle;
	float		ply_speed;
	int			ply_x_axis; 	//right - left
	int			ply_y_axis; 	//down - up
	int			ply_turn_dir; 	//right - left
	//mapa
	t_level		level;
	mlx_image_t	*map_image;
	char		*map_name;
	char		**map;
	//png
	mlx_image_t	*wall;
}	t_data;

/****************/
/*	PROVISIONAL	*/
/****************/
void	create_test_map(t_data *data, int width, int heigth);
void	draw_map(t_data *data, int width, int heigth, int size);

/********************/
/*		DRAW		*/
/********************/
void	draw_line(mlx_image_t *image, t_point begin, t_point end, int color);
void	draw_circle(mlx_image_t *image, t_point center, int radius, int color);
void	draw_poli(mlx_image_t *img, t_point *vertices, int vrt_num, int color);
void	clear_image(mlx_image_t *image);
void	draw_player(t_data *data);

/****************/
/*		MAP		*/
/****************/
void	init_map(t_data *data, t_level *level, char *str);

/********************/
/*		UTILS		*/
/********************/
void	free_split(char **split);
void	free_level(t_level *level);

/********************/
/*		HOOK		*/
/********************/
void	hook(void *param);
#endif
