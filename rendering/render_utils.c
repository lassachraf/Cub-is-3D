/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:51:08 by alassiqu          #+#    #+#             */
/*   Updated: 2024/10/09 20:16:21 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	my_mlx_pixel_put(t_cub3d *cub, float x, float y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= cub->map->width * TILE_SIZE
		|| y >= cub->map->height * TILE_SIZE)
		return ;
	dst = cub->add + (int)(y * cub->szl + x * (cub->bpp / 8));
	*(unsigned int*)dst = color;
}

void	is_walkable(t_cub3d *cub, float new_x, float new_y)
{
	int map_x;
	int	map_y;

	map_x = (int)new_x;
	map_y = (int)new_y;
	if (map_x >= 0 && map_x < cub->map->width
		&& map_y >= 0 && map_y < cub->map->height
		&& cub->map->map[map_y][map_x] != '1'
		&& cub->map->map[map_y][map_x] != 'D')
	{
		cub->player->x = new_x;
		cub->player->y = new_y;
		return ;
	}
}

void	update(t_cub3d *cub)
{
	float	new_x;
	float	new_y;
	float	angle;
	float	movestep;

	angle = 0;
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
	is_walkable(cub, new_x, new_y);
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
	update(cub);
	reset(keycode, cub);
	return (0);
}
