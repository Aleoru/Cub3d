/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 18:30:58 by aoropeza          #+#    #+#             */
/*   Updated: 2023/10/20 20:27:01 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3D_bonus.h"

size_t	split_size(char **split)
{
	size_t	size;

	size = 0;
	while (split[size])
		size++;
	return (size);
}

char	*delete_nl(char	*str)
{
	int	x;

	x = 0;
	while (str[x] != '\n')
		x++;
	str[x] = '\0';
	return (str);
}

int	check_img(t_level *level)
{
	int	fd;

	fd = open(level->no_path, O_RDONLY);
	if (fd == -1)
		return (close(fd), -1);
	close(fd);
	fd = open(level->so_path, O_RDONLY);
	if (fd == -1)
		return (close(fd), -1);
	close(fd);
	fd = open(level->ea_path, O_RDONLY);
	if (fd == -1)
		return (close(fd), -1);
	close(fd);
	fd = open(level->we_path, O_RDONLY);
	if (fd == -1)
		return (close(fd), -1);
	close(fd);
	return (0);
}
