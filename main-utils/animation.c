/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:36:19 by alassiqu          #+#    #+#             */
/*   Updated: 2024/10/15 12:47:18 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	load_player(t_cub3d *cub)
{
	if (cub->fstp->img)
		mlx_destroy_image(cub->mlx, cub->fstp->img);
	cub->fstp->img = mlx_xpm_file_to_image(cub->mlx, "animation/player-frame-0.xpm", &cub->fstp->width, &cub->fstp->height);
	if (cub->fstp->img == NULL)
		ft_error(cub, "Error: loading player image failed.");
	cub->fstp->add = mlx_get_data_addr(cub->fstp->img, &cub->fstp->bpp, &cub->fstp->szl, &cub->fstp->end);
}

void	load_player_frame(t_cub3d *cub, int nb)
{
	char	*num;
	char	*tmp;

	num = ft_itoa(nb);
	tmp = ft_strjoin("animation/player-frame-", num);
	free(num);
	if (cub->fstp->file)
		free(cub->fstp->file);
	if (cub->fstp->img)
		mlx_destroy_image(cub->mlx, cub->fstp->img);
	cub->fstp->file = ft_strjoin(tmp, ".xpm");
	free(tmp);
	cub->fstp->img = mlx_xpm_file_to_image(cub->mlx, cub->fstp->file, &cub->fstp->width, &cub->fstp->height);
	if (cub->fstp->img == NULL)
		ft_error(cub, "Error: loading player image failed.");
	cub->fstp->add = mlx_get_data_addr(cub->fstp->img, &cub->fstp->bpp, &cub->fstp->szl, &cub->fstp->end);
}

int	gun_shots(t_cub3d *cub, int x, int y)
{
	int     		i;
	int     		j;
	int     		k;
	unsigned int	color;

	i = -1;
	while (++i < 2)
	{
		j = -1;
		load_player_frame(cub, i);
		while (++j < cub->fstp->height)
		{
			k = -1;
			while (++k < cub->fstp->width)
			{
				color = get_texture_color(cub->fstp, j, i);
				my_mlx_pixel_put(cub, x + j, y + i, color);
			}
		}
	}
	return (1);
}
