/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ican <<ican@student.42.fr>>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:19:43 by aaydogdu          #+#    #+#             */
/*   Updated: 2025/12/14 16:15:57 by ican             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_map_exist(t_cub3d *cub)
{
	int	fd;

	if (!cub || !cub->map || !cub->map->name)
		error_msg("Invalid cub or map pointer\n", 2, cub);
	fd = open(cub->map->name, O_RDONLY);
	if (fd < 0)
		error_msg("File could not found or opened\n", 2, cub);
	cub->map->fd = fd;
}

static void	check_standalone_zero(char *line, t_cub3d *cub)
{
	char	*trimmed;

	trimmed = trim_spaces(line);
	if (trimmed && ft_strlen(trimmed) == 1 && trimmed[0] == '0')
		error_msg("Standalone '0' found outside map definition\n", 1, cub);
}

static void	update_bounds(int i, int status, int *start, int *end)
{
	if (status == 2)
	{
		if (*start == -1)
			*start = i;
		*end = i;
	}
	else if (status == 0 && *start != -1)
	{
		if (*end != -1)
			*end = i;
	}
}

void	find_map_bounds(char **map_lines, int *start, int *end,
			t_cub3d *cub)
{
	int	i;
	int	comp_status;

	if (!map_lines || !start || !end || !cub || !cub->comp)
		error_msg("Invalid parameters for find_map_bounds\n", 1, cub);
	i = 0;
	*start = -1;
	*end = -1;
	while (map_lines[i])
	{
		comp_status = check_comp(map_lines[i], cub->comp, cub);
		if (*start == -1 && comp_status == 2)
			check_standalone_zero(map_lines[i], cub);
		if (comp_status == 1)
			error_msg("Invalid component format\n", 1, cub);
		else if (comp_status == 2 && !all_comps_found(cub->comp))
			error_msg("Map found before all components set\n", 1, cub);
		else
			update_bounds(i, comp_status, start, end);
		i++;
	}
	if (!all_comps_found(cub->comp))
		error_msg("Missing one or more map components\n", 1, cub);
	if (*start == -1)
		error_msg("No map found in file\n", 1, cub);
}
