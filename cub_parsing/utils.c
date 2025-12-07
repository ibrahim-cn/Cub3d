/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaydogdu <aaydogdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 09:17:16 by aaydogdu          #+#    #+#             */
/*   Updated: 2025/10/29 09:17:17 by aaydogdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	char	*result;
	char	*trimmed;

	ptr = line;
	while (*ptr && !empty(*ptr))
		ptr++;
	ptr = trim_spaces(ptr);
	if (!ptr || !*ptr)
		return (NULL);
	// Sonundaki boşlukları ve newline'ları da temizle
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


