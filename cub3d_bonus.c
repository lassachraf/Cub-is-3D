/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:06:54 by alassiqu          #+#    #+#             */
/*   Updated: 2024/10/12 20:44:04 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	cub3d_bonus(t_cub3d *cub)
{
	int	size_x;
	int	size_y;

	size_x = cub->wov;
	size_y = cub->hov;
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, size_x, size_y, "The Cub-is-3D !!!");
	cub->img = mlx_new_image(cub->mlx, size_x, size_y);
	cub->add = mlx_get_data_addr(cub->img, &cub->bpp, &cub->szl, &cub->end);
	load_textures(cub);
	mlx_loop_hook(cub->mlx, cub_loop, cub);
	mlx_hook(cub->win, 2, 1L << 0, ft_moving, cub);
	mlx_loop(cub->mlx);
}

void	init_cub3d_bonus(char *av)
{
	t_cub3d	*cub;

	cub = (t_cub3d *)ft_calloc(1, sizeof(t_cub3d));
	if (cub == NULL)
		ft_error(NULL, "Error: allocation failed.");
	parsing(cub, av);
	cub3d_bonus(cub);
	general_free(cub);
}

int main(int ac, char **av)
{
	if (ac != 2)
		return (ft_error(NULL, "Error: invalid number of args."), 1);
	init_cub3d_bonus(av[1]);
	return (1);
}
