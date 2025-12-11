/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ican <ican@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 23:45:05 by ican              #+#    #+#             */
/*   Updated: 2025/12/11 23:45:07 by ican             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_ray_vars(t_cub3d *cub, int x)
{
	cub->ray.camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	cub->ray.ray_dir_x = cub->player.dir_x
		+ cub->player.plane_x * cub->ray.camera_x;
	cub->ray.ray_dir_y = cub->player.dir_y
		+ cub->player.plane_y * cub->ray.camera_x;
	cub->ray.map_x = (int)cub->player.pos_x;
	cub->ray.map_y = (int)cub->player.pos_y;
}

static void	init_dda_x(t_cub3d *cub)
{
	cub->ray.delta_dist_x = fabs(1 / cub->ray.ray_dir_x);
	if (cub->ray.ray_dir_x < 0)
	{
		cub->ray.step_x = -1;
		cub->ray.side_dist_x = (cub->player.pos_x - cub->ray.map_x)
			* cub->ray.delta_dist_x;
	}
	else
	{
		cub->ray.step_x = 1;
		cub->ray.side_dist_x = (cub->ray.map_x + 1.0 - cub->player.pos_x)
			* cub->ray.delta_dist_x;
	}
}

static void	init_dda_y(t_cub3d *cub)
{
	cub->ray.delta_dist_y = fabs(1 / cub->ray.ray_dir_y);
	if (cub->ray.ray_dir_y < 0)
	{
		cub->ray.step_y = -1;
		cub->ray.side_dist_y = (cub->player.pos_y - cub->ray.map_y)
			* cub->ray.delta_dist_y;
	}
	else
	{
		cub->ray.step_y = 1;
		cub->ray.side_dist_y = (cub->ray.map_y + 1.0 - cub->player.pos_y)
			* cub->ray.delta_dist_y;
	}
}

void	init_dda(t_cub3d *cub)
{
	init_dda_x(cub);
	init_dda_y(cub);
}

void	calculate_wall_height(t_cub3d *cub)
{
	if (cub->ray.side == 0)
		cub->ray.perp_wall_dist = (cub->ray.side_dist_x
				- cub->ray.delta_dist_x);
	else
		cub->ray.perp_wall_dist = (cub->ray.side_dist_y
				- cub->ray.delta_dist_y);
	cub->ray.line_height = (int)(SCREEN_HEIGHT / cub->ray.perp_wall_dist);
	cub->ray.draw_start = -cub->ray.line_height / 2 + SCREEN_HEIGHT / 2;
	if (cub->ray.draw_start < 0)
		cub->ray.draw_start = 0;
	cub->ray.draw_end = cub->ray.line_height / 2 + SCREEN_HEIGHT / 2;
	if (cub->ray.draw_end >= SCREEN_HEIGHT)
		cub->ray.draw_end = SCREEN_HEIGHT - 1;
}
