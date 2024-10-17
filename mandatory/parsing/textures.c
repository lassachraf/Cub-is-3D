/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:20:27 by alassiqu          #+#    #+#             */
/*   Updated: 2024/10/17 18:46:54 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	add_texture(t_cub3d *cub, t_tex **tex, char *name)
{
	*tex = ft_calloc(1, sizeof(t_tex));
	if (*tex == NULL)
		ft_error(cub, "Error: allocation failed.");
	if (name[ft_strlen(name) - 1] == '\n')
		name[ft_strlen(name) - 1] = '\0';
	(*tex)->file = ft_strdup(name);
}

void	create_texture(t_cub3d **cub, int type, char *file)
{
	if (type == 1 && !(*cub)->map->north)
		add_texture(*cub, &(*cub)->map->north, file);
	else if (type == 2 && !(*cub)->map->south)
		add_texture(*cub, &(*cub)->map->south, file);
	else if (type == 3 && !(*cub)->map->east)
		add_texture(*cub, &(*cub)->map->east, file);
	else if (type == 4 && !(*cub)->map->west)
		add_texture(*cub, &(*cub)->map->west, file);
	else if (type == 5 && !(*cub)->door)
		add_texture(*cub, &(*cub)->door, file);
	else
		ft_error(*cub, "Error: duplicated texture.");
}

void	load_textures(t_cub3d *cub)
{
	t_tex	*e;
	t_tex	*w;
	t_tex	*n;
	t_tex	*s;

	e = cub->map->east;
	w = cub->map->west;
	n = cub->map->north;
	s = cub->map->south;
	e->img = mlx_xpm_file_to_image(cub->mlx, e->file, &e->width, &e->height);
	w->img = mlx_xpm_file_to_image(cub->mlx, w->file, &w->width, &w->height);
	n->img = mlx_xpm_file_to_image(cub->mlx, n->file, &n->width, &n->height);
	s->img = mlx_xpm_file_to_image(cub->mlx, s->file, &s->width, &s->height);
	if (!e->img || !w->img || !n->img || !s->img)
		ft_error(cub, "Error: can't load texture.");
	e->add = mlx_get_data_addr(e->img, &e->bpp, &e->szl, &e->end);
	w->add = mlx_get_data_addr(w->img, &w->bpp, &w->szl, &w->end);
	n->add = mlx_get_data_addr(n->img, &n->bpp, &n->szl, &n->end);
	s->add = mlx_get_data_addr(s->img, &s->bpp, &s->szl, &s->end);
	if (!e->add || !w->add || !n->add || !s->add)
		ft_error(cub, "Error: can't load texture.");
}

int	get_texture_color(t_tex *texture, int x, int y)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= texture->width || y >= texture->height)
		return (0);
	dst = texture->add + (y * texture->szl + x * (texture->bpp / 8));
	return (*(unsigned int *)dst);
}
