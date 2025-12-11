/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaydogdu <aaydogdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 10:46:27 by aaydogdu          #+#    #+#             */
/*   Updated: 2025/12/11 12:09:44 by aaydogdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	**duplicate_map(t_cub3d *cub)
{
	char	**copy;
	int		i;
	int		start;

	start = cub->map->map_start_index;
	copy = (char **)malloc(sizeof(char *) * (cub->map->map_height + 1));
	if (!copy)
		error_msg("Memory allocation failed for map copy\n", 1, cub);
	i = 0;
	while (i < cub->map->map_height)
	{
		copy[i] = ft_strdup(cub->map->map_lines[start + i]);
		if (!copy[i])
		{
			while (i > 0)
				free(copy[--i]);
			free(copy);
			error_msg("Memory allocation failed for map copy line\n", 1, cub);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	free_map_copy(char **map_copy)
{
	int	i;

	i = 0;
	while (map_copy[i])
	{
		free(map_copy[i]);
		i++;
	}
	free(map_copy);
}

static void	flood_fill(t_cub3d *cub, char **map_copy, int y, int x)
{
	if (y < 0 || y >= cub->map->map_height
		|| x < 0 || !map_copy[y]
		|| x >= (int)ft_strlen(map_copy[y])
		|| map_copy[y][x] == ' ')
	{
		free_map_copy(map_copy);
		error_msg("Map is not closed (open to space or edge)\n", 1, cub);
	}
	if (map_copy[y][x] == '1' || map_copy[y][x] == 'F')
		return ;
	map_copy[y][x] = 'F';
	flood_fill(cub, map_copy, y + 1, x);
	flood_fill(cub, map_copy, y - 1, x);
	flood_fill(cub, map_copy, y, x + 1);
	flood_fill(cub, map_copy, y, x - 1);
}

void	check_map_layout(t_cub3d *cub)
{
	char	**map_copy;

	validate_chars_and_find_player(cub);
	map_copy = duplicate_map(cub);
	flood_fill(cub, map_copy, cub->player.pos_y, cub->player.pos_x);
	free_map_copy(map_copy);
}
