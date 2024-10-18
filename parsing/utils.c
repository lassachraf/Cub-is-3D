/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:06:19 by alassiqu          #+#    #+#             */
/*   Updated: 2024/10/18 10:04:05 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	skip_whitespaces(char **line)
{
	while (*line && **line && ft_isspace(**line))
		(*line)++;
}

int	is_white_line(char *s)
{
	int	i;

	i = 0;
	while (s[i] && ft_isspace(s[i]))
		i++;
	if (s[i] == '\0')
		return (1);
	else
		return (0);
}

void	double_check(t_cub3d *cub, char **line, int count)
{
	int	i;

	i = 0;
	if (count != 6)
		ft_error(cub, "Error: missing texture.");
	if (**line && *line && !is_white_line(*line))
	{
		while ((*line)[i] && ft_isspace((*line)[i]))
			i++;
		if ((*line)[i] && !is_map_element((*line)[i]))
		{
			free(*line);
			ft_error(cub, "Error: not a valid map element.");
		}
	}
}

void	ft_error(t_cub3d *cub, char *msg)
{
	general_free(cub);
	printf(RED"%s\n"RESET, msg);
	exit(1);
}

int	ft_exit(t_cub3d *cub)
{
	general_free(cub);
	exit(0);
	return (0);
}
