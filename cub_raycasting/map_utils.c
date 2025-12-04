#include "../cub3d.h"

static int	get_row_len(char *row)
{
	int	len;

	len = ft_strlen(row);
	while (len > 0 && (row[len - 1] == '\n' || row[len - 1] == '\r'))
		len--;
	return (len);
}

char	get_map_cell(t_cub3d *cub, int map_y, int map_x)
{
	int		abs_y;
	char	*row;
	int		len;

	if (!cub || !cub->map || !cub->map->map_lines)
		return ('1');
	if (map_y < 0 || map_y >= cub->map->map_height)
		return ('1');
	abs_y = cub->map->map_start_index + map_y;
	row = cub->map->map_lines[abs_y];
	if (!row)
		return ('1');
	len = get_row_len(row);
	if (map_x < 0 || map_x >= len)
		return ('1');
	if (row[map_x] == ' ')
		return ('1');
	return (row[map_x]);
}


