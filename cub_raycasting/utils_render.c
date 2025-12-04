#include "../cub3d.h"

void	my_mlx_pixel_put(t_cub3d *cub, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	dst = cub->imgt.addr + (y * cub->imgt.line_len + x * (cub->imgt.bpp / 8));
	*(unsigned int *)dst = color;
}

/* utils.c */

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

// Tek bir xpm dosyasını yükleyen yardımcı fonksiyon
static void	load_image(t_cub3d *cub, t_img *texture, char *path)
{
	int	width;
	int	height;

	// 1. XPM dosyasını MLX ile yükle
	texture->img = mlx_xpm_file_to_image(cub->mlx, path, &width, &height);
	if (!texture->img)
		error_msg("Texture file load failed (check path or file format)\n", 1, cub);

	// 2. Resmin veri adresini al (Piksel okumak için lazım)
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp, 
			&texture->line_len, &texture->endian);
	
	// Opsiyonel: Texture boyutlarını kontrol et (64x64 gibi sabit olması şart değil ama iyi olur)
}

void	init_textures(t_cub3d *cub)
{
	// Parsing aşamasında kaydettiğimiz yolları kullan
	load_image(cub, &cub->textures.no, cub->comp->no);
	load_image(cub, &cub->textures.so, cub->comp->so);
	load_image(cub, &cub->textures.we, cub->comp->we);
	load_image(cub, &cub->textures.ea, cub->comp->ea);
}