/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 18:39:03 by aoropeza          #+#    #+#             */
/*   Updated: 2023/11/14 20:44:35 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3D_bonus.h"

static void	validate_color(t_data *data, char	*c)
{
	size_t	i;

	i = 0;
	while (c[i])
	{
		if (!ft_isdigit(c[i]))
			break ;
		i++;
	}
	if (i != ft_strlen(c))
		exit_error(data, "ERROR\nInvalid Color\n", 2);
}

int	get_rgb(t_data *data, char *str)
{
	int		r;
	int		g;
	int		b;
	int		i;
	char	**rgb;

	i = 0;
	rgb = ft_split(str, ',');
	rgb[2][ft_strlen(rgb[2]) - 1] = '\0';
	while (rgb[i] && i < 3)
		validate_color(data, rgb[i++]);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r > 255 || g > 255 || b > 255)
		exit_error(data, "Error\nInvalid color\n", 2);
	free_split(rgb);
	return (r << 24 | g << 16 | b << 8 | 255);
}

void	get_map_size(t_data *data, t_level *level)
{
	char	*line;

	(void)data;
	line = get_next_line(level->fd);
	while (!ft_strchr(line, '1'))
	{
		free(line);
		line = get_next_line(level->fd);
		level->f_size++;
	}
	while (line != NULL && ft_strchr(line, '1'))
	{
		free(line);
		line = get_next_line(level->fd);
		level->f_size++;
		if (line == NULL)
			break ;
		if (ft_strlen(line) > (size_t)level->size_x)
			level->size_x = ft_strlen(line);
		level->size_y++;
	}
	level->size_y++;
	free(line);
	close(level->fd);
}

static void	parsing_map2(t_data *data, t_level *level)
{
	int	x;
	int	y;

	y = -1;
	while (level->file_map[++y])
	{
		x = -1;
		while (level->file_map[y][++x] != '\0')
		{
			if (!ft_strchr("10NSEWABCD \n", level->file_map[y][x]))
				exit_error(data, "Error\nInvalid character on map\n", 2);
			if (ft_strchr("NSEW", level->file_map[y][x]))
			{
				data->ply_pos.x = (x + 1) * data->cl_size + data->cl_size / 2;
				data->ply_pos.y = (y + 1) * data->cl_size + data->cl_size / 2;
				level->n_player++;
				level->direction = level->file_map[y][x];
				check_player_pos(data, level, x, y);
			}
			if (ft_strchr("ABC", level->file_map[y][x]))
				add_sprite(data, x, y, level->file_map[y][x]);
			if (level->file_map[y][x] != '\n')
				data->map[y + 1][x + 1] = level->file_map[y][x];
		}
	}
}

void	parsing_map(t_data *data, t_level *level)
{
	int		x;
	int		y;
	char	*line;

	y = 0;
	data->map = ft_calloc((level->size_y + 3) * sizeof(char),
			(level->size_x + 3) * sizeof(char));
	line = malloc(sizeof(char) * (level->size_x + 3));
	while (y < level->size_y + 2)
	{
		x = 0;
		while (x < level->size_x + 1)
			line[x++] = ' ';
		line[x] = '\0';
		data->map[y++] = ft_strdup(line);
	}
	data->map[y] = NULL;
	free(line);
	parsing_map2(data, level);
}
