/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaydogdu <aaydogdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 12:05:35 by aaydogdu          #+#    #+#             */
/*   Updated: 2025/12/11 12:05:36 by aaydogdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

static void	read_and_store_lines(t_cub3d *cub)
{
	char	*line;
	int		i;
	char	*joined;

	i = 0;
	while (1)
	{
		line = get_next_line(cub->map->fd, 0);
		if (line == NULL)
			break ;
		cub->map->map_lines[i] = line;
		joined = ft_strjoin(cub->map->one_line, line);
		if (!joined)
			error_msg("Memory allocation failed\n", 2, cub);
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
