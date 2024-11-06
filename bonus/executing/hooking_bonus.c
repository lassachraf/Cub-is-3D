/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooking_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:19:14 by alassiqu          #+#    #+#             */
/*   Updated: 2024/11/06 00:50:53 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	is_walkable(t_cub3d *cub, float new_x, float new_y)
{
	if (check_collision(cub, new_x, 0))
		cub->player->x += new_x / TILE_SIZE;
	if (check_collision(cub, 0, new_y))
		cub->player->y += new_y / TILE_SIZE;
}

void	update(t_cub3d *cub)
{
	float	angle;
	float	x_step;
	float	y_step;
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
	angle = cub->player->turndirection * cub->player->rotationspeed;
	cub->player->rot_ang += angle;
}

void	key_hooks(int keycode, t_cub3d *cub)
{
	if (keycode == LEFT_ARROW)
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
	else if (keycode == 31 && cub->oc_door == 0)
		cub->oc_door = 1;
	else if (keycode == 8 && cub->oc_door == 1 && !player_in_doorway(cub))
		cub->oc_door = 0;
	else if (keycode == 5)
		cub->info_gun.is_shoot = 1;
	else if (keycode == 15)
		cub->info_gun.is_reload = 1;
	else if (keycode == 3)
		cub->info_gun.is_focus = 1;
	else if (keycode == 9)
		cub->info_gun.is_focus = 0;
}

int	ft_reset(int keycode, t_cub3d *cub)
{
	if (keycode == LEFT_ARROW || keycode == RIGHT_ARROW)
		cub->player->turndirection = 0;
	else if (keycode == W_KEY || keycode == S_KEY)
		cub->player->walkdirection = 0;
	else if (keycode == D_KEY || keycode == A_KEY)
		cub->player->sidedirection = 0;
	return (0);
}

int	ft_moving(int keycode, t_cub3d *cub)
{
	if (keycode == ESC_KEY)
		ft_exit(cub);
	else
		key_hooks(keycode, cub);
	update(cub);
	return (0);
}
