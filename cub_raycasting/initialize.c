/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ican <ican@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 11:38:53 by aaydogdu          #+#    #+#             */
/*   Updated: 2025/12/11 23:26:23 by ican             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_game(t_cub3d *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		error_msg("MLX init failed\n", 1, cub);
	cub->win = mlx_new_window(cub->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	if (!cub->win)
		error_msg("MLX window failed\n", 1, cub);
	cub->imgt.img = mlx_new_image(cub->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!cub->imgt.img)
		error_msg("MLX image failed\n", 1, cub);
	cub->imgt.addr = mlx_get_data_addr(cub->imgt.img, &cub->imgt.bpp,
			&cub->imgt.line_len, &cub->imgt.endian);
}

void	set_dir_vectors(t_cub3d *cub, double x, double y)
{
	cub->player.dir_x = x;
	cub->player.dir_y = y;
}

void	set_plane_vectors(t_cub3d *cub, double p_x, double p_y)
{
	cub->player.plane_x = p_x;
	cub->player.plane_y = p_y;
}

void	init_player(t_cub3d *cub)
{
	cub->player.pos_x += 0.5;
	cub->player.pos_y += 0.5;
	if (cub->player_dir == 'N')
	{
		set_dir_vectors(cub, 0, -1);
		set_plane_vectors(cub, 0.66, 0);
	}
	else if (cub->player_dir == 'S')
	{
		set_dir_vectors(cub, 0, 1);
		set_plane_vectors(cub, -0.66, 0);
	}
	else if (cub->player_dir == 'E')
	{
		set_dir_vectors(cub, 1, 0);
		set_plane_vectors(cub, 0, 0.66);
	}
	else if (cub->player_dir == 'W')
	{
		set_dir_vectors(cub, -1, 0);
		set_plane_vectors(cub, 0, -0.66);
	}
}

void	free_textures(t_cub3d *cub)
{
	if (!cub || !cub->mlx)
		return ;
	if (cub->textures.no.img)
		mlx_destroy_image(cub->mlx, cub->textures.no.img);
	if (cub->textures.so.img)
		mlx_destroy_image(cub->mlx, cub->textures.so.img);
	if (cub->textures.we.img)
		mlx_destroy_image(cub->mlx, cub->textures.we.img);
	if (cub->textures.ea.img)
		mlx_destroy_image(cub->mlx, cub->textures.ea.img);
	if (cub->imgt.img)
		mlx_destroy_image(cub->mlx, cub->imgt.img);
	cub->textures.no.img = NULL;
	cub->textures.so.img = NULL;
	cub->textures.we.img = NULL;
	cub->textures.ea.img = NULL;
	cub->imgt.img = NULL;
}
