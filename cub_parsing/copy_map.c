/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ican <<ican@student.42.fr>>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 12:05:35 by aaydogdu          #+#    #+#             */
/*   Updated: 2025/12/14 12:28:58 by ican             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	count_file_lines(t_cub3d *cub)
{
	char	*line;
	int		line_count;

	if (!cub || !cub->map || cub->map->fd < 0)
		error_msg("Invalid cub or map pointer\n", 2, cub);
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
	if (!cub || !cub->map || !cub->map->name)
		error_msg("Invalid cub or map pointer\n", 2, cub);
	if (cub->map->fd > 0)
		close(cub->map->fd);
	cub->map->fd = open(cub->map->name, O_RDONLY);
	if (cub->map->fd < 0)
		error_msg("File could not be reopened\n", 2, cub);
}

static void	allocate_map_memory(t_cub3d *cub, int line_count)
{
	if (!cub || !cub->map)
		error_msg("Invalid cub or map pointer\n", 2, cub);
	cub->map->map_lines = (char **)malloc(sizeof(char *) * (line_count + 1));
	if (!cub->map->map_lines)
		error_msg("Memory allocation failed\n", 2, cub);
	cub->map->one_line = (char *)malloc(1);
	if (!cub->map->one_line)
	{
		free(cub->map->map_lines);
		cub->map->map_lines = NULL;
		error_msg("Memory allocation failed\n", 2, cub);
	}
	cub->map->one_line[0] = '\0';
}

static void	read_and_store_lines(t_cub3d *cub)
{
	char	*line;
	int		i;
	char	*joined;

	if (!cub || !cub->map || !cub->map->map_lines || !cub->map->one_line)
		error_msg("Invalid cub or map pointer\n", 2, cub);
	i = 0;
	while (1)
	{
		line = get_next_line(cub->map->fd, 0);
		if (line == NULL)
			break ;
		cub->map->map_lines[i] = line;
		joined = ft_strjoin(cub->map->one_line, line);
		if (!joined)
		{
			free(line);
			error_msg("Memory allocation failed\n", 2, cub);
		}
		free(cub->map->one_line);
		cub->map->one_line = joined;
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
