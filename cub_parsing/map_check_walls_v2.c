/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_walls_v2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaydogdu <aaydogdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 02:27:41 by ican              #+#    #+#             */
/*   Updated: 2025/12/20 23:24:42 by aaydogdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	check_map_closed(t_cub3d *cub, int y, int x)
{
	if (is_empty(cub, y - 1, x)
		|| is_empty(cub, y + 1, x)
		|| is_empty(cub, y, x - 1)
		|| is_empty(cub, y, x + 1))
	{
		error_msg("Map is not closed (open to space or edge)\n", 1, cub);
	}
}

static void	check_stray_wall(t_cub3d *cub, int y, int x)
{
	if (is_empty(cub, y - 1, x)
		&& is_empty(cub, y + 1, x)
		&& is_empty(cub, y, x - 1)
		&& is_empty(cub, y, x + 1))
	{
		error_msg("Stray (orphaned) wall detected\n", 1, cub);
	}
}

static int	process_map_char(t_cub3d *cub, char c, int y, int x)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		check_map_closed(cub, y, x);
	else if (c == '1')
		check_stray_wall(cub, y, x);
	else if (c != ' ')
		error_msg("Invalid character in map\n", 1, cub);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		cub->player.pos_x = x;
		cub->player.pos_y = y;
		cub->player_dir = c;
		return (1);
	}
	return (0);
}

static int	process_map_line(t_cub3d *cub, int i)
{
	int		j;
	int		player_count;
	char	*line;

	line = cub->map->map_lines[cub->map->map_start_index + i];
	if (!line)
		error_msg("Null map line found\n", 1, cub);
	player_count = 0;
	j = 0;
	while (line[j] && line[j] != '\n')
	{
		player_count += process_map_char(cub, line[j], i, j);
		j++;
	}
	if (j == 0 && (line[j] == '\n' || line[j] == '\0'))
		error_msg("Empty line inside map definition\n", 1, cub);
	return (player_count);
}

void	validate_chars_and_find_player(t_cub3d *cub)
{
	int		i;
	int		player_count;

	if (!cub || !cub->map || !cub->map->map_lines)
		error_msg("Invalid cub or map pointer\n", 1, cub);
	player_count = 0;
	i = 0;
	while (i < cub->map->map_height)
	{
		if (!cub->map->map_lines[cub->map->map_start_index + i])
			error_msg("Invalid map line index\n", 1, cub);
		player_count += process_map_line(cub, i);
		i++;
	}
	if (player_count != 1)
		error_msg("Map must have exactly one player start position\n", 1, cub);
}
