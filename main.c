#include "cub3D.h"

void	limits(t_game *game)
{
	game->top = (int)game->player_pos.y/64;
	game->down = (int)game->player_pos.y/64 +1;
	game->left = (int)game->player_pos.x/64;
	game->right = (int)game->player_pos.x/64 +1;
}

int		wall_collision(t_game *game, t_point *dest)
{
	int x;
	int	y;
	int	y_offset;
	
	x = dest->x / 64;
	y = dest->y / 64;
	if (game->player_pos.y > dest->y)
		y_offset = -1;
	else
		y_offset = 1;
	printf("collision x:%d y:%d\n", x, y);
	if (game->map[y + y_offset][x] == '1')
		return (1);
	return (0);
}

void	ray_dir(t_game *game)
{	
	t_point	dest;
	if (game->angle >= 0 && game->angle < 180)
	{
		game->co = game->player_pos.y - (game->top * 64);

	}
	else
		game->co = (game->down * 64) - game->player_pos.y;
	
	game->ca = game->co/tan(game->radians);
	dest.x = game->player_pos.x + game->ca;
	dest.y = game->player_pos.y - game->co; //restar porque no es un eje cartesiano
	printf("dest y:%d\n", (int)dest.y);
	printf("dest x:%d\n", (int)dest.x);
	draw_line2(game->screen, game->player_pos, dest, 0xFFFFFF);
	if (wall_collision(game, &dest))
		printf("collision\n");
}

void	draw_ray(t_game *game, float *cosine, float *sine)
{
	//borrar pixeles de una imagen
	game->screen->pixels = ft_calloc(game->screen->width * game->screen->height, sizeof(int));
	game->player_pos.x = game->player->instances[0].x + 32;
	game->player_pos.y = game->player->instances[0].y + 32;
	game->dest.x = game->player_pos.x + *cosine * 10; 
	game->dest.y = game->player_pos.y - *sine * 10; //restar porque no son cartesianas
	draw_line2(game->screen, game->player_pos, game->dest, 0xFFFFFF); 
	limits(game);
	ray_dir(game);
	printf("angle: %d\n", game->angle);
	printf("x:%d, y:%d\n", (int)game->player_pos.x / 64, (int)game->player_pos.y / 64);
	printf("top:%d, down;%d, left:%d, right:%d\n", game->top, game->down, game->left, game->right);
}

void	hook(void *param)
{
	t_game	*game;
	float   sine;
    float   cosine;

	game = param;
	game->radians = game->angle * (3.1415 / 180);
	sine = sin(game->radians);
    cosine = cos(game->radians);
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_UP))
	{
		game->player->instances[0].y -= 1;
		draw_ray(game, &cosine, &sine);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
	{
		game->player->instances[0].y += 1;
		draw_ray(game, &cosine, &sine);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		game->player->instances[0].x -= 1;
		draw_ray(game, &cosine, &sine);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		game->player->instances[0].x += 1;
		draw_ray(game, &cosine, &sine);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		game->angle++;
		if (game->angle > 360)
			game->angle = 1;
		game->radians = game->angle * (3.1415 / 180);
		sine = sin(game->radians);
        cosine = cos(game->radians);
		draw_ray(game, &cosine, &sine);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		game->angle--;
		if (game->angle < 0)
			game->angle = 359;
		game->radians = game->angle * (3.1415 / 180);
		sine = sin(game->radians);
        cosine = cos(game->radians);
		draw_ray(game, &cosine, &sine);
	}

	//memset(game->screen->pixels, 0, game->screen->width * game->screen->height * sizeof(int));
	//draw_line(game->screen, 0, 0, game->image->instances[0].x, game->image->instances[0].y, 0xFFFFFF);
	//draw_circle(game->screen, 200, 200, 150, 0xFFFFFF);
}

void reserve_memory_map(t_game *game, int width, int heigth)
{
	int		i;

	i = 0;
	game->map = malloc(sizeof(char*) * heigth +1);
	while (i < heigth)
	{
		game->map[i] = malloc(sizeof(char) * width +1);
		game->map[i][width] = '\0';
		i++;
	}
	game->map[i] = malloc(sizeof(char) * 1);
	game->map[i][0] = '\0';
}

void create_test_map(t_game *game, int width, int heigth)
{
	int x;
	int y;

	reserve_memory_map(game, width, heigth);
	y = 0;
	while (y < heigth)
	{
		x = 0;
		while (x < width)
		{
			if (y == 0 || y == heigth -1 || x == 0 || x == width -1)
				game->map[y][x] = '1';
			else
				game->map[y][x] = '0';
			x++;
		}
		y++;
	}
	game->map[3][3] = '1';
	game->map[4][3] = '1';
	game->map[5][3] = '1';
	game->map[2][1] = '1';
	game->map[7][6] = '1';
	game->map[6][6] = '1';
	game->map[2][5] = '1';
	game->map[2][6] = '1';
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	//init window
	t_game	game;
	int		width = 640;
	int		height = 640;
	game.angle = 45;
	game.mlx = mlx_init(width, height, "cub3D", true);

	//create map
	printf("pre create map\n");
	create_test_map(&game, 10, 10);

	//create images
	mlx_texture_t	*texture;
	texture = mlx_load_png("./png/tile1.png");
	game.image = mlx_texture_to_image(game.mlx, texture);
	mlx_delete_texture(texture);
	texture = mlx_load_png("./png/wall.png");
	game.wall = mlx_texture_to_image(game.mlx, texture);
	mlx_delete_texture(texture);
	texture = mlx_load_png("./png/char.png");
	game.player = mlx_texture_to_image(game.mlx, texture);
	mlx_delete_texture(texture);
	//screen
	game.screen = mlx_new_image(game.mlx, width, height);
	memset(game.screen->pixels, 0, game.screen->width * game.screen->height * sizeof(int));
	//grid
	game.grid = mlx_new_image(game.mlx, width, height);
	memset(game.grid->pixels, 0, game.screen->width * game.screen->height * sizeof(int));

	//draw
	printf("pre draw\n");
	draw_map(&game, 10, 10, 64);
	printf("post draw\n");

	//draw screen
	mlx_image_to_window(game.mlx, game.screen, 0, 0);
	mlx_image_to_window(game.mlx, game.grid, 0, 0);
	draw_grid2(game.grid, width, height, 64, 0xFFFFFF);


	//loop
	mlx_loop_hook(game.mlx, &hook, &game);
	mlx_loop(game.mlx);

	//close
	mlx_terminate(game.mlx);

	float angulo = 271;
	float radianes = angulo * (3.1415926536 / 180); //Para convertir un angulo en radianes
	float seno = sin(radianes);                     //Representa la coordenada Y del punto
	float coseno = cos(radianes);					//Representa la coordenada X del punto
	float tangente = tan(radianes);					//Representa la distancia desde el punto hasta donde corta la linea tangente con el eje X

	//Las funciones del seno, coseno y tangente necesitan el valor en radianes del angulo
	printf("seno: %.5f\n", seno);
	printf("coseno: %.5f\n", coseno);
	printf("tangente: %.5f\n", tangente);
	return (0);
}
