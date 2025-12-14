/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_render_v2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ican <<ican@student.42.fr>>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 23:42:41 by ican              #+#    #+#             */
/*   Updated: 2025/12/14 12:28:58 by ican             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	load_texture_image(t_cub3d *cub, t_img *texture, char *path)
{
	int	width;
	int	height;

	width = 0;
	height = 0;
	texture->img = mlx_xpm_file_to_image(cub->mlx, path, &width, &height);
	if (!texture->img)
		error_msg("Texture file load failed (check path or file format)\n",
			1, cub);
	if (width <= 0 || height <= 0)
		error_msg("Invalid texture dimensions from mlx_xpm_file_to_image\n",
			1, cub);
	texture->width = width;
	texture->height = height;
}

static void	get_texture_data(t_cub3d *cub, t_img *texture)
{
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->line_len, &texture->endian);
	if (!texture->addr)
		error_msg("Texture data address failed\n", 1, cub);
	if (texture->line_len <= 0 || texture->bpp <= 0)
		error_msg("Invalid texture data parameters\n", 1, cub);
}

static void	load_image(t_cub3d *cub, t_img *texture, char *path)
{
	if (!path || !*path)
		error_msg("Texture path is NULL or empty\n", 1, cub);
	texture->img = NULL;
	texture->addr = NULL;
	texture->width = 0;
	texture->height = 0;
	texture->bpp = 0;
	texture->line_len = 0;
	texture->endian = 0;
	load_texture_image(cub, texture, path);
	get_texture_data(cub, texture);
}

static void	validate_texture_paths(t_cub3d *cub)
{
	if (!cub)
		error_msg("Cub pointer is NULL\n", 1, cub);
	if (!cub->comp)
		error_msg("Comp pointer is NULL\n", 1, cub);
	if (!cub->comp->no)
		error_msg("Missing NO texture path\n", 1, cub);
	if (!cub->comp->so)
		error_msg("Missing SO texture path\n", 1, cub);
	if (!cub->comp->we)
		error_msg("Missing WE texture path\n", 1, cub);
	if (!cub->comp->ea)
		error_msg("Missing EA texture path\n", 1, cub);
}

void	init_textures(t_cub3d *cub)
{
	validate_texture_paths(cub);
	load_image(cub, &cub->textures.no, cub->comp->no);
	load_image(cub, &cub->textures.so, cub->comp->so);
	load_image(cub, &cub->textures.we, cub->comp->we);
	load_image(cub, &cub->textures.ea, cub->comp->ea);
}
