/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaydogdu <aaydogdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:00:41 by ican              #+#    #+#             */
/*   Updated: 2025/12/21 12:05:00 by aaydogdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	copy_string_part(char *str, char *tmp, int start)
{
	int	i;
	int	j;

	i = start;
	j = 0;
	while (str[i])
	{
		tmp[j] = str[i];
		j++;
		i++;
	}
	tmp[j] = '\0';
}

char	*space_is_not_important(char *str)
{
	char	*tmp;
	int		start;
	int		len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	start = 0;
	if (str[0] == '/')
	{
		len = len - 1;
		start = 1;
	}
	if (len <= 0)
		return (ft_strdup(""));
	tmp = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	copy_string_part(str, tmp, start);
	return (tmp);
}

static void	check_args(int ac, char **arg, t_cub3d *cub)
{
	if (ac != 2)
		error_msg("Wrong number of arguments!\n", 1, cub);
	if (cub_check(arg[1]))
		error_msg("Wrong Type of file\n", 1, cub);
	cub->map->name = space_is_not_important(arg[1]);
}

static void	setup_game(t_cub3d *cub)
{
	check_map_exist(cub);
	copy_map(cub);
	eliminate_one_line(cub);
	is_map_valid(cub->map->map_lines, cub);
	init_game(cub);
	init_textures(cub);
	init_player(cub);
	mlx_loop_hook(cub->mlx, render_loop, cub);
	mlx_hook(cub->win, EVENT_KEY_PRESS, 1L << 0, key_press, cub);
	mlx_hook(cub->win, EVENT_DESTROY, 0, close_window, cub);
	mlx_hook(cub->win, 2, 1L << 0, key_press, cub);
	mlx_hook(cub->win, 3, 1L << 1, key_release, cub);
}

int	main(int ac, char **arg)
{
	t_cub3d		cub;
	t_map		map;
	t_map_comp	comp;

	init_structures(&cub, &map, &comp);
	check_args(ac, arg, &cub);
	setup_game(&cub);
	mlx_loop(cub.mlx);
	all_free(&cub);
	return (0);
}
