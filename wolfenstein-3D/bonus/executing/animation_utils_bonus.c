/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:42:14 by alassiqu          #+#    #+#             */
/*   Updated: 2024/10/27 14:06:08 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	focus_shoot(t_cub3d *cub)
{
	static int	delay = 16;

	delay++;
	if (delay >= 22)
	{
		draw_gun(cub, 15);
		delay = 16;
		cub->info_gun.is_shoot = 0;
		return ;
	}
	draw_gun(cub, delay);
}

int	gun_shots(t_cub3d *cub)
{
	if (cub->info_gun.state_hand == 0)
		default_shoot(cub);
	else
		focus_shoot(cub);
	return (1);
}

void	reload_gun(t_cub3d *cub)
{
	static int	delay = 46;

	delay++;
	if (delay >= 73)
	{
		if (cub->info_gun.state_hand == 0)
			draw_gun(cub, 0);
		else
		{
			draw_gun(cub, 0);
			cub->info_gun.state_hand = 0;
		}
		cub->info_gun.is_reload = 0;
		delay = 46;
		return ;
	}
	draw_gun(cub, delay);
}

void	gun_focus(t_cub3d *cub)
{
	static int	delay = 11;

	if (cub->info_gun.state_hand == 1)
	{
		draw_gun(cub, 15);
		return ;
	}
	delay++;
	if (delay >= 16)
	{
		draw_gun(cub, 15);
		cub->info_gun.state_hand = 1;
		delay = 11;
		return ;
	}
	draw_gun(cub, delay);
}

void	gun_default_view(t_cub3d *cub)
{
	static int	delay = 25;

	if (cub->info_gun.state_hand == 0)
	{
		draw_gun(cub, 0);
		return ;
	}
	delay++;
	if (delay >= 36)
	{
		draw_gun(cub, 0);
		cub->info_gun.state_hand = 0;
		delay = 25;
		return ;
	}
	draw_gun(cub, delay);
}
