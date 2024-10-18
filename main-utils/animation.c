/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:36:19 by alassiqu          #+#    #+#             */
/*   Updated: 2024/10/15 22:09:38 by alassiqu         ###   ########.fr       */
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
		ft_error(cub, "Error: loading player image failed.");
	cub->fstp->add = mlx_get_data_addr(cub->fstp->img, &cub->fstp->bpp,
		&cub->fstp->szl, &cub->fstp->end);
}

void	load_player_frame(t_cub3d *cub, int nb)
{
	char	*num;
	char	*tmp;

	num = ft_itoa(nb);
	tmp = ft_strjoin("animation/ply-", num);
	free(num);
	if (cub->fstp->file)
		free(cub->fstp->file);
	if (cub->fstp->img)
		mlx_destroy_image(cub->mlx, cub->fstp->img);
	cub->fstp->file = ft_strjoin(tmp, ".xpm");
	free(tmp);
	cub->fstp->img = mlx_xpm_file_to_image(cub->mlx, cub->fstp->file,
		&cub->fstp->width, &cub->fstp->height);
	if (cub->fstp->img == NULL)
		ft_error(cub, "Error: loading player image failed.");
	cub->fstp->add = mlx_get_data_addr(cub->fstp->img, &cub->fstp->bpp,
		&cub->fstp->szl, &cub->fstp->end);
}

void	draw_gun(t_cub3d *cub, int index)
{
	int				i;
	int				j;
	unsigned int	color;
	int				x;
	int				y;
	x = (cub->wov / 2) - (cub->map->ani[index]->width / 2);
	y = cub->hov - cub->map->ani[index]->height + 1;


	i = -1;
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


int	gun_shots(t_cub3d *cub)
{
	static int				delay = 0;
	
	delay++;

	if (delay <=  1)
		draw_gun(cub, 1);
	else if (delay  <=  2)
		draw_gun(cub, 2);
	else if (delay <=  3)
		draw_gun(cub, 3);
	else if (delay <=  4)
		draw_gun(cub, 4);
	else if (delay <=  5)
	{
		draw_gun(cub, 0);
		cub->person = 0;
		delay = 0;
	}
				

	
	return (1);
}
