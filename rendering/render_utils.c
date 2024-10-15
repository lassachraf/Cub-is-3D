/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:51:08 by alassiqu          #+#    #+#             */
/*   Updated: 2024/10/15 19:45:19 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	my_mlx_pixel_put(t_cub3d *cub, float x, float y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= cub->wov || y >= cub->hov)
		return ;
	dst = cub->add + (int)(y * cub->szl + x * (cub->bpp / 8));
	*(unsigned int*)dst = color;
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

int	reset(int keycode, t_cub3d *cub)
{
	if (keycode == LEFT_ARROW || keycode == RIGHT_ARROW)
		cub->player->turndirection = 0;
	else if (keycode == W_KEY || keycode == S_KEY)
		cub->player->walkdirection = 0;
	else if (keycode == A_KEY || keycode == D_KEY)
		cub->player->sidedirection = 0;
	return (0);
}

int	ft_moving(int keycode, t_cub3d *cub)
{
	if (keycode == ESC_KEY)
		ft_exit(cub);
	else if (keycode == LEFT_ARROW)
		cub->player->turndirection = -1;
	else if (keycode == RIGHT_ARROW)
		cub->player->turndirection = 1;
	else if (keycode == W_KEY)
		cub->player->walkdirection = 1;
	else if (keycode == S_KEY)
		cub->player->walkdirection = -1;
	else if (keycode == A_KEY)
		cub->player->sidedirection = -1;
	else if (keycode == D_KEY)
		cub->player->sidedirection = 1;
	else if (keycode == O_KEY && cub->oc_door == 0)
		cub->oc_door = 1;
	else if (keycode == C_KEY && cub->oc_door == 1
		&& !player_in_doorway(cub))
		cub->oc_door = 0;
	else if (keycode == G_KEY && printf("Shooting now!\n"))
		cub->person = 1;
	// else if (keycode == R_KEY) // R keycode;
	// 	cub->reload = 1;
	update(cub);
	return (reset(keycode, cub), 0);
}
