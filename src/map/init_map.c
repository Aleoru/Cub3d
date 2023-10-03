/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 18:57:28 by aoropeza          #+#    #+#             */
/*   Updated: 2023/10/03 19:23:01 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	validate_map_path(t_data *data, char *path)
{
	char	*ext;

	if (ft_strrchr(path, '.'))
	{
		ext = ft_strrchr(path, '.');
		if (ft_strncmp(ext, ".cub", ft_strlen(ext)) || ft_strlen(ext) != 4)
			exit_error(data, "Error\nWrong extension\n", STDERR_FILENO);
	}
	else
		exit_error(data, "Error\nWrong extension\n", STDERR_FILENO);
}

static void	extract_elements(t_data *data, t_level *level, char **split)
{
	if (!ft_strncmp(split[0], NO, ft_strlen(split[0])
			|| ft_strlen(split[0]) != 2))
		level->no_path = ft_strdup(split[1]);
	else if (!ft_strncmp(split[0], SO, ft_strlen(split[0])
			|| ft_strlen(split[0]) != 2))
		level->so_path = ft_strdup(split[1]);
	else if (!ft_strncmp(split[0], EA, ft_strlen(split[0])
			|| ft_strlen(split[0]) != 2))
		level->ea_path = ft_strdup(split[1]);
	else if (!ft_strncmp(split[0], WE, ft_strlen(split[0])
			|| ft_strlen(split[0]) != 2))
		level->we_path = ft_strdup(split[1]);
	else if (!ft_strncmp(split[0], F, ft_strlen(split[0])
			|| ft_strlen(split[0]) != 2))
		level->f_color = get_rgb(data, level, split[1]);
	else if (!ft_strncmp(split[0], C, ft_strlen(split[0])
			|| ft_strlen(split[0]) != 2))
		level->c_color = get_rgb(data, level, split[1]);
	else
		exit_error(data, "Error\nMissing elements\n", STDERR_FILENO);
}

static void	read_map_elements(t_data *data, t_level *level)
{
	char	*line;
	char	**split;

	level->fd = open(level->path, O_RDONLY);
	if (level->fd < 0)
		return (exit_error(data, "Error\nFile not found\n", 2));
	else
	{
		while (level->n_elems < ELEM)
		{
			line = get_next_line(level->fd);
			level->f_size++;
			split = ft_split(line, ' ');
			if (split_size(split) < 2
				&& ft_strncmp(split[0], "\n", ft_strlen(split[0])))
				exit_error(data, "Error\nMissing elements\n", STDERR_FILENO);
			if (!ft_strchr(split[0], '\n'))
			{
				extract_elements(data, level, split);
				level->n_elems++;
			}
			free(line);
			free_split(split);
		}
	}
}

static void	read_map(t_data *data, t_level *level)
{
	int		y;
	int		n;
	char	*line;

	(void)data;
	y = 0;
	n = level->f_size - level->size_y;
	level->file_map = malloc(sizeof(char *) * (level->size_y + 1));
	level->fd = open(level->path, O_RDONLY);
	while (n-- > 0)
	{
		line = get_next_line(level->fd);
		free(line);
	}
	level->file_map[y] = get_next_line(level->fd);
	while (level->file_map[y] != NULL)
	{
		y++;
		level->file_map[y] = get_next_line(level->fd);
	}
	level->file_map[y] = NULL;
	close(level->fd);
}

void	init_map(t_data *data, t_level *level, char *str)
{
	level->size_x = 0;
	level->size_y = 0;
	level->f_size = 0;
	level->path = ft_strjoin("assets/maps/", str);
	validate_map_path(data, level->path);
	read_map_elements(data, level);
	get_map_size(data, level);
	read_map(data, level);
	parsing_map(data, level);
	if (level->n_player < 1)
		exit_error(data, "Error\nMissing player on map\n", 2);
	else if (level->n_player > 1)
		exit_error(data, "Error\nMore than one player on map\n", 2);
	validate_map(data, level);
}
