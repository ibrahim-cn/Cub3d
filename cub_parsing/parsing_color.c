#include "../cub3d.h"

static int	parse_color_value(char **ptr, t_cub3d *cub, int is_last)
{
	char	*start;
	int		len;

	start = *ptr;
	len = 0;
	while (**ptr && (is_last || **ptr != ',') && \
			(ft_isdigit(**ptr) || **ptr == ' ' || **ptr == '\t' || \
			(is_last && **ptr == '\n')))
	{
		if (ft_isdigit(**ptr))
			len++;
		(*ptr)++;
	}
	if ((!is_last && **ptr != ',') || len == 0)
		error_msg("Invalid RGB color format\n", 1, cub);
	return (ft_atoi(start));
}

static void	validate_rgb_values(int r, int g, int b, t_cub3d *cub)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		error_msg("RGB color values must be between 0 and 255\n", 1, cub);
}

static char	*prepare_color_string(char *line)
{
	char	*ptr;
	char	*trimmed;

	ptr = line;
	while (*ptr && !ft_empty(*ptr))
		ptr++;
	trimmed = trim_spaces(ptr);
	if (!trimmed || !*trimmed)
		return (NULL);
	return (trimmed);
}

char	*extract_color(char *line, t_cub3d *cub)
{
	char	*trimmed;
	char	*ptr;
	int		r, g, b;

	trimmed = prepare_color_string(line);
	if (!trimmed)
		return (NULL);
	if (count_commas(trimmed) != 2)
		error_msg("Invalid RGB color format (must be: R,G,B)\n", 1, cub);
	ptr = trimmed;
	r = parse_color_value(&ptr, cub, 0);
	if (*ptr == ',')
		ptr++;
	skip_spaces(&ptr);
	g = parse_color_value(&ptr, cub, 0);
	if (*ptr == ',')
		ptr++;
	skip_spaces(&ptr);
	b = parse_color_value(&ptr, cub, 1);
	validate_rgb_values(r, g, b, cub);
	return (ft_strdup(trimmed));
}

// Texture dosyasının varlığını ve XPM formatını kontrol eder
void	validate_texture_file(char *path, t_cub3d *cub)
{
	int		fd;
	char	*ext;
	int		len;

	if (!path || !*path)
		error_msg("Texture path is empty\n", 1, cub);
	
	// XPM uzantısını kontrol et
	len = ft_strlen(path);
	if (len < 5)
		error_msg("Texture file must have .xpm extension\n", 1, cub);
	ext = path + len - 4;
	if (ft_strncmp(ext, ".xpm", 4) != 0)
		error_msg("Texture file must be .xpm format\n", 1, cub);
	
	// Dosyanın varlığını kontrol et
	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_msg("Texture file could not be opened or does not exist\n", 1, cub);
	close(fd);
}