#include "../../inc/cub3D.h"

void    draw_line(mlx_image_t *image, t_point begin, t_point end, int color)
{
	float   deltaX;
	float   deltaY;
	float   pixelX;
	float   pixelY;
	int     pixels;

	deltaX = end.x - begin.x;
	deltaY = end.y - begin.y;
	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));   
	deltaX = deltaX / pixels;
	deltaY = deltaY / pixels;
	pixelX = begin.x;
	pixelY = begin.y;
	while (pixels > 0)
	{
		mlx_put_pixel(image, pixelX, pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
		pixels--;
	}
}

void    draw_circle(mlx_image_t *image, t_point center, int radius, int color)
{
	float   angle;
	float   radians;
	float   sine;
	float   cosine;
	float   increment;

	angle = 0;
	increment = 360 / (2 * 3.1415 * radius);
	while (angle < 360)
	{
		radians = angle * (3.1415 / 180);
		sine = sin(radians);
		cosine = cos(radians);
		mlx_put_pixel(image, center.x + cosine * radius, center.y + sine * radius, color); 
		angle += increment;
	}
}

//Create draw_poligon(mlx_image_t *image, t_point *vertices, int vertices_num, int color)
