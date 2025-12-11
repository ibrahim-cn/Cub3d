/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaydogdu <aaydogdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 22:00:41 by aaydogdu          #+#    #+#             */
/*   Updated: 2025/12/11 15:01:28 by aaydogdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	check_empty_lines_in_map(char **map_lines, int start, int end,
			t_cub3d *cub)
{
	int		i;
	char	*trimmed;
	int		is_empty;

	i = start;
	while (i <= end)
	{
		trimmed = trim_spaces(map_lines[i]);
		is_empty = (!trimmed || !*trimmed);
		if (is_empty)
			error_msg("Empty line inside map definition\n", 1, cub);
		i++;
	}
}

static void	check_content_after_map(char **map_lines, int end, t_cub3d *cub)
{
	int		i;
	char	*trimmed;

	i = end + 1;
	while (map_lines[i])
	{
		trimmed = trim_spaces(map_lines[i]);
		if (trimmed && *trimmed)
			error_msg("Invalid content after map definition\n", 1, cub);
		i++;
	}
}

static void	create_clean_map(t_cub3d *cub)
{
	char	**new_map;
	int		i;

	new_map = malloc(sizeof(char *) * (cub->map->map_height + 1));
	if (!new_map)
		error_msg("Memory allocation failed for clean map\n", 1, cub);
	i = 0;
	while (i < cub->map->map_height)
	{
		new_map[i] = ft_strdup(cub->map->map_lines
			[cub->map->map_start_index + i]);
		if (!new_map[i])
			error_msg("Memory allocation failed for map line\n", 1, cub);
		i++;
	}
	new_map[i] = NULL;
	free_map(cub);
	cub->map->map_lines = new_map;
}

void	is_map_valid(char **map_lines, t_cub3d *cub)
{
	int	map_start_index;
	int	map_end_index;

	find_map_bounds(map_lines, &map_start_index, &map_end_index, cub);
	cub->map->map_start_index = map_start_index;
	cub->map->map_height = map_end_index - map_start_index + 1;
	check_empty_lines_in_map(map_lines, map_start_index, map_end_index, cub);
	check_content_after_map(map_lines, map_end_index, cub);
	validate_colors(cub);
	check_map_layout(cub);
	create_clean_map(cub);
}
