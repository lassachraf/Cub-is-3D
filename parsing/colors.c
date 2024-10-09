/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:18:44 by alassiqu          #+#    #+#             */
/*   Updated: 2024/10/08 15:30:24 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	ft_atoi_rgb(t_cub3d *cub, char *str)
{
	int	nb;

	nb = 0;
	if (!str)
		ft_error(cub, "Error: color do not have a value.");
	while (*str && ft_isspace(*str))
		str++;
	if (*str == '-')
		ft_error(cub, "Error: negative number color.");
	if (*str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		nb = (nb * 10) + (((*str) - '0'));
		if (nb > 255)
			ft_error(cub, "Error: higher color value.");
		str++;
	}
	if (*str && !ft_isdigit(*str) && !ft_isspace(*str))
		ft_error(cub, "Error: color error.");
	return (nb);
}

long	ft_colors(t_cub3d *cub, char *s)
{
	char	**split;
	int		r;
	int		g;
	int		b;

	split = ft_split(s, ',');
	r = ft_atoi_rgb(cub, split[0]);
	g = ft_atoi_rgb(cub, split[1]);
	b = ft_atoi_rgb(cub, split[2]);
	if (split[3])
	{
		ft_error(cub, "Error: color should be like 'R,G,B'.");
		return (-1);
	}
	free_double(split);
	return (0 << 24 | r << 16 | g << 8 | b);
}

void	create_color(t_cub3d **cub, int type, char *s)
{
	if ((*cub)->map->colors == NULL)
	{
		(*cub)->map->colors = ft_calloc(1, sizeof(t_color));
		if ((*cub)->map->colors == NULL)
			ft_error(*cub, "Error: allocation failed.");
	}
	if (type == 1 && !(*cub)->map->colors->ceil)
	{
		(*cub)->map->colors->ceil = ft_strdup(s);
		(*cub)->map->colors->ceil_h = ft_colors(*cub, s);
	}
	else if (type == 2 && !(*cub)->map->colors->floor)
	{
		(*cub)->map->colors->floor = ft_strdup(s);
		(*cub)->map->colors->floor_h = ft_colors(*cub, s);
	}
	else
		ft_error(*cub, "Error: duplicated color.");
}
