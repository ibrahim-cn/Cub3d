/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ican <ican@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 11:39:05 by aaydogdu          #+#    #+#             */
/*   Updated: 2025/12/11 02:27:41 by ican             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	is_safe_point(t_cub3d *cub, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_y < 0 || map_y >= cub->map->map_height)
		return (0);
	if (map_x < 0 || map_x >= (int)ft_strlen(cub->map->map_lines[map_y]))
		return (0);
	if (cub->map->map_lines[map_y][map_x] == '1'
		|| cub->map->map_lines[map_y][map_x] == ' ')
		return (0);
	return (1);
}

static int	check_hitbox(t_cub3d *cub, double new_x, double new_y)
{
	if (!is_safe_point(cub, new_x - PLAYER_SIZE, new_y - PLAYER_SIZE))
		return (0);
	if (!is_safe_point(cub, new_x + PLAYER_SIZE, new_y - PLAYER_SIZE))
		return (0);
	if (!is_safe_point(cub, new_x - PLAYER_SIZE, new_y + PLAYER_SIZE))
		return (0);
	if (!is_safe_point(cub, new_x + PLAYER_SIZE, new_y + PLAYER_SIZE))
		return (0);
	return (1);
}

static void	calculate_movement(t_cub3d *cub, double *move_x, double *move_y)
{
	if (cub->keys.w)
	{
		*move_x += cub->player.dir_x * MOVE_SPEED;
		*move_y += cub->player.dir_y * MOVE_SPEED;
	}
	if (cub->keys.s)
	{
		*move_x -= cub->player.dir_x * MOVE_SPEED;
		*move_y -= cub->player.dir_y * MOVE_SPEED;
	}
	if (cub->keys.a)
	{
		*move_x -= cub->player.plane_x * MOVE_SPEED;
		*move_y -= cub->player.plane_y * MOVE_SPEED;
	}
	if (cub->keys.d)
	{
		*move_x += cub->player.plane_x * MOVE_SPEED;
		*move_y += cub->player.plane_y * MOVE_SPEED;
	}
}

static void	apply_movement(t_cub3d *cub, double move_x, double move_y)
{
	if (check_hitbox(cub, cub->player.pos_x + move_x, cub->player.pos_y))
		cub->player.pos_x += move_x;
	if (check_hitbox(cub, cub->player.pos_x, cub->player.pos_y + move_y))
		cub->player.pos_y += move_y;
}

void	move_player(t_cub3d *cub)
{
	double	move_x;
	double	move_y;

	move_x = 0;
	move_y = 0;
	calculate_movement(cub, &move_x, &move_y);
	apply_movement(cub, move_x, move_y);
}

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
