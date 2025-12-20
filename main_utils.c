/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaydogdu <aaydogdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 02:27:41 by ican              #+#    #+#             */
/*   Updated: 2025/12/20 23:35:05 by aaydogdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_existing_map_lines(t_cub3d *cub)
{
	int	i;

	if (!cub || !cub->map || !cub->map->map_lines)
		return ;
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
	int		len;

	count = 0;
	str = one_line;
	len = ft_strlen(one_line);
	while (*str)
	{
		if (*str == '\n')
			count++;
		str++;
	}
	if (len > 0 && one_line[len - 1] != '\n')
		count++;
	return (count);
}

static void	parse_lines_from_one_line(char **lines, char *one_line,
			int count, t_cub3d *cub)
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

void	eliminate_one_line(t_cub3d *cub)
{
	char	*trimmed;

	if (!cub || !cub->map)
		return ;
	if (cub->map->one_line && check_tab(cub->map->one_line))
		error_msg("Tab character found in map\n", 2, cub);
	if (!cub->map->one_line)
		return ;
	trimmed = ft_strtrim(cub->map->one_line, "\t\n\v\f\r");
	if (!trimmed)
		error_msg("Memory allocation failed\n", 2, cub);
	free(cub->map->one_line);
	cub->map->one_line = trimmed;
	split_one_line(cub);
}

void	split_one_line(t_cub3d *cub)
{
	char	**lines;
	int		count;

	if (!cub || !cub->map || !cub->map->one_line)
		return ;
	free_existing_map_lines(cub);
	count = count_lines_in_one_line(cub->map->one_line);
	lines = (char **)malloc(sizeof(char *) * (count + 1));
	if (!lines)
		error_msg("Memory allocation failed\n", 2, cub);
	parse_lines_from_one_line(lines, cub->map->one_line, count, cub);
	cub->map->map_lines = lines;
}
