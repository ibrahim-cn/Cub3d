/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ican <ican@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 11:40:00 by aaydogdu          #+#    #+#             */
/*   Updated: 2025/12/11 02:27:41 by ican             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	get_map_cell(t_cub3d *cub, int y, int x)
{
	int	real_y;

	if (y < 0 || y >= cub->map->map_height)
		return (' ');
	real_y = cub->map->map_start_index + y;
	if (!cub->map->map_lines[real_y]
		|| x < 0 || x >= (int)ft_strlen(cub->map->map_lines[real_y]))
		return (' ');
	return (cub->map->map_lines[real_y][x]);
}
