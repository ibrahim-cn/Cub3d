/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ican <<ican@student.42.fr>>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:00:41 by ican              #+#    #+#             */
/*   Updated: 2025/10/11 19:29:58 by ican             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int ac, char **arg)
{
    static t_cub3d	cub;
	static t_map	map;

	cub.map = &map;
    if (ac != 2)
        error_msg("Wrong number of arguments!\n", 1);
    if (cub_check(arg[1]) == 1)
        error_msg("Wrong Type of file\n", 2);
    (cub.map)->name = arg[1];
    check_map_exist(&cub);
    //if ()


    return (0);
}