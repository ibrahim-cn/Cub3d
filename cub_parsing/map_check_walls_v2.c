/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_walls_v2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ican <ican@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 02:27:41 by ican              #+#    #+#             */
/*   Updated: 2025/12/11 02:27:41 by ican             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	is_empty(t_cub3d *cub, int y, int x)
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

static void	check_empty_line_in_map(char *line, int j, t_cub3d *cub)
{
	if (j == 0 && (line[j] == '\n' || line[j] == '\0'))
		error_msg("Empty line inside map definition\n", 1, cub);
}

void	validate_chars_and_find_player(t_cub3d *cub)
{
	int		i;
	int		j;
	int		player_count;
	char	*line;

	player_count = 0;
	i = 0;
	while (i < cub->map->map_height)
	{
		line = cub->map->map_lines[cub->map->map_start_index + i];
		j = 0;
		while (line[j] && line[j] != '\n')
		{
			player_count += process_map_char(cub, line[j], i, j);
			j++;
		}
		check_empty_line_in_map(line, j, cub);
		i++;
	}
	if (player_count != 1)
		error_msg("Map must have exactly one player start position\n", 1, cub);
}

