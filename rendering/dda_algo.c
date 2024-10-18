/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 23:17:18 by alassiqu          #+#    #+#             */
/*   Updated: 2024/10/13 14:11:34 by alassiqu         ###   ########.fr       */
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

void draw_wall_slice(t_cub3d *cub, int x, int wall_height, float ray_distance, float curr_ang)
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
    

	float wall_x;
	float ray_dir_x = cos(curr_ang);
	float ray_dir_y = sin(curr_ang);



    if (cub->side == 2 || cub->side == 3)
		wall_x = cub->player->y + ray_distance * ray_dir_y;
    else 
		wall_x = cub->player->x + ray_distance * ray_dir_x;

	wall_x -= floor((wall_x));

	tex_x = wall_x * texture->width;
	if (cub->side == 0 && ray_dir_x > 0)
		tex_x = texture->width - tex_x - 1;
	if (cub->side == 1 && ray_dir_y < 0)
		tex_x = texture->width - tex_x - 1;

    for (int y = start; y < end; y++)
    {
        int d = y * 256 - cub->hov * 128 + wall_height * 128;
        tex_y = ((d * texture->height) / wall_height) / 256;
		tex_y = (int)tex_y % texture->height;

        int color = get_texture_color(texture, tex_x, tex_y);
        my_mlx_pixel_put(cub, x, y, color);
    }
}