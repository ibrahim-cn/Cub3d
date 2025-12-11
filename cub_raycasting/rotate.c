/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ican <ican@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 23:43:25 by ican              #+#    #+#             */
/*   Updated: 2025/12/11 23:48:41 by ican             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	rotate_player(t_cub3d *cub)
{
	double	old_dir_x;
	double	old_plane_x;
	double	speed;

	if (cub->keys.right)
		speed = ROT_SPEED;
	else if (cub->keys.left)
		speed = -ROT_SPEED;
	else
		return ;
	old_dir_x = cub->player.dir_x;
	cub->player.dir_x = cub->player.dir_x * cos(speed)
		- cub->player.dir_y * sin(speed);
	cub->player.dir_y = old_dir_x * sin(speed)
		+ cub->player.dir_y * cos(speed);
	old_plane_x = cub->player.plane_x;
	cub->player.plane_x = cub->player.plane_x * cos(speed)
		- cub->player.plane_y * sin(speed);
	cub->player.plane_y = old_plane_x * sin(speed)
		+ cub->player.plane_y * cos(speed);
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
