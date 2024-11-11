/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:35:57 by alassiqu          #+#    #+#             */
/*   Updated: 2024/11/11 17:56:28 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

float	get_current_angle(float ray_start, float ang_inc, int x)
{
	float	angle;

	angle = ray_start + (x * ang_inc);
	return (normalize_angle(angle));
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
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img, 0, 0);
	return (0);
}
