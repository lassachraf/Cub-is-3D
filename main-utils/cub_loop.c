/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:35:57 by alassiqu          #+#    #+#             */
/*   Updated: 2024/10/10 19:56:56 by alassiqu         ###   ########.fr       */
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
		ft_error(cub, "Error: allocation failled.");
	ray[0] = cub->player->x + cos(curr_ang) * ray_dist;
	ray[1] = cub->player->y + sin(curr_ang) * ray_dist;
	return (ray);
}

void	draw_and_coloring(t_cub3d *cub, int ind, int ray_dist)
{
	int	i;
	int	wall_top;
	int	wall_bottom;
	int	wall_height;

	wall_height = (int)(cub->hov / ray_dist);
	wall_top = (cub->hov - wall_height) / 2;
	wall_bottom = wall_top + wall_height;
	i = 0;
	while (i < wall_top)
		my_mlx_pixel_put(cub, ind, i++, cub->map->colors->ceil_h);
	draw_wall_slice(cub, ind, wall_height, ray_dist);
	i = wall_bottom;
	while (i < cub->hov)
		my_mlx_pixel_put(cub, ind, i++, cub->map->colors->floor_h);
}

void	cast_fov(t_cub3d *cub)
{
    int     i;
    float   ang_inc;
	float	curr_ang;
    float   ray_start;
	float	ray_dist;

    i = -1;
    ang_inc = cub->player->fov / cub->wov;
    ray_start = cub->player->rot_ang - (cub->player->fov / 2.0);
    while (++i < cub->wov)
    {
        curr_ang = get_current_angle(ray_start, ang_inc, i);
        ray_dist = calculate_ray_distance(cub, curr_ang);
        dda(cub, get_index(cub, curr_ang, ray_dist));
		// Should be done with the function "draw_and_coloring".
		int wall_height = (int)(cub->hov / ray_dist);
		int wall_top = (cub->hov - wall_height) / 2;
		int wall_bottom = wall_top + wall_height;

		for (int y = 0; y < wall_top; y++)
			my_mlx_pixel_put(cub, i, y, cub->map->colors->ceil_h);
		draw_wall_slice(cub, i, wall_height, ray_dist);
		for (int y = wall_bottom; y < cub->hov; y++)
			my_mlx_pixel_put(cub, i, y, cub->map->colors->floor_h);
    }
}

int	cub_loop(t_cub3d *cub)
{
	if (cub->img)
		mlx_destroy_image(cub->mlx, cub->img);
	cub->img = mlx_new_image(cub->mlx, cub->wov, cub->hov);
	cub->add = mlx_get_data_addr(cub->img, &cub->bpp, &cub->szl, &cub->end);
	cast_fov(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img, 0, 0);
	return (0);
}
