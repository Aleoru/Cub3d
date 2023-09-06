/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 04:15:43 by fgalan-r          #+#    #+#             */
/*   Updated: 2023/07/27 20:51:12 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void    draw_map(t_game *game, int width, int heigth, int size)
{
    int y;
    int x;

    y = 0;
    while (y < heigth)
    {
        x = 0;
        while (x < width)
        {
            if (game->map[y][x] == '1')
                mlx_image_to_window(game->mlx, game->wall, x * size, y * size);
            x++;
        }
        y++;
    }
    printf("draw character\n");
    mlx_image_to_window(game->mlx, game->player, 320, 320);
}

void	draw_grid(mlx_image_t *image, int width, int heigth, int size, int color)
{
    int y;
    int x;

    y = 0;
    while (y < heigth)
    {
        draw_line(image, 0, y, width -1, y, color);
        y += size;
    }
    x = 0;
    while (x < heigth)
    {
        draw_line(image, x, 0, x, heigth -1, color);
        x += size;
    }
}

void	draw_grid2(mlx_image_t *image, int width, int heigth, int size, int color)
{
    t_point init;
    t_point end;

    init.y = 0;
    init.x = 0;
    end.y = 0;
    end.x = width -1;
    while (init.y < heigth)
    {
        draw_line2(image, init, end, color);
        init.y += size;
        end.y += size;
    }
    init.y = 0;
    init.x = 0;
    end.y = heigth -1;
    end.x = 0;
    while (init.x < heigth)
    {
        draw_line2(image, init, end, color);
        init.x += size;
        end.x += size;
    }
}