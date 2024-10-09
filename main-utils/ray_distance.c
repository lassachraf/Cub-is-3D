/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_distance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:23:15 by alassiqu          #+#    #+#             */
/*   Updated: 2024/10/09 18:03:59 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

float	calculate_ray_distance(t_cub3d *cub, float ray_angle)
{
	int     map_x, map_y;
	float   side_dist_x, side_dist_y;
	float   delta_dist_x, delta_dist_y;
	float   perp_wall_dist;
	int     step_x, step_y;
	int     hit = 0;
	int     side;

	map_x = (int)cub->player->x;
	map_y = (int)cub->player->y;

	float ray_dir_x = cos(ray_angle);
	float ray_dir_y = sin(ray_angle);

	delta_dist_x = fabs(1 / ray_dir_x);
	delta_dist_y = fabs(1 / ray_dir_y);
	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (cub->player->x - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - cub->player->x) * delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (cub->player->y - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - cub->player->y) * delta_dist_y;
	}
	while (hit == 0)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0;  // Hit vertical side (x-direction)
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1;  // Hit horizontal side (y-direction)
		}
		if (cub->map->map[map_y][map_x] == 'D')
			hit = 2;
		if (cub->map->map[map_y][map_x] == '1')
			hit = 1;
	}
	if (side == 0)
		perp_wall_dist = (map_x - cub->player->x + (1 - step_x) / 2) / ray_dir_x;
	else
		perp_wall_dist = (map_y - cub->player->y + (1 - step_y) / 2) / ray_dir_y;
	if (side == 0)
	{
		if (step_x < 0)
			cub->side = 2;  // West (ray is moving left)
		else
			cub->side = 3;  // East (ray is moving right)
	}
	else
	{
		if (step_y < 0)
			cub->side = 0;  // North (ray is moving up)
		else
			cub->side = 1;  // South (ray is moving down)
	}
	if (hit == 2)
		cub->side = 4;

	return (perp_wall_dist);
	return (perp_wall_dist);
}
