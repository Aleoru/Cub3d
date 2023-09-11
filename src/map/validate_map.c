/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 20:03:06 by aoropeza          #+#    #+#             */
/*   Updated: 2023/09/09 20:03:06 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	printf_map(char	**map)
{
	int	y;

	y = 0;
	while (map[y])
	{
		printf("%s", map[y]);
		y++;
	}
	printf("\n-----------------------\n\n");
}

static char	**copy_map(t_level *level)
{
	int		y;
	char	**map;

	y = 0;
	map = ft_calloc(level->size_y, level->size_x);
	while (level->map[y])
	{
		map[y] = ft_strdup(level->map[y]);
		y++;
	}
	return (map);
}

static void	flood_map(t_level *level, char **map, int x, int y)
{
	printf("Inundando...\n");
	printf("%c\n", map[y][x]);
	if (x < 0 || y < 0 || x > level->size_x || y > level->size_y)
		return ;
	if (map[y][x] != '1' && map[y][x] != '2')
		map[y][x] = '2';
	printf_map(map);
	flood_map (level, map, x + 1, y);
	//flood_map (level, map, x + 1, y + 1);
	flood_map (level, map, x, y + 1);
	//flood_map (level, map, x - 1, y + 1);
	flood_map (level, map, x - 1, y);
	//flood_map (level, map, x - 1, y - 1);
	flood_map (level, map, x, y - 1);
	//flood_map (level, map, x + 1, y - 1);
}

void	validate_map(t_data *data, t_level *level, char **map)
{
	int	x;
	int	y;

	(void)data;
	(void)map;
	x = level->size_x / 2;
	y = level->size_y / 2;
	flood_map(level, copy_map(level), x, y);

	printf("Todo correcto\n");
}
