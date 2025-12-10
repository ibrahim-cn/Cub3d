/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ican <ican@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 11:38:59 by aaydogdu          #+#    #+#             */
/*   Updated: 2025/12/11 02:27:41 by ican             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	init_ray_vars(t_cub3d *cub, int x)
{
	cub->ray.camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	cub->ray.ray_dir_x = cub->player.dir_x
		+ cub->player.plane_x * cub->ray.camera_x;
	cub->ray.ray_dir_y = cub->player.dir_y
		+ cub->player.plane_y * cub->ray.camera_x;
	cub->ray.map_x = (int)cub->player.pos_x;
	cub->ray.map_y = (int)cub->player.pos_y;
}

static void	init_dda(t_cub3d *cub)
{
	cub->ray.delta_dist_x = fabs(1 / cub->ray.ray_dir_x);
	cub->ray.delta_dist_y = fabs(1 / cub->ray.ray_dir_y);
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

static void	perform_dda(t_cub3d *cub)
{
	int	hit;

	hit = 0;
	while (hit == 0)
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
		if (cub->ray.map_y < 0 || cub->ray.map_y >= cub->map->height
			|| !cub->map->map_lines[cub->ray.map_y]
			|| cub->ray.map_x < 0
			|| cub->ray.map_x >= (int)ft_strlen(
				cub->map->map_lines[cub->ray.map_y]))
			hit = 1;
		else if (cub->map->map_lines[cub->ray.map_y][cub->ray.map_x] == '1')
			hit = 1;
	}
}

static void	calculate_wall_height(t_cub3d *cub)
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

static t_img	*select_texture(t_cub3d *cub)
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

static void	calculate_texture_coords(t_cub3d *cub, t_img *texture,
			double *wall_x, int *tex_x, double *step, double *tex_pos)
{
	calc_wall_x_tex_x(cub, texture, wall_x, tex_x);
	*step = 1.0 * texture->height / cub->ray.line_height;
	*tex_pos = (cub->ray.draw_start - SCREEN_HEIGHT / 2.0
			+ cub->ray.line_height / 2.0) * (*step);
}

static void	draw_ceiling(t_cub3d *cub, int x)
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

static void	draw_wall_slice(t_cub3d *cub, int x, t_img *texture, int tex_x,
			double step, double tex_pos)
{
	int		y;
	int		tex_y;
	int		color;
	char	*dst;

	y = cub->ray.draw_start;
	while (y < cub->ray.draw_end)
	{
		tex_y = (int)tex_pos % texture->height;
		tex_pos += step;
		if (tex_y < 0)
			tex_y = 0;
		dst = texture->addr + (tex_y * texture->line_len
				+ tex_x * (texture->bpp / 8));
		color = *(unsigned int *)dst;
		my_mlx_pixel_put(cub, x, y, color);
		y++;
	}
}

static void	draw_floor(t_cub3d *cub, int x)
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

static void	draw_column(t_cub3d *cub, int x, t_img *texture, int tex_x,
			double step, double tex_pos)
{
	draw_ceiling(cub, x);
	draw_wall_slice(cub, x, texture, tex_x, step, tex_pos);
	draw_floor(cub, x);
}

static void	process_ray(t_cub3d *cub, int x, t_img **texture, int *tex_x,
			double *step, double *tex_pos)
{
	double	wall_x;

	init_ray_vars(cub, x);
	init_dda(cub);
	perform_dda(cub);
	calculate_wall_height(cub);
	*texture = select_texture(cub);
	calculate_texture_coords(cub, *texture, &wall_x, tex_x, step, tex_pos);
}

void	raycasting(t_cub3d *cub)
{
	int		x;
	t_img	*texture;
	int		tex_x;
	double	step;
	double	tex_pos;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		process_ray(cub, x, &texture, &tex_x, &step, &tex_pos);
		draw_column(cub, x, texture, tex_x, step, tex_pos);
		x++;
	}
}
