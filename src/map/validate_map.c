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

void	print_map(char	**map)
{
	int	y;

	y = 0;
	while (map[y])
	{
		if (ft_strchr(map[y], '\n'))
			printf("%s", map[y]);
		else
			printf("%s\n", map[y]);
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

static void	flood_map(t_level *level, int x, int y)
{
	if (x < 0 || y < 0 || x >= level->size_x + 2 || y >= level->size_y + 2)
		return ;
	if (level->fake_map[y][x] != '1' && level->fake_map[y][x] != '2'
		&& level->fake_map[y][x] != '\0')
	{
		level->fake_map[y][x] = '2';
		flood_map (level, x + 1, y);
		flood_map (level, x + 1, y + 1);
		flood_map (level, x, y + 1);
		flood_map (level, x - 1, y + 1);
		flood_map (level, x - 1, y);
		flood_map (level, x - 1, y - 1);
		flood_map (level, x, y - 1);
		flood_map (level, x + 1, y - 1);
	}
	check_flood(level);
}

void	check_flood(t_level *level)
{
	int	x;
	int	y;

	y = 0;
	while (level->fake_map[y])
	{
		x = 0;
		while (level->fake_map[y][x])
		{
			if (!ft_strchr("0NSEW", level->fake_map[y][x]))
				x++;
			else
				break ;
		}
		if (level->fake_map[y][x] == '0')
			flood_map(level, x, y);
		else
			y++;
	}
}

void	validate_map(t_data *data, t_level *level)
{
	int	x;
	int	y;

	(void)data;
	y = 0;
	(void)x;
	level->fake_map = copy_map(level);
	check_flood(level);
	if (level->fake_map[0][0] == '2')
		printf("ERROR\nInvalid map, open walls\n");
	print_map(level->fake_map);
	printf("Todo correcto\n");
}
