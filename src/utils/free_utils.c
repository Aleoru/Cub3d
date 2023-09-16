/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:38:38 by aoropeza          #+#    #+#             */
/*   Updated: 2023/09/16 19:46:31 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

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

void	free_level(t_level *level)
{
	free_split(level->file_map);
	free_split(level->map);
	free_split(level->fake_map);
	free(level->no_path);
	free(level->so_path);
	free(level->ea_path);
	free(level->we_path);
}
