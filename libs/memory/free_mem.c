/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 12:32:20 by alassiqu          #+#    #+#             */
/*   Updated: 2024/10/15 10:43:18 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"

void	free_texture(t_cub3d *cub, t_tex *tex)
{
	if (tex->file)
		free(tex->file);
	if (tex->img)
		mlx_destroy_image(cub->mlx, tex->img);
	free(tex);
}

void	free_map_element(t_cub3d *cub)
{
	if (cub->map->doors)
		free(cub->map->doors);
	if (cub->map->map)
		free_double(cub->map->map);
	if (cub->map)
	{
		if (cub->map->north)
			free_texture(cub, cub->map->north);
		if (cub->map->south)
			free_texture(cub, cub->map->south);
		if (cub->map->east)
			free_texture(cub, cub->map->east);
		if (cub->map->west)
			free_texture(cub, cub->map->west);
	}
	if (cub->map->colors)
	{
		if (cub->map->colors->ceil)
			free(cub->map->colors->ceil);
		if (cub->map->colors->floor)
			free(cub->map->colors->floor);
		free(cub->map->colors);
	}
	if (cub->map)
		free(cub->map);
}

void	free_cub_element(t_cub3d *cub)
{
	if (cub->fstp)
		free_texture(cub, cub->fstp);
	if (cub->door)
		free_texture(cub, cub->door);
	if (cub->player)
		free(cub->player);
	if (cub->img)
		mlx_destroy_image(cub->mlx, cub->img);
	if (cub->win)
		mlx_destroy_window(cub->mlx, cub->win);
	if (cub->mlx)
		free(cub->mlx);
	free(cub);
}

void	general_free(t_cub3d *cub)
{
	if (cub)
	{
		free_map_element(cub);
		free_cub_element(cub);
	}
}

void	free_double(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}
