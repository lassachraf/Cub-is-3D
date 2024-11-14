/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:51:44 by alassiqu          #+#    #+#             */
/*   Updated: 2024/11/15 00:10:00 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_extension(char *mapfile, char *ext)
{
	if (!access(mapfile, F_OK))
	{
		if (!ft_strncmp(&mapfile[ft_strlen(mapfile) - 4], ext, 5))
			return ;
		else
			ft_error(NULL, "Error.\nBad extension.");
	}
	else
		ft_error(NULL, "Error.\nCan't open mapfile.");
}
