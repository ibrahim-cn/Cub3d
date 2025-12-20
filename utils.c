/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ican <ican@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 21:58:49 by ican              #+#    #+#             */
/*   Updated: 2025/12/20 23:07:14 by ican             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_structures(t_cub3d *cub, t_map *map, t_map_comp *comp)
{
	ft_bzero(cub, sizeof(t_cub3d));
	ft_bzero(map, sizeof(t_map));
	ft_bzero(comp, sizeof(t_map_comp));
	cub->map = map;
	cub->comp = comp;
}

void	free_map_copy(char **map_copy)
{
	int	i;

	if (!map_copy)
		return ;
	i = 0;
	while (map_copy[i])
	{
		free(map_copy[i]);
		i++;
	}
	free(map_copy);
}

int	has_unreachable_area(char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '0' || map[y][x] == '1')
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

void	process_line(t_cub3d *cub, char *line, int i)
{
	char	*joined;

	cub->map->map_lines[i] = line;
	joined = ft_strjoin(cub->map->one_line, line);
	if (!joined)
	{
		free(line);
		error_msg("Memory allocation failed\n", 2, cub);
	}
	free(cub->map->one_line);
	cub->map->one_line = joined;
}

int	is_empty(t_cub3d *cub, int y, int x)
{
	char	**map;
	int		start;
	int		height;

	map = cub->map->map_lines;
	start = cub->map->map_start_index;
	height = cub->map->map_height;
	if (y < 0 || y >= height)
		return (1);
	if (!map[start + y])
		return (1);
	if (x < 0 || (int)ft_strlen(map[start + y]) <= x)
		return (1);
	if (map[start + y][x] == ' ' || map[start + y][x] == '\n'
		|| map[start + y][x] == '\0')
		return (1);
	return (0);
}
