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
