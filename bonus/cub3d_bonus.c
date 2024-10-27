/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:06:54 by alassiqu          #+#    #+#             */
/*   Updated: 2024/10/26 16:40:48 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	ft_mouse(int x, int y, t_cub3d *cub)
{
	static int	last_x = -1;

	(void)y;
	if (last_x != -1)
	{
		if (x > last_x)
			cub->player->rot_ang += 0.02;
		else if (x < last_x)
			cub->player->rot_ang -= 0.02;
	}
	last_x = x;
	return (0);
}

void	cub3d_bonus(t_cub3d *cub)
{
	cub->wov = 1920;
	cub->hov = 1080;
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, cub->wov, cub->hov, "Cub-is-DDD !");
	cub->img = mlx_new_image(cub->mlx, cub->wov, cub->hov);
	cub->add = mlx_get_data_addr(cub->img, &cub->bpp, &cub->szl, &cub->end);
	cub->info_gun.state_hand = 0;
	cub->info_gun.is_focus = 0;
	cub->info_gun.is_animation_run = 0;
	load_textures(cub);
	load_animation_textures(cub);
	mlx_loop_hook(cub->mlx, cub_loop, cub);
	mlx_hook(cub->win, 6, 1L << 6, ft_mouse, cub);
	mlx_hook(cub->win, 2, 1L << 0, ft_moving, cub);
	mlx_hook(cub->win, 3, 1L << 1, ft_reset, cub);
	mlx_loop(cub->mlx);
}

void	init_cub3d_bonus(char *av)
{
	int		i;
	t_cub3d	*cub;

	cub = (t_cub3d *)ft_calloc(1, sizeof(t_cub3d));
	if (cub == NULL)
		ft_error(NULL, "Error.");
	parsing(cub, av);
	cub3d_bonus(cub);
	i = -1;
	while (++i < 73)
	{
		if (cub->map->ani[i])
			free(cub->map->ani[i]);
	}
	general_free(cub);
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return (ft_error(NULL, "Error: invalid number of args."), 1);
	init_cub3d_bonus(av[1]);
	return (1);
}
