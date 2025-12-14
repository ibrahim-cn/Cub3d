/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ican <<ican@student.42.fr>>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:00:41 by ican              #+#    #+#             */
/*   Updated: 2025/12/14 16:45:42 by ican             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


char	*space_is_not_important(char *str)
{
	char	*tmp;
	int		i;
	int		j;
	int		len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	i = 0;
	j = 0;
	if (str[0] == '/')
	{
		len = len - 1;
		i = 1;
	}
	if (len <= 0)
		return (ft_strdup(""));
	tmp = (char *)malloc((len + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	len = ft_strlen(str);
	while (i < len)
	{
		tmp[j] = str[i];
		j++;
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}




static void	init_main(int ac, char **arg, t_cub3d *cub)
{
	if (ac != 2)
		error_msg("Wrong number of arguments!\n", 1, cub);
	if (cub_check(arg[1]))
		error_msg("Wrong Type of file\n", 2, cub);
	cub->map->name = space_is_not_important(arg[1]);
}

int	main(int ac, char **arg)
{
	t_cub3d		cub;
	t_map		map;
	t_map_comp	comp;

	ft_bzero(&cub, sizeof(t_cub3d));
	ft_bzero(&map, sizeof(t_map));
	ft_bzero(&comp, sizeof(t_map_comp));
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
