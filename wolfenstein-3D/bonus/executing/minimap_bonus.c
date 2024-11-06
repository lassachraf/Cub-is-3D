/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:49:15 by alassiqu          #+#    #+#             */
/*   Updated: 2024/11/06 22:06:34 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	draw_player(t_cub3d *cub, int tile_size, int radius, int color)
{
	int	i;
	int	j;
	int	x;
	int	y;

	x = 20 + cub->player->x * tile_size;
	y = 20 + cub->player->y * tile_size;
	j = -radius;
	while (j <= radius)
	{
		i = -radius;
		while (i <= radius)
		{
			if (i * i + j * j <= radius * radius)
				my_mlx_pixel_put(cub, x + i, y + j, color);
			i++;
		}
		j++;
	}
}

void	draw_mini(t_cub3d *cub, t_minimap mini, int a, int b)
{
	int	i;
	int	j;
	int	x;
	int	y;

	if (cub->map->map[b][a] == '1')
		mini.color = 0x483D8B;
	else if (cub->map->map[b][a] == 'D' && cub->oc_door == 0)
		mini.color = 0x3CB371;
	else if (cub->map->map[b][a] == '0' || is_it_player(cub->map->map[b][a])
		|| cub->map->map[b][a] == 'D')
		mini.color = 0xFFFACD;
	else
		return ;
	j = -1;
	while (++j < mini.tile_size)
	{
		i = -1;
		while (++i < mini.tile_size)
		{
			x = 20 + a * mini.tile_size + i;
			y = 20 + b * mini.tile_size + j;
			my_mlx_pixel_put(cub, x, y, mini.color);
		}
	}
}

void	draw_minimap(t_cub3d *cub)
{
	t_minimap	mini;
	int			map_x;
	int			map_y;

	mini.max_map_size = cub->map->height - 1;
	if (cub->map->width > cub->map->height)
		mini.max_map_size = cub->map->width;
	mini.max_mini_size = cub->wov / 7 - 20;
	mini.tile_size = mini.max_mini_size / mini.max_map_size;
	if (mini.tile_size < 4)
		mini.tile_size = 4;
	mini.player_radius = mini.tile_size / 2;
	if (mini.player_radius > 10)
		mini.player_radius = 9;
	map_y = -1;
	while (++map_y < cub->map->height)
	{
		map_x = -1;
		while (++map_x < cub->map->width)
			draw_mini(cub, mini, map_x, map_y);
	}
	draw_player(cub, mini.tile_size, mini.player_radius, 0xFF4500);
}
