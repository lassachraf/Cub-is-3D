/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:34:39 by alassiqu          #+#    #+#             */
/*   Updated: 2024/11/15 00:23:53 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_it_player(char c)
{
	return (c == 'W' || c == 'N' || c == 'S' || c == 'E');
}

void	alloc_and_set(t_cub3d *cub)
{
	cub->player = calloc(1, sizeof(t_player));
	if (cub->player == NULL)
		ft_error(cub, "Error.\nAllocation failed.");
	cub->player->fov = deg_to_rad(60);
	cub->player->movespeed = 6;
	cub->player->rotationspeed = 3 * (PI / 180);
}

float	get_angle(char c)
{
	if (c == 'E')
		return (deg_to_rad(0));
	if (c == 'S')
		return (deg_to_rad(90));
	if (c == 'W')
		return (deg_to_rad(180));
	if (c == 'N')
		return (deg_to_rad(270));
	return (-1);
}

void	get_player(t_cub3d *cub)
{
	char	**map;
	int		i;
	int		j;

	alloc_and_set(cub);
	map = cub->map->map;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (is_it_player(map[i][j]))
			{
				cub->player->rot_ang = get_angle(map[i][j]);
				cub->player->x = j + 0.5;
				cub->player->y = i + 0.5;
				cub->player->count++;
			}
		}
	}
	if (cub->player->count != 1)
		ft_error(cub, "Error.\nThe game need one player.");
}
