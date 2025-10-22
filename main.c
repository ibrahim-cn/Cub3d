/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ican <<ican@student.42.fr>>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:00:41 by ican              #+#    #+#             */
/*   Updated: 2025/10/18 15:49:52 by ican             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int ac, char **arg)
{
    static t_cub3d	cub;
	static t_map	map;
    static t_map_comp comp; // zero-initialized

	cub.map = &map;
    cub.comp = &comp;
    if (ac != 2)
        error_msg("Wrong number of arguments!\n", 1, &cub);
    if (cub_check(arg[1]))
        error_msg("Wrong Type of file\n", 2, &cub);
    (cub.map)->name = arg[1];
    check_map_exist(&cub);
    copy_map(&cub);
    is_map_valid(cub.map->map_lines, &cub);

    printf("NO: %s",cub.comp->no);

    free_comp(&cub);
    free_map(&cub);

    /* int i = 0;
    while(cub.map->map_lines[i] != NULL ){
        printf("%s",cub.map->map_lines[i]);
        i++;
    } */
    return (0);
}
