/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaydogdu <aaydogdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 22:00:41 by aaydogdu          #+#    #+#             */
/*   Updated: 2025/12/11 02:27:41 by ican             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	cub_check(char *file_name)
{
	int	i;

	i = ft_strlen(file_name);
	if (file_name[i - 1] == 'b' && file_name[i - 2] == 'u'
		&& file_name[i - 3] == 'c' && file_name[i - 4] == '.')
		return (0);
	else
		return (1);
}

void	check_map_exist(t_cub3d *cub)
{
	int	fd;

	fd = open(cub->map->name, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		error_msg("File could not found or opened\n", 2, cub);
	}
	cub->map->fd = fd;
}

static int	count_file_lines(t_cub3d *cub)
{
	char	*line;
	int		line_count;

	line_count = 0;
	while (1)
	{
		line = get_next_line(cub->map->fd, 0);
		if (line == NULL)
			break ;
		free(line);
		line_count++;
	}
	get_next_line(cub->map->fd, 1);
	return (line_count);
}

static void	reopen_file(t_cub3d *cub)
{
	close(cub->map->fd);
	cub->map->fd = open(cub->map->name, O_RDONLY);
	if (cub->map->fd < 0)
		error_msg("File could not be reopened\n", 2, cub);
}

static void	allocate_map_memory(t_cub3d *cub, int line_count)
{
	cub->map->map_lines = (char **)malloc(sizeof(char *) * (line_count + 1));
	if (!cub->map->map_lines)
		error_msg("Memory allocation failed\n", 2, cub);
	cub->map->one_line = (char *)malloc(1);
	if (!cub->map->one_line)
		error_msg("Memory allocation failed\n", 2, cub);
	cub->map->one_line[0] = '\0';
}

static void	append_line_to_one_line(t_cub3d *cub, char *line)
{
	char	*joined;

	joined = ft_strjoin(cub->map->one_line, line);
	if (!joined)
		error_msg("Memory allocation failed\n", 2, cub);
	free(cub->map->one_line);
	cub->map->one_line = joined;
}

static void	read_and_store_lines(t_cub3d *cub)
{
	char	*line;
	int		i;

	i = 0;
	while (1)
	{
		line = get_next_line(cub->map->fd, 0);
		if (line == NULL)
			break ;
		cub->map->map_lines[i] = line;
		append_line_to_one_line(cub, line);
		i++;
	}
	cub->map->map_lines[i] = NULL;
	cub->map->height = i;
	get_next_line(cub->map->fd, 1);
}

void	copy_map(t_cub3d *cub)
{
	int		line_count;

	line_count = count_file_lines(cub);
	reopen_file(cub);
	allocate_map_memory(cub, line_count);
	read_and_store_lines(cub);
}

static int	set_texture_path(char **texture_ptr, char *line, t_cub3d *cub)
{
	*texture_ptr = extract_path(line);
	if (*texture_ptr)
		validate_texture_file(*texture_ptr, cub);
	return (0);
}

static int	process_texture_component(char *line, t_map_comp *comp,
			t_cub3d *cub)
{
	if (!ft_strncmp(line, "NO", 2) && ft_empty(line[2]) && !comp->no)
		return (set_texture_path(&comp->no, line + 2, cub));
	else if (!ft_strncmp(line, "SO", 2) && ft_empty(line[2]) && !comp->so)
		return (set_texture_path(&comp->so, line + 2, cub));
	else if (!ft_strncmp(line, "WE", 2) && ft_empty(line[2]) && !comp->we)
		return (set_texture_path(&comp->we, line + 2, cub));
	else if (!ft_strncmp(line, "EA", 2) && ft_empty(line[2]) && !comp->ea)
		return (set_texture_path(&comp->ea, line + 2, cub));
	return (-1);
}

static int	process_color_component(char *line, t_map_comp *comp, t_cub3d *cub)
{
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

	line = trim_spaces(line);
	if (!line || !*line)
		return (0);
	if (check_tab(line))
		return (1);
	result = process_texture_component(line, comp, cub);
	if (result == 0)
		return (0);
	result = process_color_component(line, comp, cub);
	if (result == 0)
		return (0);
	if (check_duplicate_component(line))
		return (1);
	return (2);
}

static int	all_comps_found(t_map_comp *comp)
{
	if (!comp->no || !comp->so || !comp->we || !comp->ea
		|| !comp->f || !comp->c)
		return (0);
	return (1);
}

static void	check_standalone_zero(char *line, t_cub3d *cub)
{
	char	*trimmed;

	trimmed = trim_spaces(line);
	if (trimmed && ft_strlen(trimmed) == 1 && trimmed[0] == '0')
		error_msg("Standalone '0' found outside map definition\n", 1, cub);
}

static void	handle_map_start_end(int i, int comp_status,
			int *start, int *end, t_cub3d *cub)
{
	if (comp_status == 2)
	{
		if (!all_comps_found(cub->comp))
			error_msg("Map line found before all components were set\n",
				1, cub);
		if (*start == -1)
			*start = i;
		*end = i;
	}
	else if (comp_status == 0 && *start != -1)
	{
		if (*end != -1)
			*end = i;
	}
}

static void	process_map_line(int i, int comp_status,
			int *start, int *end, t_cub3d *cub)
{
	if (comp_status == 1)
		error_msg("Invalid component format\n", 1, cub);
	else
		handle_map_start_end(i, comp_status, start, end, cub);
}

static void	find_map_bounds(char **map_lines, int *start, int *end,
			t_cub3d *cub)
{
	int	i;
	int	comp_status;

	i = 0;
	*start = -1;
	*end = -1;
	while (map_lines[i])
	{
		comp_status = check_comp(map_lines[i], cub->comp, cub);
		if (*start == -1 && comp_status == 2)
			check_standalone_zero(map_lines[i], cub);
		process_map_line(i, comp_status, start, end, cub);
		i++;
	}
	if (!all_comps_found(cub->comp))
		error_msg("Missing one or more map components\n", 1, cub);
	if (*start == -1)
		error_msg("No map found in file\n", 1, cub);
}

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
