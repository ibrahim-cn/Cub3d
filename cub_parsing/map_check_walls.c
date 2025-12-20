/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ican <ican@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 10:46:27 by aaydogdu          #+#    #+#             */
/*   Updated: 2025/12/20 22:58:10 by ican             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	cleanup_on_dup_error(char **copy, int i)
{
	while (i > 0)
		free(copy[--i]);
	free(copy);
}

static void	copy_map_lines(char **copy, t_cub3d *cub, int start)
{
	int	i;

	i = 0;
	while (i < cub->map->map_height)
	{
		if (!cub->map->map_lines[start + i])
		{
			cleanup_on_dup_error(copy, i);
			error_msg("Invalid map line in duplicate\n", 1, cub);
		}
		copy[i] = ft_strdup(cub->map->map_lines[start + i]);
		if (!copy[i])
		{
			cleanup_on_dup_error(copy, i);
			error_msg("Memory allocation failed for map copy line\n", 1, cub);
		}
		i++;
	}
	copy[i] = NULL;
}

char	**duplicate_map(t_cub3d *cub)
{
	char	**copy;
	int		start;

	if (!cub || !cub->map || !cub->map->map_lines)
		error_msg("Invalid cub or map pointer\n", 1, cub);
	start = cub->map->map_start_index;
	copy = (char **)malloc(sizeof(char *) * (cub->map->map_height + 1));
	if (!copy)
		error_msg("Memory allocation failed for map copy\n", 1, cub);
	copy_map_lines(copy, cub, start);
	return (copy);
}

static void	flood_fill(char **map, int x, int y)
{
	if (y < 0 || !map[y] || x < 0 || x >= (int)ft_strlen(map[y]) || !map[y][x])
		return ;
	if (map[y][x] == ' ' || map[y][x] == '\t')
		return ;
	if (map[y][x] == 'F')
		return ;
	map[y][x] = 'F';
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}

void	check_map_layout(t_cub3d *cub)
{
	char	**map_copy;

	if (!cub || !cub->map)
		error_msg("Invalid cub or map pointer\n", 1, cub);
	validate_chars_and_find_player(cub);
	map_copy = duplicate_map(cub);
	flood_fill(map_copy, cub->player.pos_x, cub->player.pos_y);
	if (has_unreachable_area(map_copy))
	{
		free_map_copy(map_copy);
		error_msg("Ups, double map! hihi 🤭🤭🤭\n", 1, cub);
	}
	free_map_copy(map_copy);
}
