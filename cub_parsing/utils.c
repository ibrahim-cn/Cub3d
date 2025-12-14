/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ican <<ican@student.42.fr>>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 09:17:16 by aaydogdu          #+#    #+#             */
/*   Updated: 2025/12/14 12:24:18 by ican             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	error_msg(char *message, int code, t_cub3d *cub)
{
	printf("Error! %s", message);
	if (cub)
	{
		free_map(cub);
		free_comp(cub);
	}
	exit(code);
}

char	*trim_spaces(char *str)
{
	while (*str && ft_empty(*str))
		str++;
	if (!*str)
		return (NULL);
	return (str);
}

char	*extract_path(char *line)
{
	char	*ptr;
	char	*result;
	char	*trimmed;

	ptr = line;
	while (*ptr && !ft_empty(*ptr))
		ptr++;
	ptr = trim_spaces(ptr);
	if (!ptr || !*ptr)
		return (NULL);
	trimmed = ft_strtrim(ptr, " \t\n\r");
	if (!trimmed || !*trimmed)
	{
		if (trimmed)
			free(trimmed);
		return (NULL);
	}
	result = trimmed;
	return (result);
}

int	count_commas(char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == ',')
			count++;
		str++;
	}
	return (count);
}

void	skip_spaces(char **ptr)
{
	while (**ptr && (**ptr == ' ' || **ptr == '\t'))
		(*ptr)++;
}
