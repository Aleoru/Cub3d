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

/* void	print_map(char	**map)
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
} */

void	check_player_pos(t_data *data, t_level *level, int x, int y)
{
	if (level->file_map[y + 1][x] == ' ' || level->file_map[y + 1][x + 1] == ' '
		|| level->file_map[y][x + 1] == ' '
		|| level->file_map[y - 1][x + 1] == ' '
		|| level->file_map[y - 1][x] == ' '
		|| level->file_map[y - 1][x - 1] == ' '
		|| level->file_map[y][x - 1] == ' '
		|| level->file_map[y + 1][x - 1] == ' ')
		exit_error(data, "Error\nPlayer out from the map\n", 2);
}

static void	copy_map(t_data *data, t_level *level)
{
	int		y;

	y = 0;
	level->fake_map = ft_calloc(level->size_y, level->size_x);
	while (data->map[y])
	{
		level->fake_map[y] = ft_strdup(data->map[y]);
		y++;
	}
}

static void	flood_map(t_data *data, t_level *level, int x, int y)
{
	if (x < 0 || y < 0 || x >= level->size_x + 2 || y >= level->size_y + 2)
		return ;
	if (level->fake_map[y][x] != '1' && level->fake_map[y][x] != '2'
		&& level->fake_map[y][x] != '3' && level->fake_map[y][x] != '\0')
	{
		if (level->fake_map[y][x] == ' ')
			level->fake_map[y][x] = '3';
		else
			level->fake_map[y][x] = '2';
		flood_map (data, level, x + 1, y);
		flood_map (data, level, x + 1, y + 1);
		flood_map (data, level, x, y + 1);
		flood_map (data, level, x - 1, y + 1);
		flood_map (data, level, x - 1, y);
		flood_map (data, level, x - 1, y - 1);
		flood_map (data, level, x, y - 1);
		flood_map (data, level, x + 1, y - 1);
	}
	check_flood(data, level);
}

void	check_flood(t_data *data, t_level *level)
{
	int	x;
	int	y;

	y = 0;
	while (level->fake_map[y])
	{
		x = 0;
		while (level->fake_map[y][x])
		{
			if (level->fake_map[y][x] == '3' && level->fake_map[0][0] == ' ')
				exit_error(data, "Error\nInvalid map, whitespaces inside map\n",
					STDERR_FILENO);
			if (!ft_strchr("0NSEW", level->fake_map[y][x]))
				x++;
			else
				break ;
		}
		if (level->fake_map[y][x] == '0')
			flood_map(data, level, x, y);
		else
			y++;
	}
}

void	validate_map(t_data *data, t_level *level)
{
	copy_map(data, level);
	check_flood(data, level);
	check_flood(data, level);
	if (level->fake_map[0][0] == '3')
		exit_error(data, "Error\nInvalid map, open walls\n", STDERR_FILENO);
}
