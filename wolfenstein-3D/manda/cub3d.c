/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:06:54 by alassiqu          #+#    #+#             */
/*   Updated: 2024/11/11 21:20:27 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub3d(t_cub3d *cub)
{
	cub->wov = 2300;
	cub->hov = 1300;
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, cub->wov, cub->hov, "Cub-is-DDD !");
	if (cub->win == NULL)
		ft_error(cub, "Error.");
	cub->img = mlx_new_image(cub->mlx, cub->wov, cub->hov);
	if (cub->img == NULL)
		ft_error(cub, "Error.");
	cub->add = mlx_get_data_addr(cub->img, &cub->bpp, &cub->szl, &cub->end);
	if (cub->add == NULL)
		ft_error(cub, "Error.");
	load_textures(cub);
	mlx_loop_hook(cub->mlx, cub_loop, cub);
	mlx_hook(cub->win, 2, 1L << 0, ft_moving, cub);
	mlx_hook(cub->win, 3, 1L << 1, ft_reset, cub);
	mlx_hook(cub->win, 17, 0, ft_exit, cub);
	mlx_loop(cub->mlx);
}

void	init_cub3d(char *av)
{
	t_cub3d	*cub;

	cub = (t_cub3d *)ft_calloc(1, sizeof(t_cub3d));
	if (cub == NULL)
		ft_error(NULL, "Error.");
	parsing(cub, av);
	cub3d(cub);
	general_free(cub);
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return (ft_error(NULL, "Error."), 1);
	init_cub3d(av[1]);
	return (1);
}
