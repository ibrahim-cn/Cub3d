/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ican <ican@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 23:43:40 by ican              #+#    #+#             */
/*   Updated: 2025/12/11 23:43:44 by ican             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_ceiling(t_cub3d *cub, int x)
{
	int	y;
	int	ceil_c;

	ceil_c = create_rgb(cub->comp->ceiling_color[0],
			cub->comp->ceiling_color[1], cub->comp->ceiling_color[2]);
	y = 0;
	while (y < cub->ray.draw_start)
	{
		my_mlx_pixel_put(cub, x, y, ceil_c);
		y++;
	}
}

void	draw_wall_slice(t_cub3d *cub, int x, t_tex_data *tex_data)
{
	int		y;
	int		tex_y;
	int		color;
	char	*dst;

	y = cub->ray.draw_start;
	while (y <= cub->ray.draw_end)
	{
		tex_y = (int)tex_data->tex_pos % tex_data->texture->height;
		tex_data->tex_pos += tex_data->step;
		if (tex_y < 0)
			tex_y = 0;
		dst = tex_data->texture->addr + (tex_y * tex_data->texture->line_len
				+ tex_data->tex_x * (tex_data->texture->bpp / 8));
		color = *(unsigned int *)dst;
		my_mlx_pixel_put(cub, x, y, color);
		y++;
	}
}

void	draw_floor(t_cub3d *cub, int x)
{
	int	y;
	int	floor_c;

	floor_c = create_rgb(cub->comp->floor_color[0],
			cub->comp->floor_color[1], cub->comp->floor_color[2]);
	y = cub->ray.draw_end;
	while (y < SCREEN_HEIGHT)
	{
		my_mlx_pixel_put(cub, x, y, floor_c);
		y++;
	}
}

void	draw_column(t_cub3d *cub, int x, t_tex_data *tex_data)
{
	draw_ceiling(cub, x);
	draw_floor(cub, x);
	draw_wall_slice(cub, x, tex_data);
}
