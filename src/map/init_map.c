/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 18:57:28 by aoropeza          #+#    #+#             */
/*   Updated: 2023/09/23 12:04:24 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	validate_map_path(t_data *data, char *path)
{
	char	*ext;

	(void)data;
	if (ft_strrchr(path, '.'))
	{
		ext = ft_strrchr(path, '.');
		if (ft_strncmp(ext, ".cub", ft_strlen(ext)) || ft_strlen(ext) != 4)
		{
			ft_putstr_fd("Error\nWrong extension\n", STDERR_FILENO);
			exit_error(data);
		}
	}
	else
	{
		ft_putstr_fd("Error\nWrong extension\n", STDERR_FILENO);
		exit_error(data);
	}
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
}

static void	read_map_elements(t_data *data, t_level *level)
{
	int		n;
	char	*line;
	char	**split;

	(void)data;
	level->fd = open(level->path, O_RDONLY);
	n = 0;
	if (level->fd < 0)
	{
		ft_putstr_fd("Error\nFile not found\n", STDERR_FILENO);
		exit_error(data);
	}
	else
	{
		while (n < ELEM)
		{
			line = get_next_line(level->fd);
			level->f_size++;
			split = ft_split(line, ' ');
			if (!ft_strchr(split[0], '\n'))
			{
				extract_elements(data, level, split);
				n++;
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
	parsing_map(level);
	validate_map(data, level);
	free_level(level);
	exit (0);
}
