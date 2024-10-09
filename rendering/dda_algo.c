/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 23:17:18 by alassiqu          #+#    #+#             */
/*   Updated: 2024/10/09 18:57:28 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	dda(t_cub3d *cub, float *xy)
{
	int		i;
	float   xp;
	float   yp;
	float   steps;
	
	xp = cub->player->x;
	yp = cub->player->y;
	if (fabs(xy[0] - xp) > fabs(xy[1] - yp))
		steps = fabs(xy[0] - xp);
	else
		steps = fabs(xy[1] - yp);
	i = -1;
	while (++i <= steps)
	{
		my_mlx_pixel_put(cub, round(xp), round(yp), 0xFFFFFF);
		xp += (xy[0] - xp) / steps;
		yp += (xy[1] - yp) / steps;
	}
    free(xy);
}

void	set_textures(t_cub3d *cub, t_tex **tex)
{
	if (cub->side == 0)
		*tex = cub->map->north;
	if (cub->side == 1)
		*tex = cub->map->south;
	if (cub->side == 2)
		*tex = cub->map->west;
	if (cub->side == 3)
		*tex = cub->map->east;
	if (cub->side == 4)
		*tex = cub->door;
}

// void	get_color_and_draw(t_cub3d *cub, t_tex *tex, int wall_h, float *x)
// {
// 	int		y;
// 	int		d;
// 	int		end;
// 	int		start;
//     float	tex_y;

// 	start = (cub->hov / 2) - (wall_h / 2);
// 	end = (cub->hov / 2) + (wall_h / 2);
// 	y = start;
// 	while (y < end)
//     {
//         d = y * 256 - cub->hov * 128 + wall_h * 128;
//         tex_y = ((d * tex->height) / wall_h) / 256;
//         my_mlx_pixel_put(cub, x[0], y, get_texture_color(tex, x[1], tex_y));
// 		y++;
//     }
// }

// void draw_wall_slice(t_cub3d *cub, int x, int wall_height, float ray_distance)
// {
//     int		end;
//     int		start;
//     float	*tex_x;
//     t_tex	*texture;

// 	tex_x = malloc(2 * sizeof(float));
// 	if (tex_x == NULL)
// 		ft_error(cub, "Error: allocation failed.");
// 	start = (cub->hov / 2) - (wall_height / 2);
// 	end = (cub->hov / 2) + (wall_height / 2);
// 	set_textures(cub, &texture);
//     if (start < 0)
//         start = 0;
//     if (end > cub->hov)
// 	{
//         end = cub->hov;
// 	}
// 	tex_x[0] = x;
//     tex_x[1] = (int)(ray_distance * texture->width) % texture->width;
// 	// get_color_and_draw(cub, texture, wall_height, tex_x);
//     for (int y = start; y < end; y++)
//     {
//         // Calculate texture Y coordinate
//         int d = y * 256 - cub->hov * 128 + wall_height * 128;
//         tex_y = ((d * texture->height) / wall_height) / 256;

//         // Get pixel color from the texture
//         int color = get_texture_color(texture, tex_x, tex_y);

//         // Draw the pixel on screen
//         my_mlx_pixel_put(cub, x, y, color);
//     }
// 	free(tex_x);
// }

void draw_wall_slice(t_cub3d *cub, int x, int wall_height, float ray_distance)
{
    int start = (cub->hov / 2) - (wall_height / 2);  // Starting point for drawing the wall slice
    int end = (cub->hov / 2) + (wall_height / 2);    // Ending point
    float tex_x;  // X-coordinate on the texture
    float tex_y;  // Y-coordinate on the texture
    t_tex *texture;

	set_textures(cub, &texture);
    if (start < 0)
        start = 0;
    if (end > cub->hov)
        end = cub->hov;

    tex_x = (int)(ray_distance * texture->width) % texture->width;

    for (int y = start; y < end; y++)
    {
        int d = y * 256 - cub->hov * 128 + wall_height * 128;
        tex_y = ((d * texture->height) / wall_height) / 256;

        int color = get_texture_color(texture, tex_x, tex_y);
        my_mlx_pixel_put(cub, x, y, color);
    }
}
