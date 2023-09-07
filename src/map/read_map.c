/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 18:39:03 by aoropeza          #+#    #+#             */
/*   Updated: 2023/09/07 19:51:16 by aoropeza         ###   ########.fr       */
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

static void	extract_elements(t_level *level, char **split)
{
	
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
		while (n < ELEM)
		{
			if (!ft_strncmp(split[0], NO, ft_strlen(split[0])
					|| ft_strlen(split[0]) != 2))
			{
				level->no_path = ft_strdup(split[1]);
				printf("%s\n", level->no_path);
				free(level->no_path);
			}
		}
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
