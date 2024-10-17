/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:20:23 by alassiqu          #+#    #+#             */
/*   Updated: 2024/10/17 18:40:33 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void draw_wall_slice(t_cub3d *cub, int x, int wall_height, float ray_distance)
{
    int start = (cub->hov / 2) - (wall_height / 2);  // Starting point for drawing the wall slice
    int end = (cub->hov / 2) + (wall_height / 2);    // Ending point
    float tex_x;  // X-coordinate on the texture
    float tex_y;  // Y-coordinate on the texture
    t_tex *texture;

    set_textures(cub, &texture);
    
    // Ensure start and end are within bounds
    if (start < 0)
        start = 0;
    if (end > cub->hov)
        end = cub->hov;
    // Calculate tex_x based on the wall hit position
    if (cub->side == 0 || cub->side == 1) // North or South
        tex_x = (int)(cub->player->x + (ray_distance - (int)ray_distance)) * texture->width; // Adjust as needed
    else // East or West
        tex_x = (int)(cub->player->y + (ray_distance - (int)ray_distance)) * texture->width; // Adjust as needed
    
    tex_x = (int)tex_x % texture->width; // Ensure tex_x is within texture bounds

    for (int y = start; y < end; y++)
    {
        int d = y * 256 - cub->hov * 128 + wall_height * 128;
        tex_y = ((d * texture->height) / wall_height) / 256;
		tex_y = (int)tex_y % texture->height;

        int color = get_texture_color(texture, tex_x, tex_y);
        (void)color;
        my_mlx_pixel_put(cub, x, y, 0x000000FF);
    }
}
