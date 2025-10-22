/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ican <<ican@student.42.fr>>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 19:35:47 by ican              #+#    #+#             */
/*   Updated: 2025/10/11 19:37:41 by ican             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_msg(char *message, int code, t_cub3d *cub)
{
	printf("Error! %s", message);
	free_map(cub);
	free_comp(cub);
	exit(code);
}

int	check_tab(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\t')
			return (1);
		i++;
	}
	return (0);
}

int	empty(char c)
{
	if (c == '\n' || c == ' ')
		return (1);
	return (0);
}

char	*trim_spaces(char *str)
{
	while (*str && empty(*str))
		str++;
	if (!*str)
		return (NULL);
	return (str);
}

char	*extract_path(char *line)
{
	char	*ptr;

	ptr = line;
	while (*ptr && !empty(*ptr))
		ptr++;
	ptr = trim_spaces(ptr);
	if (!ptr || !*ptr)
		return (NULL);
	return (ft_strdup(ptr));
}

void	free_map(t_cub3d *cub)
{
	int	i;

	i = 0;
	while (cub->map->map_lines[i])
	{
		free(cub->map->map_lines[i]);
		i++;
	}
	free(cub->map->map_lines);
}

void	free_comp(t_cub3d *cub)
{
	if (cub->comp->so)
		free(cub->comp->so);
	if (cub->comp->ea)
		free(cub->comp->ea);
	if (cub->comp->no)
		free(cub->comp->no);
	if (cub->comp->we)
		free(cub->comp->we);
	if (cub->comp->f)
		free(cub->comp->f);
	if (cub->comp->c)
		free(cub->comp->c);
}
