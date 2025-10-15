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

void error_msg(char *message, int code)
{
    printf("Error! %s", message);
    exit(code);
}

int empty(char c)
{
    if (c == '\n' || c == ' ' || c == '\t')
        return (1);
    else
        return (0);
}