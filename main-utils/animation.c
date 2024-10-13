/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:36:19 by alassiqu          #+#    #+#             */
/*   Updated: 2024/10/13 18:57:20 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

// void    set_tex(t_cub3d *cub, t_tex **tex, int nb)
// {
//     *tex = ft_calloc(1, sizeof(t_tex));
//     if (*tex == NULL)
//         ft_error(cub, "Error: allocation failed.");
//     (*tex)->file = ft_strjoin("../animation/player-frame-", nb);
//     (*tex)->img = mlx_xpm_file_to_image(cub->mlx, (*tex)->file, (*tex)->width, (*tex)->height);
//     if ((*tex)->img == NULL)
//         ft_error(cub, "Error: animation texture has been deleted.");
//     (*tex)->add = mlx_get_data_addr((*tex)->img, (*tex)->bpp, (*tex)->szl, (*tex)->end);
// }

// void    gun_animation(t_cub3d *cub)
// {
//     int     i;
//     int     nb_tex;
//     t_tex   *texture;

//     i = -1;
//     while (++i < nb_tex)
//     {
//         set_tex(cub, &texture, i);
//     }
// }
