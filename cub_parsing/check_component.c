/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_component.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ican <<ican@student.42.fr>>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 12:39:57 by aaydogdu          #+#    #+#             */
/*   Updated: 2025/12/14 12:35:12 by ican             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	all_comps_found(t_map_comp *comp)
{
	if (!comp)
		return (0);
	if (!comp->no || !comp->so || !comp->we || !comp->ea
		|| !comp->f || !comp->c)
		return (0);
	return (1);
}

static int	set_texture_path(char **texture_ptr, char *line, t_cub3d *cub)
{
	*texture_ptr = extract_path(line);
	if (*texture_ptr)
		validate_texture_file(*texture_ptr, cub);
	return (0);
}

static int	process_component(char *line, t_map_comp *comp, t_cub3d *cub)
{
	if (!ft_strncmp(line, "NO", 2) && ft_empty(line[2]) && !comp->no)
		return (set_texture_path(&comp->no, line + 2, cub));
	else if (!ft_strncmp(line, "SO", 2) && ft_empty(line[2]) && !comp->so)
		return (set_texture_path(&comp->so, line + 2, cub));
	else if (!ft_strncmp(line, "WE", 2) && ft_empty(line[2]) && !comp->we)
		return (set_texture_path(&comp->we, line + 2, cub));
	else if (!ft_strncmp(line, "EA", 2) && ft_empty(line[2]) && !comp->ea)
		return (set_texture_path(&comp->ea, line + 2, cub));
	if (line[0] == 'F' && ft_empty(line[1]) && !comp->f)
	{
		comp->f = extract_color(line + 1, cub);
		return (0);
	}
	else if (line[0] == 'C' && ft_empty(line[1]) && !comp->c)
	{
		comp->c = extract_color(line + 1, cub);
		return (0);
	}
	return (-1);
}

static int	check_duplicate_component(char *line)
{
	if (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2)
		|| !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2)
		|| line[0] == 'F' || line[0] == 'C')
		return (1);
	return (0);
}

int	check_comp(char *line, t_map_comp *comp, t_cub3d *cub)
{
	int	result;

	if (!line || !comp || !cub)
		return (1);
	line = trim_spaces(line);
	if (!line || !*line)
		return (0);
	if (check_tab(line))
		return (1);
	result = process_component(line, comp, cub);
	if (result == 0)
		return (0);
	if (check_duplicate_component(line))
		return (1);
	return (2);
}
