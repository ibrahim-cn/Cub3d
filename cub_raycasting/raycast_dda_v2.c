/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_dda_v2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ican <ican@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 23:44:46 by ican              #+#    #+#             */
/*   Updated: 2025/12/11 23:44:48 by ican             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	check_wall_hit(t_cub3d *cub)
{
	if (cub->ray.map_y < 0 || cub->ray.map_y >= cub->map->height
		|| !cub->map->map_lines[cub->ray.map_y]
		|| cub->ray.map_x < 0
		|| cub->ray.map_x >= (int)ft_strlen(
			cub->map->map_lines[cub->ray.map_y]))
		return (1);
	if (cub->map->map_lines[cub->ray.map_y][cub->ray.map_x] == '1')
		return (1);
	return (0);
}

static void	perform_dda_step(t_cub3d *cub)
{
	if (cub->ray.side_dist_x < cub->ray.side_dist_y)
	{
		cub->ray.side_dist_x += cub->ray.delta_dist_x;
		cub->ray.map_x += cub->ray.step_x;
		cub->ray.side = 0;
	}
	else
	{
		cub->ray.side_dist_y += cub->ray.delta_dist_y;
		cub->ray.map_y += cub->ray.step_y;
		cub->ray.side = 1;
	}
}

void	perform_dda(t_cub3d *cub)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		perform_dda_step(cub);
		hit = check_wall_hit(cub);
	}
}
