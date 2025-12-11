/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ican <ican@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 23:45:20 by ican              #+#    #+#             */
/*   Updated: 2025/12/11 23:45:26 by ican             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_img	*select_texture(t_cub3d *cub)
{
	if (cub->ray.side == 0)
	{
		if (cub->ray.ray_dir_x < 0)
			return (&cub->textures.we);
		else
			return (&cub->textures.ea);
	}
	else
	{
		if (cub->ray.ray_dir_y < 0)
			return (&cub->textures.no);
		else
			return (&cub->textures.so);
	}
}

static void	calc_wall_x_tex_x(t_cub3d *cub, t_img *texture,
			double *wall_x, int *tex_x)
{
	if (cub->ray.side == 0)
		*wall_x = cub->player.pos_y + cub->ray.perp_wall_dist
			* cub->ray.ray_dir_y;
	else
		*wall_x = cub->player.pos_x + cub->ray.perp_wall_dist
			* cub->ray.ray_dir_x;
	*wall_x -= floor(*wall_x);
	*tex_x = (int)(*wall_x * (double)texture->width);
	if (cub->ray.side == 0 && cub->ray.ray_dir_x > 0)
		*tex_x = texture->width - *tex_x - 1;
	if (cub->ray.side == 1 && cub->ray.ray_dir_y < 0)
		*tex_x = texture->width - *tex_x - 1;
}

void	calculate_texture_coords(t_cub3d *cub, t_img *texture,
			t_tex_data *tex_data)
{
	double	wall_x;

	calc_wall_x_tex_x(cub, texture, &wall_x, &tex_data->tex_x);
	tex_data->step = 1.0 * texture->height / cub->ray.line_height;
	tex_data->tex_pos = (cub->ray.draw_start - SCREEN_HEIGHT / 2.0
			+ cub->ray.line_height / 2.0) * tex_data->step;
}
