/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:51:44 by alassiqu          #+#    #+#             */
/*   Updated: 2024/10/06 17:25:38 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	ft_open(t_cub3d *cub, char *filename)
{
	cub->map->fd = open(filename, O_RDONLY);
	if (cub->map->fd == -1)
		ft_error(cub, "Error: Can't open map file.");
}

void	ft_extension(char *mapfile, char *ext)
{
	if (!access(mapfile, F_OK))
	{
		if (!ft_strncmp(&mapfile[ft_strlen(mapfile) - 4], ext, 5)
			&& ft_strlen(mapfile) > 4)
			return ;
		else
			ft_error(NULL, "Error: extension error.");
	}
	else
		ft_error(NULL, "Error: file doesn't exist.");
}
