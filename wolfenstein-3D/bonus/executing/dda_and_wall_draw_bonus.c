/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_and_wall_draw_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 23:17:18 by alassiqu          #+#    #+#             */
/*   Updated: 2024/11/06 22:09:56 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	my_mlx_pixel_put(t_cub3d *cub, float x, float y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= cub->wov || y >= cub->hov)
		return ;
	dst = cub->add + (int)(y * cub->szl + x * (cub->bpp / 8));
	*(unsigned int *)dst = color;
}

void	dda(t_cub3d *cub, float *xy)
{
	int		i;
	float	xp;
	float	yp;
	float	steps;

	xp = cub->player->x;
	yp = cub->player->y;
	if (fabs(xy[0] - xp) > fabs(xy[1] - yp))
		steps = fabs(xy[0] - xp);
	else
		steps = fabs(xy[1] - yp);
	i = -1;
	while (++i <= steps)
	{
		xp += (xy[0] - xp) / steps;
		yp += (xy[1] - yp) / steps;
	}
	free(xy);
}

void	set_textures(t_cub3d *cub, t_tex **tex)
{
	if (cub->side == 0)
		*tex = cub->map->north;
	if (cub->side == 1)
		*tex = cub->map->south;
	if (cub->side == 2)
		*tex = cub->map->west;
	if (cub->side == 3)
		*tex = cub->map->east;
	if (cub->side == 4)
		*tex = cub->door;
}

void	init_wall(t_cub3d *cub, t_ray ray, t_wall *wall)
{
	wall->end = (cub->hov / 2) + (ray.wall_h / 2);
	wall->start = (cub->hov / 2) - (ray.wall_h / 2);
	if (wall->start < 0)
		wall->start = 0;
	if (wall->end > cub->hov)
		wall->end = cub->hov;
	if (cub->side == 4)
	{
		if (ray.side == 0)
			wall->wall_x = cub->player->y + ray.ray_dist * ray.ray_y;
		else
			wall->wall_x = cub->player->x + ray.ray_dist * ray.ray_x;
	}
	else if (cub->side == 2 || cub->side == 3)
		wall->wall_x = cub->player->y + ray.ray_dist * ray.ray_y;
	else
		wall->wall_x = cub->player->x + ray.ray_dist * ray.ray_x;
	wall->wall_x -= floor((wall->wall_x));
}

void	draw_wall_slice(t_cub3d *cub, t_ray ray, int x)
{
	int		i;
	int		d;
	t_wall	wall;
	t_tex	*texture;

	init_wall(cub, ray, &wall);
	set_textures(cub, &texture);
	wall.tex_x = wall.wall_x * (double)texture->width;
	if ((cub->side == 0 && ray.ray_y < 0) || (cub->side == 1 && ray.ray_y > 0))
		wall.tex_x = texture->width - wall.tex_x - 1;
	else if (cub->side == 2 && ray.ray_x < 0)
		wall.tex_x = texture->width - wall.tex_x - 1;
	else if (cub->side == 3 && ray.ray_x > 0)
		wall.tex_x = texture->width - wall.tex_x - 1;
	i = wall.start - 1;
	while (++i < wall.end)
	{
		d = i * 256 - cub->hov * 128 + ray.wall_h * 128;
		wall.tex_y = ((d * texture->height) / ray.wall_h) / 256;
		wall.tex_y = (int)wall.tex_y % texture->height;
		wall.color = get_texture_color(texture, wall.tex_x, wall.tex_y);
		my_mlx_pixel_put(cub, x, i, wall.color);
	}
}
