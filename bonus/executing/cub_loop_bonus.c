/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_loop_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:35:57 by alassiqu          #+#    #+#             */
/*   Updated: 2024/10/30 15:51:56 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

float	get_current_angle(float ray_start, float ang_inc, int x)
{
	float	angle;

	angle = ray_start + (x * ang_inc);
	return (normalize_angle(angle));
}

float	*get_index(t_cub3d *cub, float curr_ang, float ray_dist)
{
	float	*ray;

	ray = malloc(2 * sizeof(float));
	if (ray == NULL)
		ft_error(cub, "Error: allocation failed.");
	ray[0] = cub->player->x + cos(curr_ang) * ray_dist;
	ray[1] = cub->player->y + sin(curr_ang) * ray_dist;
	return (ray);
}

void	draw_c_wall_f(t_cub3d *cub, t_ray ray, int x)
{
	int	y;

	y = 0;
	while (y < ray.wall_t)
	{
		my_mlx_pixel_put(cub, x, y, cub->map->colors->ceil_h);
		y++;
	}
	draw_wall_slice(cub, ray, x);
	y = ray.wall_b;
	while (y < cub->hov)
	{
		my_mlx_pixel_put(cub, x, y, cub->map->colors->floor_h);
		y++;
	}
}

void	cast_fov(t_cub3d *cub)
{
	int		i;
	t_ray	ray;

	i = -1;
	ray.ang_inc = cub->player->fov / cub->wov;
	ray.ray_start = cub->player->rot_ang - (cub->player->fov / 2.0);
	while (++i < cub->wov)
	{
		ray.curr_ang = get_current_angle(ray.ray_start, ray.ang_inc, i);
		ray.ray_dist = calculate_ray_distance(cub, &ray);
		dda(cub, get_index(cub, ray.curr_ang, ray.ray_dist));
		ray.wall_h = (int)(cub->hov / ray.ray_dist);
		ray.wall_t = (cub->hov - ray.wall_h) / 2;
		ray.wall_b = ray.wall_t + ray.wall_h;
		draw_c_wall_f(cub, ray, i);
	}
}

int	cub_loop(t_cub3d *cub)
{
	update(cub);
	if (cub->img)
		mlx_destroy_image(cub->mlx, cub->img);
	cub->img = mlx_new_image(cub->mlx, cub->wov, cub->hov);
	if (cub->img == NULL)
		ft_error(cub, "Error.");
	cub->add = mlx_get_data_addr(cub->img, &cub->bpp, &cub->szl, &cub->end);
	if (cub->add == NULL)
		ft_error(cub, "Error.");
	cast_fov(cub);
	draw_minimap(cub);
	if (cub->info_gun.is_focus == 0 && cub->info_gun.is_reload == 0
		&& cub->info_gun.is_shoot == 0)
		gun_default_view(cub);
	else if (cub->info_gun.is_focus == 1 && cub->info_gun.is_reload == 0
		&& cub->info_gun.is_shoot == 0)
		gun_focus(cub);
	if (cub->info_gun.is_reload == 1)
		reload_gun(cub);
	else if (cub->info_gun.is_shoot == 1)
		gun_shots(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img, 0, 0);
	return (0);
}
