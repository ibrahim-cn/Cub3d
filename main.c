/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaydogdu <aaydogdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:00:41 by ican              #+#    #+#             */
/*   Updated: 2025/11/08 11:39:15 by aaydogdu         ###   ########.fr       */
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

static void	free_existing_map_lines(t_cub3d *cub)
{
	int	i;

	if (!cub->map->map_lines)
		return;
	i = 0;
	while (cub->map->map_lines[i])
	{
		free(cub->map->map_lines[i]);
		i++;
	}
	free(cub->map->map_lines);
	cub->map->map_lines = NULL;
}

static int	count_lines_in_one_line(char *one_line)
{
	char	*str;
	int		count;

	count = 0;
	str = one_line;
	while (*str)
	{
		if (*str == '\n')
			count++;
		str++;
	}
	if (one_line[ft_strlen(one_line) - 1] != '\n')
		count++;
	return (count);
}

static void	parse_lines_from_one_line(char **lines, char *one_line, int count, t_cub3d *cub)
{
	char	*str;
	char	*start;
	int		len;
	int		i;

	i = 0;
	str = one_line;
	while (*str && i < count)
	{
		start = str;
		len = 0;
		while (*str && *str != '\n')
		{
			len++;
			str++;
		}
		lines[i] = ft_substr(start, 0, len);
		if (!lines[i])
			error_msg("Memory allocation failed\n", 2, cub);
		i++;
		if (*str == '\n')
			str++;
	}
	lines[i] = NULL;
}

void split_one_line(t_cub3d *cub)
{
	char	**lines;
	int		count;

	free_existing_map_lines(cub);
	count = count_lines_in_one_line(cub->map->one_line);
	lines = (char **)malloc(sizeof(char *) * (count + 1));
	if (!lines)
		error_msg("Memory allocation failed\n", 2, cub);
	parse_lines_from_one_line(lines, cub->map->one_line, count, cub);
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
	printf("NO: %s\n", cub.comp->no);
	all_free(&cub);
	return (0);
}
