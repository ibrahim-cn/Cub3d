#include "../cub3d.h"

/*static int	get_row_len(char *row)
{
	int	len;

	len = ft_strlen(row);
	while (len > 0 && (row[len - 1] == '\n' || row[len - 1] == '\r'))
		len--;
	return (len);
}*/

char	get_map_cell(t_cub3d *cub, int y, int x)
{
	// 1. Harita sınırları içinde miyiz? (Göreceli Y'ye göre)
	if (y < 0 || y >= cub->map->map_height)
		return (' ');

	// 2. Dosyadaki GERÇEK satır numarasını bul (Start Index ekle!)
	// İşte eksik olan sihirli dokunuş burası:
	int real_y = cub->map->map_start_index + y;

	// 3. Satır var mı ve X satır uzunluğu içinde mi?
	if (!cub->map->map_lines[real_y] || 
		x < 0 || x >= (int)ft_strlen(cub->map->map_lines[real_y]))
		return (' ');

	// 4. Doğru hücreyi döndür
	return (cub->map->map_lines[real_y][x]);
}


