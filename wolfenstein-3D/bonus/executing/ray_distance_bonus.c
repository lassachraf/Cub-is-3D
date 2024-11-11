/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_distance_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:23:15 by alassiqu          #+#    #+#             */
/*   Updated: 2024/11/11 16:26:43 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	precise_step_side(t_cub3d *cub, t_ray *ray)
{
	if (ray->ray_x < 0)
	{
		ray->step_x = -1;
		ray->side_x = (cub->player->x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_x = (ray->map_x + 1.0 - cub->player->x) * ray->delta_x;
	}
	if (ray->ray_y < 0)
	{
		ray->step_y = -1;
		ray->side_y = (cub->player->y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_y = (ray->map_y + 1.0 - cub->player->y) * ray->delta_y;
	}
}

void	set_texture_side(t_cub3d *cub, t_ray *ray)
{
	if (ray->side == 0)
		ray->fl_dist = (ray->map_x - cub->player->x + (1 - ray->step_x) / 2)
			/ ray->ray_x;
	else
		ray->fl_dist = (ray->map_y - cub->player->y + (1 - ray->step_y) / 2)
			/ ray->ray_y;
	if (ray->side == 0)
	{
		if (ray->step_x < 0)
			cub->side = 2;
		else
			cub->side = 3;
	}
	else
	{
		if (ray->step_y < 0)
			cub->side = 0;
		else
			cub->side = 1;
	}
	if (ray->hit == 2)
		cub->side = 4;
}

void	init_ray(t_cub3d *cub, t_ray *ray)
{
	ray->hit = 0;
	ray->map_x = (int)cub->player->x;
	ray->map_y = (int)cub->player->y;
	ray->ray_x = cos(ray->curr_ang);
	ray->ray_y = sin(ray->curr_ang);
	ray->delta_x = fabs(1 / ray->ray_x);
	ray->delta_y = fabs(1 / ray->ray_y);
}

float	calculate_ray_distance(t_cub3d *cub, t_ray *ray)
{
	init_ray(cub, ray);
	precise_step_side(cub, ray);
	while (ray->hit == 0)
	{
		if (ray->side_x < ray->side_y)
		{
			ray->side_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (cub->map->map[ray->map_y][ray->map_x] == 'D' && !cub->oc_door)
			ray->hit = 2;
		if (cub->map->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
	set_texture_side(cub, ray);
	return (ray->fl_dist);
}
