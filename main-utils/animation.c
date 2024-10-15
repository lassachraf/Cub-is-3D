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
	printf("frame >> %d >> %s\n", nb, cub->fstp->file);
	cub->fstp->img = mlx_xpm_file_to_image(cub->mlx, cub->fstp->file,
		&cub->fstp->width, &cub->fstp->height);
	if (cub->fstp->img == NULL)
		ft_error(cub, "Error: loading player image failed.");
	cub->fstp->add = mlx_get_data_addr(cub->fstp->img, &cub->fstp->bpp,
		&cub->fstp->szl, &cub->fstp->end);
}

void	draw_gun(t_cub3d *cub, int x, int y)
{
	int				i;
	int				j;
	unsigned int	color;

	i = -1;
	while (++i < cub->fstp->height)
	{
		j = -1;
		while (++j < cub->fstp->width)
		{
			color = get_texture_color(cub->fstp, j, i);
			if (color != 0xFF000000)
				my_mlx_pixel_put(cub, x + j, y + i, color);
		}
	}
}

int	gun_shots(t_cub3d *cub, int flag)
{
	int				x_pos;
	int				y_pos;
	static int		frame = 0;
	static int		delay = 1;

	if (cub->fstp == NULL || cub->fstp->img == NULL)
		return (1);
	x_pos = (cub->wov / 2) - (cub->fstp->width / 2);
	y_pos = cub->hov - cub->fstp->height + 1;
	while (delay && flag == 0)
	{
		delay++;
		if (delay < 40)
			frame = 0;
		else if (delay <= 80)
			frame = 1;
		else if (delay <= 120)
			frame = 2;
		else if (delay <= 160)
			frame = 3;
		else if (delay <= 190)
			frame = 4;
		else if (delay <= 220)
			frame = 5;
		else if (delay > 240)
			delay = 0;
		load_player_frame(cub, frame);
	}
	draw_gun(cub, x_pos, y_pos);
	return (1);
}
