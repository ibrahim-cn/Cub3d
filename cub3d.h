/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ican <<ican@student.42.fr>>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:02:17 by ican              #+#    #+#             */
/*   Updated: 2025/10/11 20:26:59 by ican             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H


#include "libft/libft.h"
#include <stdio.h>
#include <fcntl.h>

typedef struct s_map
{
	char	*name;
}	t_map;

typedef struct s_cub3d
{
	t_map	*map;
}	t_cub3d;


void	error_msg(char *message, int code);
void	arg_controller(char **arg, int ac);
int		cub_check(char *file_name);
void	check_map_exist(t_cub3d *cub);

#endif