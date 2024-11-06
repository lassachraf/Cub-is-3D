/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:51:44 by alassiqu          #+#    #+#             */
/*   Updated: 2024/11/06 22:52:28 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	ft_open(t_cub3d *cub, char *filename)
{
	cub->map->fd = open(filename, O_RDONLY);
	if (cub->map->fd == -1)
		ft_error(cub, "Error.");
}

void	ft_extension(char *mapfile, char *ext)
{
	if (!access(mapfile, F_OK))
	{
		if (!ft_strncmp(&mapfile[ft_strlen(mapfile) - 4], ext, 5))
			return ;
		else
			ft_error(NULL, "Error.");
	}
	else
		ft_error(NULL, "Error.");
}
