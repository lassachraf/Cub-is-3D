/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:42:45 by alassiqu          #+#    #+#             */
/*   Updated: 2024/10/06 19:21:19 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	render_square(t_cub3d *cub, float x, float y, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < TILE_SIZE)
	{
		j = -1;
		while (++j < TILE_SIZE)
			my_mlx_pixel_put(cub, x + i, y + j, color);
	}
}

void	render_circle(t_cub3d *cub, int cx, int cy, int radius, int color)
{
	int	x;
	int	y;

	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius * radius)
				my_mlx_pixel_put(cub, cx + x, cy + y, color);
			x++;
		}
		y++;
	}
}

void	render_player(t_cub3d *cub, int x, int y)
{
	int	x_p;
	int	y_p;

	x_p = cub->player->x * TILE_SIZE + (TILE_SIZE / 2);
	y_p = cub->player->y * TILE_SIZE + (TILE_SIZE / 2);
	render_square(cub, x * TILE_SIZE, y * TILE_SIZE, 0x00CCCCCC);
	render_circle(cub, x_p, y_p, 6, 0x0099FFFF);
}

void	render_map_2(t_cub3d *cub)
{
	int x, y;

	y = -1;
	while (cub->map->map[++y])
	{
		x = -1;
		while (cub->map->map[y][++x])
		{
			if (cub->map->map[y][x] == '1')
				render_square(cub, x * TILE_SIZE, y * TILE_SIZE, 0x00FF0000);
			else if (cub->map->map[y][x] == 'D')
				render_square(cub, x * TILE_SIZE, y * TILE_SIZE, 0x000000FF);
			else if (cub->map->map[y][x] == ' ')
				render_square(cub, x * TILE_SIZE, y * TILE_SIZE, 0x0000);
			else
				render_player(cub, x, y);
		}
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img, 0, 0);
}

void    render_map(t_cub3d *cub)
{
	int x, y;

	y = -1;
	while (cub->map->map[++y])
	{
		x = -1;
		while (cub->map->map[y][++x])
		{
			if (cub->map->map[y][x] == '1')
				render_square(cub, x * TILE_SIZE, y * TILE_SIZE, 0x00FF0000);
			else if (cub->map->map[y][x] == 'D')
				render_square(cub, x * TILE_SIZE, y * TILE_SIZE, 0x000000FF);
			else
				render_square(cub, x * TILE_SIZE, y * TILE_SIZE, 0x00CCCCCC);
		}
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img, 0, 0);
}
