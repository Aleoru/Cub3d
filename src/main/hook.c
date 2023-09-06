#include "../../inc/cub3D.h"

void	hook(void *param)
{
	t_data	*data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
        //printf("key w\n");
		data->ply_pos.y -= 1;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
        //printf("key s\n");
		data->ply_pos.y += 1;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
        //printf("key a\n");
		data->ply_pos.x -= 1;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
        //printf("key d\n");
		data->ply_pos.x += 1;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
        printf("key left\n");
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
        printf("key right\n");
	}
	draw_player(data);
}