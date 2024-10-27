/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:41:14 by alassiqu          #+#    #+#             */
/*   Updated: 2024/10/27 14:24:13 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	detect_collision(t_cub3d *cub, float x, float y)
{
	int		off_x;
	int		off_y;
	int		check_x;
	int		check_y;
	char	adjacent;

	off_x = -2;
	while (++off_x <= 1)
	{
		off_y = -2;
		while (++off_y <= 1)
		{
			check_x = (int)((x + off_x * 5) / TILE_SIZE);
			check_y = (int)((y + off_y * 5) / TILE_SIZE);
			if (check_x >= 0 && check_x < cub->map->width
				&& check_y >= 0 && check_y < cub->map->height)
			{
				adjacent = cub->map->map[check_y][check_x];
				if (adjacent == '1'
					|| (adjacent == 'D' && cub->oc_door == 0))
					return (0);
			}
		}
	}
	return (1);
}

int	check_collision(t_cub3d *cub, float new_x, float new_y)
{
	int		tile_x;
	int		tile_y;
	char	main_tile;
	float	projected_x;
	float	projected_y;

	projected_x = cub->player->x * TILE_SIZE + new_x;
	projected_y = cub->player->y * TILE_SIZE + new_y;
	tile_x = (int)(projected_x / TILE_SIZE);
	tile_y = (int)(projected_y / TILE_SIZE);
	if (tile_x >= 0 && tile_x < cub->map->width
		&& tile_y >= 0 && tile_y < cub->map->height)
	{
		main_tile = cub->map->map[tile_y][tile_x];
		if (main_tile == '1' || (main_tile == 'D' && cub->oc_door == 0))
			return (0);
	}
	if (detect_collision(cub, projected_x, projected_y) == 0)
		return (0);
	return (1);
}
