/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:41:35 by alassiqu          #+#    #+#             */
/*   Updated: 2024/11/15 00:07:31 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	load_player(t_cub3d *cub)
{
	if (cub->fstp->img)
		mlx_destroy_image(cub->mlx, cub->fstp->img);
	cub->fstp->img = mlx_xpm_file_to_image(cub->mlx, "animation/ply-0.xpm",
			&cub->fstp->width, &cub->fstp->height);
	if (cub->fstp->img == NULL)
		ft_error(cub, "Error.\nMlx fails to create image from xpm file.");
	cub->fstp->add = mlx_get_data_addr(cub->fstp->img, &cub->fstp->bpp,
			&cub->fstp->szl, &cub->fstp->end);
	if (cub->fstp->add == NULL)
		ft_error(cub, "Error.\nMlx fails to get the address of the image.");
}

void	draw_gun(t_cub3d *cub, int index)
{
	int				i;
	int				j;
	int				x;
	int				y;
	unsigned int	color;

	i = -1;
	y = cub->hov - cub->map->ani[index]->height + 1;
	x = (cub->wov / 2) - (cub->map->ani[index]->width / 2) + 200;
	while (++i < cub->map->ani[index]->height)
	{
		j = -1;
		while (++j < cub->map->ani[index]->width)
		{
			color = get_texture_color(cub->map->ani[index], j, i);
			if (color != 0xFF000000)
				my_mlx_pixel_put(cub, x + j, y + i, color);
		}
	}
}

void	default_shoot(t_cub3d *cub)
{
	static int	delay = 2;

	delay++;
	if (delay >= 7)
	{
		draw_gun(cub, 0);
		delay = 2;
		cub->info_gun.is_shoot = 0;
		return ;
	}
	draw_gun(cub, delay);
}
