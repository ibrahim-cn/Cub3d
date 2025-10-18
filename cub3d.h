/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ican <<ican@student.42.fr>>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:02:17 by ican              #+#    #+#             */
/*   Updated: 2025/10/18 15:03:24 by ican             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H


#include "libft/libft.h"
#include "get_next_line/get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

#define FLOOR '0'
#define WALL '1'

typedef struct s_map
{
	char	*name;
	char	**map_lines;

	int		fd;
}	t_map;

typedef struct s_cub3d
{
	t_map	*map;
}	t_cub3d;

typedef struct s_map_comp //map components
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f;
	char	*c;



}	t_map_comp;


void	error_msg(char *message, int code);
void	arg_controller(char **arg, int ac);
int		cub_check(char *file_name);
void	check_map_exist(t_cub3d *cub);



void	copy_map(t_cub3d *cub);

#endif