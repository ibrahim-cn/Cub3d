/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaydogdu <aaydogdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 10:46:27 by aaydogdu          #+#    #+#             */
/*   Updated: 2025/12/20 21:34:24 by aaydogdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	**duplicate_map(t_cub3d *cub)
{
	char	**copy;
	int		i;
	int		start;

	if (!cub || !cub->map || !cub->map->map_lines)
		error_msg("Invalid cub or map pointer\n", 1, cub);
	start = cub->map->map_start_index;
	copy = (char **)malloc(sizeof(char *) * (cub->map->map_height + 1));
	if (!copy)
		error_msg("Memory allocation failed for map copy\n", 1, cub);
	i = 0;
	while (i < cub->map->map_height)
	{
		if (!cub->map->map_lines[start + i])
		{
			while (i > 0)
				free(copy[--i]);
			free(copy);
			error_msg("Invalid map line in duplicate\n", 1, cub);
		}
		copy[i] = ft_strdup(cub->map->map_lines[start + i]);
		if (!copy[i])
		{
			while (i > 0)
				free(copy[--i]);
			free(copy);
			error_msg("Memory allocation failed for map copy line\n", 1, cub);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	free_map_copy(char **map_copy)
{
	int	i;

	if (!map_copy)
		return ;
	i = 0;
	while (map_copy[i])
	{
		free(map_copy[i]);
		i++;
	}
	free(map_copy);
}

static void	flood_fill(char **map, int x, int y)
{
	// 1. Sınır Kontrolü
	if (y < 0 || !map[y] || x < 0 || x >= (int)ft_strlen(map[y]) || !map[y][x])
		return ;

	// 2. Boşluk kontrolü: Boşluklar haritanın bir parçası değil, engel olarak görmeliyiz
	// Boşluklar üzerinden geçemeyiz çünkü bunlar haritanın bir parçası değil
	if (map[y][x] == ' ' || map[y][x] == '\t')
		return ;

	// 3. Durdurma Koşulu:
	// Eğer zaten işaretlenmişse ('F') dur.
	if (map[y][x] == 'F')
		return ;

	// 4. İşaretleme:
	// İster duvar ('1'), ister zemin ('0'), ister oyuncu olsun 'F' yapıyoruz.
	map[y][x] = 'F';

	// 5. Yayılma (4 Yön)
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}

static int	has_unreachable_area(char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			// Eğer flood fill sonrası haritada hala '0' VEYA '1' kaldıysa
			// demek ki oyuncunun olduğu ana kıtadan bağımsız bir ada var.
			if (map[y][x] == '0' || map[y][x] == '1') 
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

void	check_map_layout(t_cub3d *cub)
{
	char	**map_copy;

	if (!cub || !cub->map)
		error_msg("Invalid cub or map pointer\n", 1, cub);
	validate_chars_and_find_player(cub);
	map_copy = duplicate_map(cub);
	flood_fill(map_copy, cub->player.pos_x, cub->player.pos_y);
	if (has_unreachable_area(map_copy))
	{
		free_map_copy(map_copy);
		error_msg("Ups, double map! hihi 🤭🤭🤭\n", 1, cub);
	}
	free_map_copy(map_copy);
}
