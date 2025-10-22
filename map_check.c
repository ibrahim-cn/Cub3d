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
#include "libft/libft.h"
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
		error_msg("File could not found or opened\n", 2, cub);
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
		error_msg("File could not be reopened\n", 2, cub);
	
	// map_lines için bellek ayır
	cub->map->map_lines = (char **)malloc(sizeof(char *) * (line_count + 1));
	if (!cub->map->map_lines)
		error_msg("Memory allocation failed\n", 2, cub);
	
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

int	check_comp(char *line, t_map_comp *comp)
{
	line = trim_spaces(line);
	if (!line || !*line)
		return (0);
	if (check_tab(line))
		return (1);
	if (!ft_strncmp(line, "NO", 2) && empty(line[2]) && !comp->no)
		comp->no = extract_path(line + 2);
	else if (!ft_strncmp(line, "SO", 2) && empty(line[2]) && !comp->so)
		comp->so = extract_path(line + 2);
	else if (!ft_strncmp(line, "WE", 2) && empty(line[2]) && !comp->we)
		comp->we = extract_path(line + 2);
	else if (!ft_strncmp(line, "EA", 2) && empty(line[2]) && !comp->ea)
		comp->ea = extract_path(line + 2);
	else if (line[0] == 'F' && empty(line[1]) && !comp->f)
		comp->f = extract_path(line + 1);
	else if (line[0] == 'C' && empty(line[1]) && !comp->c)
		comp->c = extract_path(line + 1);
	else
		return (1);
	return (0);
}

void	is_map_valid(char **map_lines, t_cub3d *cub)
{
	int	i;

	i = 0;
	while (map_lines[i])
	{
		if (check_comp(map_lines[i], cub->comp))
			error_msg("Missing or wrong components\n", 1, cub);
		i++;
	}
}











/* int	check_comp(char *line, t_map_comp *comp) //her çağırmada tek satır kontrol edecek
{
	while(1)
	{
		if (ft_strncmp(line, "SO", 2) == 0 && empty(line[2]) && !comp->so)
			comp->so = ft_strdup(line);
		else
		 return (1);
	}
	return (1);
}

void	is_map_valid(t_cub3d *cub)
{
	//char	*line;
	int	i;

	i = 0;
	while (cub->map->map_lines[i])
	{
		//cub->map->map_lines[i] = get_next_line(cub->map->fd, 0);
		printf("%s\n", cub->map->map_lines[0]);
		if (check_comp(cub->map->map_lines[i], cub->comp))
			error_msg("Missing or wrong components\n", 1);
		i++;
	}
	printf("Component found: %s \n", cub->comp->so);
} */