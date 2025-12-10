/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaydogdu <aaydogdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:00:41 by ican              #+#    #+#             */
/*   Updated: 2025/11/08 11:39:15 by aaydogdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "minilibx-linux/mlx.h"

static void	init_main(int ac, char **arg, t_cub3d *cub)
{
	if (ac != 2)
		error_msg("Wrong number of arguments!\n", 1, cub);
	if (cub_check(arg[1]))
		error_msg("Wrong Type of file\n", 2, cub);
	cub->map->name = arg[1];
}

int	main(int ac, char **arg)
{
	static t_cub3d		cub;
	static t_map		map;
	static t_map_comp	comp;

	cub.map = &map;
	cub.comp = &comp;
	init_main(ac, arg, &cub);
	check_map_exist(&cub);
	copy_map(&cub);
	eliminate_one_line(&cub);
	is_map_valid(cub.map->map_lines, &cub);
	init_game(&cub);
	init_textures(&cub);
	init_player(&cub);
	mlx_loop_hook(cub.mlx, render_loop, &cub);
	mlx_hook(cub.win, EVENT_KEY_PRESS, 1L << 0, key_press, &cub);
	mlx_hook(cub.win, EVENT_DESTROY, 0, close_window, &cub);
	mlx_hook(cub.win, 2, 1L << 0, key_press, &cub);
	mlx_hook(cub.win, 3, 1L << 1, key_release, &cub);
	mlx_loop(cub.mlx);
	all_free(&cub);
	return (0);
}
