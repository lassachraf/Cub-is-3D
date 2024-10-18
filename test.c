/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:15:55 by alassiqu          #+#    #+#             */
/*   Updated: 2024/10/18 12:10:09 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"


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

void	is_walkable(t_cub3d *cub, float new_x, float new_y)
{
	float	map_x;
	float	map_y;

	map_x = ((cub->player->x * TILE_SIZE) + new_x) / TILE_SIZE;
	map_y = ((cub->player->y * TILE_SIZE) + new_y) / TILE_SIZE;
	if (map_x >= 0 && map_x < cub->map->width
		&& map_y >= 0 && map_y < cub->map->height)
	{
		if (collision_effect(cub, new_x, new_y))
			return ;
		if (cub->map->map[(int)map_y][(int)map_x] == 'D')
		{
			if (cub->oc_door == 1)
			{
				cub->player->x = map_x;
				cub->player->y = map_y;
			}
		}
		else if (cub->map->map[(int)map_y][(int)map_x] != '1')
		{
			cub->player->x = map_x;
			cub->player->y = map_y;
		}
	}
}

void	update(t_cub3d *cub)
{
	float	x_step;
	float	y_step;
	float	angle;
	float	movestep;

	angle = 0;
	x_step = 0;
	y_step = 0;
	if (cub->player->walkdirection)
	{
		movestep = cub->player->walkdirection * cub->player->movespeed;
		x_step = cos(cub->player->rot_ang) * movestep;
		y_step = sin(cub->player->rot_ang) * movestep;
	}
	else if (cub->player->sidedirection)
	{
		movestep = cub->player->sidedirection * cub->player->movespeed;
		angle = cub->player->rot_ang + (PI / 2);
		x_step = cos(angle) * movestep;
		y_step = sin(angle) * movestep;
	}
	if (cub->player->walkdirection || cub->player->sidedirection)
		is_walkable(cub, x_step, y_step);
	cub->player->rot_ang += cub->player->turndirection * cub->player->rotationspeed;
}
