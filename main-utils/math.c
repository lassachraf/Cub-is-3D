/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matth.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:13:47 by alassiqu          #+#    #+#             */
/*   Updated: 2024/10/08 19:13:57 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

float	normalize_angle(float angle)
{
	angle = fmod(angle, (2 * PI));
	if (angle < 0)
		angle += (2 * PI);
	return (angle);
}
