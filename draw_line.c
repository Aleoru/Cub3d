/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:14:11 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/07/27 20:38:12 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void    draw_line(mlx_image_t *image, int beginX, int beginY, int endX, int endY, int color)
{
    double  deltaX;
    double  deltaY;
    double  pixelX;
    double  pixelY;
    int     pixels;

    deltaX = endX - beginX;
    deltaY = endY - beginY;
    pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));   
    deltaX = deltaX / pixels;
    deltaY = deltaY / pixels;
    pixelX = beginX;
    pixelY = beginY;
    while (pixels > 0)
    {
        mlx_put_pixel(image, pixelX, pixelY, color);
        pixelX += deltaX;
        pixelY += deltaY;
        pixels--;
    }
}

void    draw_line2(mlx_image_t *image, t_point begin, t_point end, int color)
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

void    draw_circle(mlx_image_t *image, int x, int y, int radius, int color)
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
        mlx_put_pixel(image, x + cosine * radius, y + sine * radius, color); 
        angle += increment;
    }
}

void    draw_circle2(mlx_image_t *image, t_point center, int radius, int color)
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
