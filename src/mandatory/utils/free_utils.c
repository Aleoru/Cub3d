/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:38:38 by aoropeza          #+#    #+#             */
/*   Updated: 2023/10/20 18:51:26 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3D.h"

void	free_split(char **split)
{
	int		i;

	i = 0;
	while (split[i] != NULL)
		i++;
	while (i >= 0)
	{
		free(split[i]);
		i--;
	}
	free(split);
}

void	free_level(t_data *data, t_level *level)
{
	if (level->file_map)
		free_split(level->file_map);
	if (data->map)
		free_split(data->map);
	if (level->fake_map)
		free_split(level->fake_map);
	if (level->path)
		free(level->path);
	if (level->no_path)
		free(level->no_path);
	if (level->so_path)
		free(level->so_path);
	if (level->ea_path)
		free(level->ea_path);
	if (level->we_path)
		free(level->we_path);
}
