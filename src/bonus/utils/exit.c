/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:07:46 by aoropeza          #+#    #+#             */
/*   Updated: 2023/10/20 19:31:00 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3D_bonus.h"

void	exit_error(t_data *data, char *str, int fd)
{
	ft_putstr_fd(str, fd);
	free_level(data, &data->level);
	exit(1);
}
