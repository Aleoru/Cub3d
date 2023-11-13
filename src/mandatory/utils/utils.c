/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 18:30:58 by aoropeza          #+#    #+#             */
/*   Updated: 2023/11/13 20:19:48 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3D.h"

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

int	check_tags(t_level *level, char *tag)
{
	if (!ft_strncmp(tag, NO, ft_strlen(tag) || ft_strlen(tag) != 2))
		if (level->no_check == 0)
			return (level->no_check = 1, 0);
	if (!ft_strncmp(tag, SO, ft_strlen(tag) || ft_strlen(tag) != 2))
		if (level->so_check == 0)
			return (level->so_check = 1, 0);
	if (!ft_strncmp(tag, WE, ft_strlen(tag) || ft_strlen(tag) != 2))
		if (level->we_check == 0)
			return (level->we_check = 1, 0);
	if (!ft_strncmp(tag, EA, ft_strlen(tag) || ft_strlen(tag) != 2))
		if (level->ea_check == 0)
			return (level->ea_check = 1, 0);
	if ((!ft_strncmp(tag, F, ft_strlen(tag) || ft_strlen(tag) != 1))
		|| (!ft_strncmp(tag, C, ft_strlen(tag) || ft_strlen(tag) != 1)))
		return (0);
	return (1);
}
