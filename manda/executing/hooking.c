/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:19:14 by alassiqu          #+#    #+#             */
/*   Updated: 2024/10/27 16:07:42 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	is_walkable(t_cub3d *cub, float new_x, float new_y)
{
	float	x;
	float	y;

	x = (cub->player->x + new_x);
	y = (cub->player->y + new_y);
	if ((int)x >= 0 && (int)x < cub->map->width
		&& (int)y >= 0 && (int)y < cub->map->height)
	{
		if (cub->map->map[(int)y][(int)x] != '1')
		{
			cub->player->x = x;
			cub->player->y = y;
		}
	}
}

void	update(t_cub3d *cub)
{
	float	angle;
	float	x_step;
	float	y_step;
	float	movestep;

	angle = 0;
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
	angle = cub->player->turndirection * cub->player->rotationspeed;
	cub->player->rot_ang += angle;
}

void	key_hooks(int keycode, t_cub3d *cub)
{
	if (keycode == 123)
		cub->player->turndirection = -1;
	else if (keycode == 124)
		cub->player->turndirection = 1;
	else if (keycode == 13)
		cub->player->walkdirection = 1;
	else if (keycode == 1)
		cub->player->walkdirection = -1;
	else if (keycode == 0)
		cub->player->sidedirection = -1;
	else if (keycode == 2)
		cub->player->sidedirection = 1;
}

int	ft_reset(int keycode, t_cub3d *cub)
{
	if (keycode == 123 || keycode == 124)
		cub->player->turndirection = 0;
	else if (keycode == 13 || keycode == 1)
		cub->player->walkdirection = 0;
	else if (keycode == 0 || keycode == 2)
		cub->player->sidedirection = 0;
	return (0);
}

int	ft_moving(int keycode, t_cub3d *cub)
{
	if (keycode == 53)
		ft_exit(cub);
	else
		key_hooks(keycode, cub);
	update(cub);
	return (0);
}
