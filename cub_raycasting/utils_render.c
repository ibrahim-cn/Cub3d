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

	if (!path || !*path)
		error_msg("Texture path is NULL or empty\n", 1, cub);
	
	// Texture struct'ını sıfırla
	texture->img = NULL;
	texture->addr = NULL;
	texture->width = 0;
	texture->height = 0;
	texture->bpp = 0;
	texture->line_len = 0;
	texture->endian = 0;
	
	// 1. XPM dosyasını MLX ile yükle
	width = 0;
	height = 0;
	texture->img = mlx_xpm_file_to_image(cub->mlx, path, &width, &height);
	if (!texture->img)
		error_msg("Texture file load failed (check path or file format)\n", 1, cub);
	if (width <= 0 || height <= 0)
		error_msg("Invalid texture dimensions from mlx_xpm_file_to_image\n", 1, cub);

	// 2. Resmin veri adresini al (Piksel okumak için lazım)
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp, 
			&texture->line_len, &texture->endian);
	if (!texture->addr)
		error_msg("Texture data address failed\n", 1, cub);
	if (texture->line_len <= 0 || texture->bpp <= 0)
		error_msg("Invalid texture data parameters\n", 1, cub);
	
	// 3. Texture boyutlarını sakla
	texture->width = width;
	texture->height = height;
}

void	init_textures(t_cub3d *cub)
{
	// cub ve comp pointer'larını kontrol et
	if (!cub)
	{
		printf("Error! Cub pointer is NULL\n");
		exit(1);
	}
	if (!cub->comp)
	{
		printf("Error! Comp pointer is NULL\n");
		exit(1);
	}
	
	// Texture path'lerini kontrol et
	if (!cub->comp->no)
		error_msg("Missing NO texture path\n", 1, cub);
	if (!cub->comp->so)
		error_msg("Missing SO texture path\n", 1, cub);
	if (!cub->comp->we)
		error_msg("Missing WE texture path\n", 1, cub);
	if (!cub->comp->ea)
		error_msg("Missing EA texture path\n", 1, cub);
	
	// Parsing aşamasında kaydettiğimiz yolları kullan
	load_image(cub, &cub->textures.no, cub->comp->no);
	load_image(cub, &cub->textures.so, cub->comp->so);
	load_image(cub, &cub->textures.we, cub->comp->we);
	load_image(cub, &cub->textures.ea, cub->comp->ea);
}