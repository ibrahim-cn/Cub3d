/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_v2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ican <ican@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 02:27:41 by ican              #+#    #+#             */
/*   Updated: 2025/12/11 02:27:41 by ican             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	parse_rgb(char *line)
{
	int	i;
	int	j;
	int	val;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (!line[i])
		return (-1);
	j = i;
	while (line[j] && ft_isdigit(line[j]))
		j++;
	while (line[j] && line[j] == ' ')
		j++;
	if (line[j] != '\0')
		return (-1);
	val = ft_atoi(line + i);
	if (val < 0 || val > 255)
		return (-1);
	return (val);
}

static void	validate_ceiling(t_cub3d *cub)
{
	char	**rgb;
	int		i;

	rgb = ft_split(cub->comp->c, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		free_split(rgb);
		error_msg("Invalid ceiling color format\n", 1, cub);
	}
	i = 0;
	while (i < 3)
	{
		cub->comp->ceiling_color[i] = parse_rgb(rgb[i]);
		if (cub->comp->ceiling_color[i] == -1)
		{
			free_split(rgb);
			error_msg("Invalid ceiling color value (0-255 only)\n", 1, cub);
		}
		i++;
	}
	free_split(rgb);
}

void	validate_colors(t_cub3d *cub)
{
	char	**rgb;
	int		i;

	rgb = ft_split(cub->comp->f, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		free_split(rgb);
		error_msg("Invalid floor color format\n", 1, cub);
	}
	i = -1;
	while (++i < 3)
	{
		cub->comp->floor_color[i] = parse_rgb(rgb[i]);
		if (cub->comp->floor_color[i] == -1)
		{
			free_split(rgb);
			error_msg("Invalid floor color value (0-255 only)\n", 1, cub);
		}
	}
	free_split(rgb);
	validate_ceiling(cub);
}
