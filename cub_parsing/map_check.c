/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ican <ican@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 22:00:41 by aaydogdu          #+#    #+#             */
/*   Updated: 2025/12/20 23:05:08 by ican             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	check_content_after_map(char **map_lines, int end, t_cub3d *cub)
{
	int		i;
	char	*trimmed;

	if (!map_lines || !cub)
		return ;
	i = end + 1;
	while (map_lines[i])
	{
		trimmed = trim_spaces(map_lines[i]);
		if (trimmed && *trimmed)
			error_msg("Invalid content after map definition\n", 1, cub);
		i++;
	}
}

static void	cleanup_on_error(char **new_map, int i, t_cub3d *cub)
{
	while (i > 0)
		free(new_map[--i]);
	free(new_map);
	error_msg("Invalid map line index\n", 1, cub);
}

static void	copy_map_lines(char **new_map, t_cub3d *cub)
{
	int		i;

	i = 0;
	while (i < cub->map->map_height)
	{
		if (!cub->map->map_lines
			|| !cub->map->map_lines[cub->map->map_start_index + i])
			cleanup_on_error(new_map, i, cub);
		new_map[i] = ft_strdup(cub->map->map_lines
			[cub->map->map_start_index + i]);
		if (!new_map[i])
		{
			while (i > 0)
				free(new_map[--i]);
			free(new_map);
			error_msg("Memory allocation failed for map line\n", 1, cub);
		}
		i++;
	}
	new_map[i] = NULL;
}

static void	create_clean_map(t_cub3d *cub)
{
	char	**new_map;

	if (!cub || !cub->map)
		return ;
	new_map = malloc(sizeof(char *) * (cub->map->map_height + 1));
	if (!new_map)
		error_msg("Memory allocation failed for clean map\n", 1, cub);
	copy_map_lines(new_map, cub);
	free_map(cub);
	cub->map->map_lines = new_map;
}

void	is_map_valid(char **map_lines, t_cub3d *cub)
{
	int	map_start_index;
	int	map_end_index;

	if (!map_lines || !cub || !cub->map)
		error_msg("Invalid parameters for is_map_valid\n", 1, cub);
	find_map_bounds(map_lines, &map_start_index, &map_end_index, cub);
	cub->map->map_start_index = map_start_index;
	cub->map->map_height = map_end_index - map_start_index + 1;
	check_content_after_map(map_lines, map_end_index, cub);
	validate_colors(cub);
	check_map_layout(cub);
	check_empty_lines_in_map(map_lines, map_start_index, map_end_index, cub);
	create_clean_map(cub);
}
