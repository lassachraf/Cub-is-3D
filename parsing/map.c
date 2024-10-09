/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:32:32 by alassiqu          #+#    #+#             */
/*   Updated: 2024/10/08 15:33:04 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	general_check(t_cub3d *cub, char **map, int *i, int *j)
{
	char	**s;

	s = map;
	if (s[*i][*j] == '0' || s[*i][*j] == 'D' || is_it_player(s[*i][*j]))
	{
		if (*i == 0 || *i == cub->map->height - 1 || *j == 0
			|| *j == cub->map->width - 1)
			ft_error(cub, "Error: not a valid map.");
		if (s[(*i) - 1][*j] == ' ' || s[(*i) + 1][*j] == ' ' || s[*i][*j
			- 1] == ' ' || s[*i][*j + 1] == ' ')
			ft_error(cub, "Error: not a valid map.");
	}
	if (s[*i][*j] == 'D')
	{
		if (!((s[*i - 1][*j] == '1' && s[*i + 1][*j] == '1')
			|| s[*i][*j - 1] == '1' || s[*i][*j + 1] == '1'))
			ft_error(cub, "Error: useless door position.");
	}
}

void	check_surrounded(t_cub3d *cub, char **map)
{
	int	i;
	int	j;

	i = -1;
	while (++i < cub->map->height)
	{
		j = -1;
		while (++j < cub->map->width)
			general_check(cub, map, &i, &j);
	}
}

void	alloc_and_fill_map(t_cub3d **cub, char **map)
{
	int		i;
	int		j;
	char	**ret;
	char	**cpy_map;

	i = 0;
	j = 0;
	cpy_map = map;
	ret = malloc((sizeof(char *) * ((*cub)->map->height + 1)));
	while (cpy_map[i] && i < (*cub)->map->height)
	{
		ret[i] = malloc(sizeof(char) * (*cub)->map->width + 1);
		ft_strncpy_2(ret[i++], cpy_map[j++], (*cub)->map->width);
	}
	ret[(*cub)->map->height] = 0;
	check_surrounded(*cub, ret);
	(*cub)->map->map = ret;
}

void	map_parsing(t_cub3d **cub, char **map)
{
	int	i;
	int	j;

	i = -1;
	map = skip_white_lines(map);
	while (map[++i])
	{
		j = 0;
		while (map[i][j] && is_map_element(map[i][j]))
			j++;
		if (map[i][j] && !is_map_element(map[i][j]))
			ft_error(*cub, "Error: invalid map element.");
		if (j > (*cub)->map->width)
			(*cub)->map->width = j;
	}
	(*cub)->map->height = i;
	alloc_and_fill_map(cub, map);
	free_double(map);
}

void	get_2d_map(t_cub3d *cub, char *line)
{
	char	**map_2d;
	char	*lines;

	lines = NULL;
	while (line && line[0])
		lines = free_and_join(&line, &lines, cub->map->fd);
	if (lines == NULL)
		ft_error(cub, "Error: no map.");
	map_2d = ft_split(lines, '\n');
	free(lines);
	map_parsing(&cub, map_2d);
}
