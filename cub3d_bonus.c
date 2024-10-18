/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:06:54 by alassiqu          #+#    #+#             */
/*   Updated: 2024/10/18 17:00:25 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	ft_mouse(int x, int y, t_cub3d *cub)
{
	(void)y;
	static int last_x = -1;

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


void fill_window_with_red(t_cub3d *cub)
{
    int x;
    int y;

    // Set the color to red (0xFF0000)
    int red_color = 0xFF0000;

    // Loop over all pixels in the window
    for (y = 0; y < cub->hov; y++)
    {
        for (x = 0; x < cub->wov; x++)
        {
            mlx_pixel_put(cub->mlx, cub->win, x, y, red_color);
        }
    }
}


void	cub3d_bonus(t_cub3d *cub)
{
	cub->wov = 1900;
	cub->hov = 1080;
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, cub->wov, cub->hov, "The Cub-is-3D !!!");
	cub->img = mlx_new_image(cub->mlx, cub->wov, cub->hov);
	cub->add = mlx_get_data_addr(cub->img, &cub->bpp, &cub->szl, &cub->end);
	// fill_window_with_red(cub);
	load_textures(cub);
	mlx_loop_hook(cub->mlx, cub_loop, cub);
	mlx_hook(cub->win, 6, 1L << 6, ft_mouse, cub);
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
