/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 18:39:03 by aoropeza          #+#    #+#             */
/*   Updated: 2023/09/07 21:18:23 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	validate_map(t_data *data, char *path)
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

/* static int	rgb_to_hex(int n, int c, int r)
{
	c = n / 16;
	r = n % 16;

} */

static int	get_rgb(t_level *level, char *str)
{
	int		r;
	int		g;
	int		b;
	char	**rgb;

	(void)level;
	rgb = ft_split(str, ',');
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	printf("%d, %d, %d\n", r, g, b);
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
	int		fd;
	int		n;
	char	*line;
	char	**split;

	(void)data;
	fd = open(level->path, O_RDONLY);
	n = 0;
	if (fd < 0)
		printf("ERROR\nFile not found\n");
	else
	{
		line = get_next_line(fd);
		split = ft_split(line, ' ');
		while (n < 6)
		{
			extract_elements(level, split);
			line = get_next_line(fd);
			free_split(split);
			split = ft_split(line, ' ');
			n++;
		}
		ft_printf("%p\n", level->f_color);	// Hay que añadir de alguna manera de forma manual el 0x en el número decimal
		free(level->no_path);
		free(level->so_path);
		free(level->ea_path);
		free(level->we_path);
		free_split(split);
	}
}

void	init_map(t_data *data, t_level *level, char *str)
{
	(void)data;
	level->path = ft_strjoin("assets/maps/", str);
	validate_map(data, level->path);
	read_map_elements(data, level);
	free(level->path);
	exit (0);
}
