/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaydogdu <aaydogdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 11:38:59 by aaydogdu          #+#    #+#             */
/*   Updated: 2025/12/11 16:20:43 by aaydogdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	process_ray(t_cub3d *cub, int x, t_tex_data *tex_data)
{
	init_ray_vars(cub, x);
	init_dda(cub);
	perform_dda(cub);
	calculate_wall_height(cub);
	tex_data->texture = select_texture(cub);
	calculate_texture_coords(cub, tex_data->texture, tex_data);
}

void	raycasting(t_cub3d *cub)
{
	int			x;
	t_tex_data	tex_data;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		process_ray(cub, x, &tex_data);
		draw_column(cub, x, &tex_data);
		x++;
	}
}
