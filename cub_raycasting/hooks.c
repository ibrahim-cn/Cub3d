/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ican <ican@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 23:28:11 by ican              #+#    #+#             */
/*   Updated: 2025/12/11 23:28:17 by ican             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	close_window(t_cub3d *cub)
{
	if (!cub)
		return (0);
	free_map(cub);
	free_comp(cub);
	free_textures(cub);
	if (cub->win)
		mlx_destroy_window(cub->mlx, cub->win);
	if (cub->mlx)
	{
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
		cub->mlx = NULL;
	}
	exit(0);
	return (0);
}

int	render_loop(t_cub3d *cub)
{
	move_player(cub);
	rotate_player(cub);
	raycasting(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->imgt.img, 0, 0);
	return (0);
}

int	key_press(int keycode, t_cub3d *cub)
{
	if (keycode == KEY_ESC)
		close_window(cub);
	else if (keycode == 119)
		cub->keys.w = 1;
	else if (keycode == 97)
		cub->keys.a = 1;
	else if (keycode == 115)
		cub->keys.s = 1;
	else if (keycode == 100)
		cub->keys.d = 1;
	else if (keycode == 65361)
		cub->keys.left = 1;
	else if (keycode == 65363)
		cub->keys.right = 1;
	else if (keycode == 65307)
		close_window(cub);
	return (0);
}

int	key_release(int keycode, t_cub3d *cub)
{
	if (keycode == 119)
		cub->keys.w = 0;
	else if (keycode == 97)
		cub->keys.a = 0;
	else if (keycode == 115)
		cub->keys.s = 0;
	else if (keycode == 100)
		cub->keys.d = 0;
	else if (keycode == 65361)
		cub->keys.left = 0;
	else if (keycode == 65363)
		cub->keys.right = 0;
	return (0);
}
