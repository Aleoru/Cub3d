/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 18:30:58 by aoropeza          #+#    #+#             */
/*   Updated: 2023/10/03 19:56:29 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

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
