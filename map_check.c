/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ican <<ican@student.42.fr>>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 22:00:41 by aaydogdu          #+#    #+#             */
/*   Updated: 2025/10/18 15:44:45 by ican             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <string.h>

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
		error_msg("File could not found or opened\n", 2);
	}
	cub->map->fd = fd;
}

void	copy_map(t_cub3d *cub)
{
	char	*line;
	int		i;
	int		line_count;

	// Önce dosyadaki satır sayısını say
	line_count = 0;
	while (1)
	{
		line = get_next_line(cub->map->fd, 0);
		if (line == NULL)
			break;
		free(line); // Geçici olarak okunan satırı serbest bırak
		line_count++;
	}
	
	// Dosyayı tekrar aç (fd'yi sıfırla)
	close(cub->map->fd);
	cub->map->fd = open(cub->map->name, O_RDONLY);
	if (cub->map->fd < 0)
		error_msg("File could not be reopened\n", 2);
	
	// map_lines için bellek ayır
	cub->map->map_lines = (char **)malloc(sizeof(char *) * (line_count + 1));
	if (!cub->map->map_lines)
		error_msg("Memory allocation failed\n", 2);
	
	// Şimdi satırları oku ve kaydet
	i = 0;
	while (1)
	{
		line = get_next_line(cub->map->fd, 0);
		if (line == NULL)
			break;
		cub->map->map_lines[i] = line;
		i++;
	}
	cub->map->map_lines[i] = NULL;
	
// Son elemanı NULL yap
}
