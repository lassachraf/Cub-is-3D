/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:32:26 by alassiqu          #+#    #+#             */
/*   Updated: 2024/10/18 11:03:31 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	is_map_element(char c)
{
	return (c == '1' || c == '0' || c == ' ' || is_it_player(c)
		|| c == 'D');
}

char	*free_and_join(char **line, char **lines, int fd)
{
	char	*ret;
	int		i;

	i = 0;
	if (*line && **line && ft_isspace(**line))
	{
		while (line[0][i] && ft_isspace(line[0][i]))
			i++;
		if (line[0][i] == '\0')
		{
			free(*line);
			*line = ft_strdup(" \n");
		}
	}
	ret = ft_strjoin(*lines, *line);
	if (*lines)
		free(*lines);
	if (*line)
		free(*line);
	*line = get_next_line(fd);
	return (ret);
}

char	**skip_white_lines(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i] && ft_isspace(map[i][0]))
	{
		j = 0;
		while (map[i][j] && ft_isspace(map[i][j]))
			j++;
		if (map[i][j])
			break ;
		i++;
	}
	return (&map[i]);
}

char	*ft_strncpy_2(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		++i;
	}
	while (i < n)
	{
		dest[i] = ' ';
		i++;
	}
	dest[i] = 0;
	return (dest);
}
