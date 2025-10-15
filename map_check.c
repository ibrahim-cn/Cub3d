#include "cub3d.h"
#include <string.h>

int	cub_check(char *file_name)
{
	int	i;

	i = strlen(file_name);
	if (file_name[i - 1] == 'b' && file_name[i - 2] == 'u'
		&& file_name[i - 3] == 'c' && file_name[i - 4] == '.')
		return (0);
	else
		return (1);
}

void	check_map_exist(t_cub3d *cub)
{
	int	fd;

	fd = open(cub->map->name, O_RDONLY);
	if (fd < 0)
		error_msg("File could not found or opened\n", 2);
	close(fd);
}