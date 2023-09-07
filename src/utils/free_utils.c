/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:38:38 by aoropeza          #+#    #+#             */
/*   Updated: 2023/09/07 19:39:43 by aoropeza         ###   ########.fr       */
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
