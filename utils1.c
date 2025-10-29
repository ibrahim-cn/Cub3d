/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaydogdu <aaydogdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 09:15:59 by aaydogdu          #+#    #+#             */
/*   Updated: 2025/10/29 09:17:22 by aaydogdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
