/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:42:48 by aoropeza          #+#    #+#             */
/*   Updated: 2023/10/25 19:52:38 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# define N 90
# define S 270
# define E 0
# define W 180
# define ELEM 6
# define NORTH 1
# define SOUTH 2
# define EAST 3
# define WEST 4

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
	char	**file_map;
	char	**fake_map;
	int		size_x;
	int		size_y;
	int		f_size;
	int		n_player;
	int		n_elems;
	char	direction;
}	t_level;

typedef struct s_inputs
{
	int			right;
	int			left;
	int			up;
	int			down;
	int			turn_right;
	int			turn_left;
	int			m_turn_right;
	int			m_turn_left;
}	t_inputs;

typedef struct s_ray
{
	t_point		dest;
	t_point		aux;
	t_point		init;
	float		distance;
	float		height_wall;
	float		dis_fov;
	int			h_fov;
	float		angle;
	int			x_dir;
	int			y_dir;
	int			pixel;
	int			texture;
}	t_ray;

typedef struct s_sprite
{
	float		angle;
	float		dist;
	t_point		pos;
	mlx_image_t	*img;
}	t_sprite;

typedef struct s_img
{
	mlx_image_t	*no_wall;
	mlx_image_t	*so_wall;
	mlx_image_t	*ea_wall;
	mlx_image_t	*we_wall;
}	t_img;

typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*screen;
	mlx_image_t	*background;
	mlx_image_t	*minimap;
	mlx_image_t	*ply_minimap;
	t_img		img;
	int			width;
	int			height;
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
	t_level		level;
	mlx_image_t	*map_image;
	char		*map_name;
	char		**map;
	int			cl_size;
	mlx_image_t	*wall;
	float		radian_conver;
	float		increment;
	float		wall_height;
	t_ray		*rays;
	int			num_rays;
	int			angle_vision;
	int			horizont;
	//draw sprites
	t_sprite	*sprites;
	int			n_sprites;
	mlx_image_t	*sprite_A;
	mlx_image_t	*sprite_B;
	mlx_image_t	*sprite_C;

}	t_data;

/****************/
/*	PROVISIONAL	*/
/****************/
void		create_test_map(t_data *data, int width, int heigth);
void		draw_map(t_data *data, int width, int heigth, int size);

/********************/
/*		DRAW		*/
/********************/
void		draw_line(mlx_image_t *image, t_point begin, t_point end,
				int color);
void		draw_circle(mlx_image_t *image, t_point center, int radius,
				int color);
void		draw_poli(mlx_image_t *img, t_point *vertices, int vrt_num,
				int color);
void		clear_image(mlx_image_t *image);
void		draw_screen(t_data *data);
void		draw_background(t_data *data, int width, int heigth);
void		draw_cell(mlx_image_t *img, t_point init, int size, int color);
void		draw_big(t_data *data, int ray, int dist, t_point init);
void		draw_small(t_data *data, int ray, int dist, t_point init);
int			get_color(mlx_image_t *img, int p);
mlx_image_t	*get_texture(t_data *data, int ray);

/****************/
/*		MAP		*/
/****************/
void		init_map(t_data *data, t_level *level, char *str);
void		validate_map(t_data *data, t_level *level);
int			get_rgb(t_data *data, t_level *level, char *str);
void		get_map_size(t_data *data, t_level *level);
void		parsing_map(t_data *data, t_level *level);
void		check_flood(t_data *data, t_level *level);
void		check_player_pos(t_data *data, t_level *level, int x, int y);

/********************/
/*		MOVE		*/
/********************/
void		move_player(t_data *data);
int			collision_player(t_data *data, float x, float y);

/********************/
/*		RAYCAST		*/
/********************/
float		normalized_radians(float radians);
void		create_rays(t_data *data);
void		angle_rays(t_data *data);
int			w_coll(t_data *data, float x, float y);
void		ray_collision(t_data *data, int ray);
float		ray_v_collision(t_data *data, int ray);
float		ray_h_collision(t_data *data, int ray);
void		calculate_hipotenuses(t_data *data);
float		hypotenuse(float a, float b);
void		height_calculation(t_data *data, int ray);

/********************/
/*		UTILS		*/
/********************/
size_t		split_size(char **split);
int			check_img(t_level *level);
char		*delete_nl(char	*str);
void		free_split(char **split);
void		free_level(t_data *data, t_level *level);
void		exit_error(t_data *data, char *str, int fd);

/********************/
/*		HOOK		*/
/********************/
void		hook(void *param);
void		cursor_hook(double xdelta, double ydelta, void *param);

/********************/
/*		MINIMAP		*/
/********************/
void		create_minimap(t_data *data, int cell_size);
void		draw_player_minimap(t_data *data, int size);

/********************/
/*		SPRITES		*/
/********************/
void		add_sprite(t_data *data, int x, int y, char c);
#endif
