/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:41:14 by alassiqu          #+#    #+#             */
/*   Updated: 2024/10/18 12:01:43 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	check_the_xs(t_cub3d *cub, float pt)
{
	if (cub->map->map[(int)cub->player->y][(int)(pt + 5) / TILE_SIZE] != '1'
		&& cub->map->map[(int)cub->player->y][(int)(pt - 5) / TILE_SIZE] != '1'
		&& (cub->map->map[(int)cub->player->y][(int)(pt + 5) / TILE_SIZE] != 'D'
		|| cub->oc_door == 1)
		&& (cub->map->map[(int)cub->player->y][(int)(pt - 5) / TILE_SIZE] != 'D'
		|| cub->oc_door == 1))
		return (1);
	return (0);
}

int	check_the_ys(t_cub3d *cub, float pt)
{
	if (cub->map->map[(int)(pt + 5) / TILE_SIZE][(int)cub->player->x] != '1'
		&& cub->map->map[(int)(pt - 5) / TILE_SIZE][(int)cub->player->x] != '1'
		&& (cub->map->map[(int)(pt + 5) / TILE_SIZE][(int)cub->player->x] != 'D'
		|| cub->oc_door == 1)
		&& (cub->map->map[(int)(pt - 5) / TILE_SIZE][(int)cub->player->x] != 'D'
		|| cub->oc_door == 1))
		return (1);
	return (0);
}

int	collision_effect(t_cub3d *cub, float new_x, float new_y)
{
	int		counter;
	float	map_x;
	float	map_y;

	counter = 0;
	map_x = ((cub->player->x * TILE_SIZE) + new_x);
	map_y = ((cub->player->y * TILE_SIZE) + new_y);
	if (map_x >= 0 && map_x < cub->wov
		&& map_y >= 0 && map_y < cub->hov)
	{
		if (check_the_xs(cub, map_x))
		{
			cub->player->x = map_x / TILE_SIZE;
			counter++;
		}
		if (check_the_ys(cub, map_y))
		{
			cub->player->y = map_y / TILE_SIZE;
			counter++;
		}
		if (counter == 2)
			return (1);
	}
	return (0);
}
