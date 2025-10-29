/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaydogdu <aaydogdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:00:41 by ican              #+#    #+#             */
/*   Updated: 2025/10/29 12:15:26 by aaydogdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void all_free(t_cub3d *cub)
{
	free_map(cub);
	free_comp(cub);
}

void eliminate_one_line(t_cub3d *cub)
{
	char	*trimmed;

	if (check_tab(cub->map->one_line))
	{
		printf("error düzenle");
		exit(1);
	}
	if (!cub->map->one_line)
		return;
	trimmed = ft_strtrim(cub->map->one_line, "\t\n\v\f\r");
	if (!trimmed)
		error_msg("Memory allocation failed\n", 2, cub);
	free(cub->map->one_line);
	cub->map->one_line = trimmed;
	split_one_line(cub);
}

void split_one_line(t_cub3d *cub)
{
	char	**lines;

	lines = ft_split(cub->map->one_line, '\n');
	cub->map->map_lines = lines;
}

int main(int ac, char **arg)
{
	static t_cub3d	cub;
	static t_map	map;
	static t_map_comp	comp; // zero-initialized

	cub.map = &map;
	cub.comp = &comp;
	if (ac != 2)
		error_msg("Wrong number of arguments!\n", 1, &cub);
	if (cub_check(arg[1]))
		error_msg("Wrong Type of file\n", 2, &cub);
	(cub.map)->name = arg[1];
	check_map_exist(&cub);
	copy_map(&cub);
	eliminate_one_line(&cub);
	is_map_valid(cub.map->map_lines, &cub);
	int i = 0;
	while (cub.map->map_lines[i] != NULL)
	{
		printf("%s", cub.map->map_lines[i]);
		printf("\n");
		i++;
	}
	//is_map_valid(cub.map->map_lines, &cub);
	//printf("NO: %s\n", cub.comp->no);
	all_free(&cub);
	return (0);
}