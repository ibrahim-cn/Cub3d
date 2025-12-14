/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ican <<ican@student.42.fr>>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 22:00:41 by aaydogdu          #+#    #+#             */
/*   Updated: 2025/12/14 13:54:43 by ican             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	is_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ');
}

static int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

static void	check_double_map_in_line(char *line, t_cub3d *cub)
{
	int	i;
	int	found_first_map;
	int	whitespace_count;
	int	in_whitespace;

	if (!line)
		return ;
	i = 0;
	found_first_map = 0;
	whitespace_count = 0;
	in_whitespace = 0;
	while (line[i] && line[i] != '\n')
	{
		if (is_map_char(line[i]) && line[i] != ' ')
		{
			if (found_first_map && in_whitespace && whitespace_count > 2)
				error_msg("Double map detected (multiple map blocks in one line)\n", 1, cub);
			found_first_map = 1;
			in_whitespace = 0;
			whitespace_count = 0;
		}
		else if (is_whitespace(line[i]))
		{
			if (found_first_map)
			{
				in_whitespace = 1;
				whitespace_count++;
			}
		}
		else
		{
			found_first_map = 0;
			in_whitespace = 0;
			whitespace_count = 0;
		}
		i++;
	}
}

static void	check_empty_lines_in_map(char **map_lines, int start, int end,
			t_cub3d *cub)
{
	int		i;
	char	*trimmed;
	int		is_empty;

	if (!map_lines || !cub)
		error_msg("Invalid parameters\n", 1, cub);
	i = start;
	while (i <= end)
	{
		if (!map_lines[i])
			error_msg("Null map line found\n", 1, cub);
		trimmed = trim_spaces(map_lines[i]);
		is_empty = (!trimmed || !*trimmed);
		if (is_empty)
			error_msg("Empty line inside map definition\n", 1, cub);
		check_double_map_in_line(map_lines[i], cub);
		i++;
	}
}

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

static void	create_clean_map(t_cub3d *cub)
{
	char	**new_map;
	int		i;

	if (!cub || !cub->map)
		return ;
	new_map = malloc(sizeof(char *) * (cub->map->map_height + 1));
	if (!new_map)
		error_msg("Memory allocation failed for clean map\n", 1, cub);
	i = 0;
	while (i < cub->map->map_height)
	{
		if (!cub->map->map_lines || !cub->map->map_lines[cub->map->map_start_index + i])
		{
			while (i > 0)
				free(new_map[--i]);
			free(new_map);
			error_msg("Invalid map line index\n", 1, cub);
		}
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
	check_empty_lines_in_map(map_lines, map_start_index, map_end_index, cub);
	check_content_after_map(map_lines, map_end_index, cub);
	validate_colors(cub);
	check_map_layout(cub);
	create_clean_map(cub);
}
