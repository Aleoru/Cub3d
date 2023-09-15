/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 18:39:03 by aoropeza          #+#    #+#             */
/*   Updated: 2023/09/15 20:45:38 by aoropeza         ###   ########.fr       */
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
			printf("ERROR\nExtension incorrecta\n");
	}
	else
		printf("ERROR\nNo tiene extension\n");
}

static void	validate_color(char	*c)
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
	{
		printf("Color no válido\n");
		exit (1);
	}
}

static int	get_rgb(t_level *level, char *str)
{
	int		r;
	int		g;
	int		b;
	int		i;
	char	**rgb;

	(void)level;
	i = 0;
	rgb = ft_split(str, ',');
	rgb[2][ft_strlen(rgb[2]) - 1] = '\0';
	while (rgb[i] && i < 3)
		validate_color(rgb[i++]);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	printf("%d, %d, %d\n", r, g, b);
	if (r > 255 || g > 255 || b > 255)
	{
		printf("Color no válido\n");
		return (0);
	}
	free_split(rgb);
	return (r << 24 | g << 16 | b << 8 | 255);
}

static void	extract_elements(t_level *level, char **split)
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
		level->f_color = get_rgb(level, split[1]);
	else if (!ft_strncmp(split[0], C, ft_strlen(split[0])
			|| ft_strlen(split[0]) != 2))
		level->c_color = get_rgb(level, split[1]);
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
		printf("ERROR\nFile not found\n");
	else
	{
		while (n < ELEM)
		{
			line = get_next_line(level->fd);
			level->f_size++;
			split = ft_split(line, ' ');
			if (!ft_strchr(split[0], '\n'))
			{
				extract_elements(level, split);
				n++;
			}
			free(line);
			free_split(split);
		}
	}
}

static void	get_map_size(t_data *data, t_level *level)
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
	printf("\nX: %d, Y: %d\nFILE SIZE: %d\n\n", level->size_x, level->size_y, level->f_size);
	close(level->fd);
}

static void	parsing_map(t_data *data, t_level *level)
{
	int		x;
	int		y;
	char	*line;

	(void)data;
	y = 0;
	level->map = ft_calloc((level->size_y + 3) * sizeof(char),
			(level->size_x + 3) * sizeof(char));
	line = malloc(sizeof(char) * (level->size_x + 3));
	while (y < level->size_y + 2)
	{
		x = 0;
		while (x < level->size_x + 1)
			line[x++] = ' ';
		line[x] = '\0';
		level->map[y] = ft_strdup(line);
		printf("%d:	%s\n", y, level->map[y]);
		y++;
	}
	level->map[y] = NULL;
	puts("");
	y = 0;
	while (level->file_map[y])
	{
		x = 0;
		while (level->file_map[y][x + 1] != '\0')
		{
			level->map[y + 1][x + 1] = level->file_map[y][x];
			x++;
		}
		printf("%d:	%s\n", y, level->map[y]);
		y++;
	}
	printf("%d:	%s\n", y, level->map[y]);
	printf("%d:	%s\n", y + 1, level->map[y + 1]);
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
	(void)data;
	level->size_x = 0;
	level->size_y = 0;
	level->f_size = 0;
	level->path = ft_strjoin("assets/maps/", str);
	validate_map_path(data, level->path);
	read_map_elements(data, level);
	get_map_size(data, level);
	read_map(data, level);
	parsing_map(data, level);
	validate_map(data, level, level->map);
	free(level->path);
	free_level(level);
	exit (0);
}