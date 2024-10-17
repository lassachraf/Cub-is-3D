/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:39:53 by alassiqu          #+#    #+#             */
/*   Updated: 2024/10/17 17:50:04 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	is_walkable(t_cub3d *cub, float new_x, float new_y)
{
	if (new_x >= 0 && new_x < cub->map->width
		&& new_y >= 0 && new_y < cub->map->height)
	{
		if (cub->map->map[(int)new_y][(int)new_x] != '1')
		{
			cub->player->x = new_x;
			cub->player->y = new_y;
		}
	}
}

void	update(t_cub3d *cub)
{
	float	new_x;
	float	new_y;
	float	angle;
	float	movestep;

	angle = 0;
	new_x = 0;
	new_y = 0;
	if (cub->player->walkdirection)
	{
		movestep = cub->player->walkdirection * cub->player->movespeed;
		new_x = cub->player->x + cos(cub->player->rot_ang) * movestep;
		new_y = cub->player->y + sin(cub->player->rot_ang) * movestep;
	}
	else if (cub->player->sidedirection)
	{
		movestep = cub->player->sidedirection * cub->player->movespeed;
		angle = cub->player->rot_ang + (PI / 2);
		new_x = cub->player->x + cos(angle) * movestep;
		new_y = cub->player->y + sin(angle) * movestep;
	}
	if (cub->player->walkdirection || cub->player->sidedirection)
		is_walkable(cub, new_x, new_y);
    angle = cub->player->turndirection * cub->player->rotationspeed;
	cub->player->rot_ang += angle;
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
	if (keycode == ESC)
		ft_exit(cub);
	else if (keycode == L)
		cub->player->turndirection = -1;
	else if (keycode == R)
		cub->player->turndirection = 1;
	else if (keycode == W)
		cub->player->walkdirection = 1;
	else if (keycode == S)
		cub->player->walkdirection = -1;
	else if (keycode == A)
		cub->player->sidedirection = -1;
	else if (keycode == D)
		cub->player->sidedirection = 1;
	update(cub);
	reset(keycode, cub);
	return (0);
}
