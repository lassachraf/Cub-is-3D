/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:55:30 by alassiqu          #+#    #+#             */
/*   Updated: 2024/10/17 17:24:25 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	compare_and_set(t_cub3d **cub, char **s, int *count)
{
	if (!ft_strcmp(s[0], "NO"))
		create_texture(cub, 1, s[1]);
	else if (!ft_strcmp(s[0], "SO"))
		create_texture(cub, 2, s[1]);
	else if (!ft_strcmp(s[0], "EA"))
		create_texture(cub, 3, s[1]);
	else if (!ft_strcmp(s[0], "WE"))
		create_texture(cub, 4, s[1]);
	else if (!ft_strcmp(s[0], "C"))
		create_color(cub, 1, s[1]);
	else if (!ft_strcmp(s[0], "F"))
		create_color(cub, 2, s[1]);
	(*count)++;
	free_double(s);
}

int	check_texture_color(t_cub3d **cub, char *line, int *count)
{
	char	**split;

	if (line == NULL)
		return (1);
	split = ft_split(line, ' ');
	if (split == NULL || split[0] == NULL)
		return (1);
	if (split[2] && ft_strcmp(split[2], "\n"))
	{
		free(line);
		free_double(split);
		return (ft_error(*cub, "Error: bad color or texture."), 0);
	}
	if (!ft_strcmp(split[0], "NO") || !ft_strcmp(split[0], "SO")
		|| !ft_strcmp(split[0], "EA") || !ft_strcmp(split[0], "WE")
		|| !ft_strcmp(split[0], "F") || !ft_strcmp(split[0], "C"))
	{
		compare_and_set(cub, split, count);
		return (1);
	}
	return (free(line), 0);
}

void	get_textures_and_colors(t_cub3d *cub, char **line)
{
	int	count;

	count = 0;
	while (*line && *line[0])
	{
		if (count == 6 && !is_white_line(*line))
			break ;
		if (is_white_line(*line))
		{
			free(*line);
			*line = NULL;
		}
		skip_whitespaces(&(*line));
		if (count < 6 && *line && *line[0])
		{
			if (check_texture_color(&cub, *line, &count) == 0)
				ft_error(cub, "Error: bad texture/color structure.");
			free(*line);
		}
		*line = get_next_line(cub->map->fd);
	}
	double_check(cub, line, count);
}

void	get_file_content(t_cub3d *cub)
{
	char	*line;

	line = get_next_line(cub->map->fd);
	get_textures_and_colors(cub, &line);
	get_2d_map(cub, line);
	get_player(cub);
	close(cub->map->fd);
	cub->hov = cub->map->height * TILE_SIZE;
	cub->wov = cub->map->width * TILE_SIZE;
}

void	parsing(t_cub3d *cub, char *av)
{
	ft_extension(av, ".cub");
	cub->map = ft_calloc(1, sizeof(*cub->map));
	if (cub->map == NULL)
		ft_error(cub, "Error: allocation failed.");
	cub->map->fd = open(av, O_RDONLY);
	if (cub->map->fd == -1)
		ft_error(cub, "Error: open failed.");
	get_file_content(cub);
	close(cub->map->fd);
	create_texture(&cub, 5, "textures/door.xpm");
}
