/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ican <ican@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 23:45:50 by ican              #+#    #+#             */
/*   Updated: 2025/12/12 00:09:45 by ican             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	my_mlx_pixel_put(t_cub3d *cub, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	dst = cub->imgt.addr + (y * cub->imgt.line_len
			+ x * (cub->imgt.bpp / 8));
	*(unsigned int *)dst = color;
}

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	init_texture_struct(t_img *texture)
{
	texture->img = NULL;
	texture->addr = NULL;
	texture->width = 0;
	texture->height = 0;
	texture->bpp = 0;
	texture->line_len = 0;
	texture->endian = 0;
}

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
