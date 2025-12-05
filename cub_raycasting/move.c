#include "../cub3d.h"
#define MOVE_SPEED 0.05
#define ROT_SPEED 0.03

static int	is_valid_move(t_cub3d *cub, double new_y, double new_x)
{
	int	x;
	int	y;

	x = (int)new_x;
	y = (int)new_y;

	// 1. Harita Yüksekliği Kontrolü
	if (y < 0 || y >= cub->map->map_height)
		return (0); // Harita dışı

	// 2. Satır Uzunluğu Kontrolü (Segfault ve Görünmez Duvarı Önler)
	// Gideceğimiz x, o satırın uzunluğundan büyükse durmalıyız.
	if (x < 0 || x >= (int)ft_strlen(cub->map->map_lines[y]))
		return (0);

	// 3. Duvar ve Boşluk Kontrolü
	// Sadece '1' değil, ' ' (boşluk) karakterine de girmemeliyiz.
	if (cub->map->map_lines[y][x] == '1' || cub->map->map_lines[y][x] == ' ')
		return (0);

	return (1); // Hareket güvenli
}

/* move.c içindeki move_player fonksiyonu */

void	move_player(t_cub3d *cub)
{
	double	new_x;
	double	new_y;

	// W Tuşu (İleri)
	if (cub->keys.w)
	{
		new_x = cub->player.pos_x + cub->player.dir_x * MOVE_SPEED;
		new_y = cub->player.pos_y + cub->player.dir_y * MOVE_SPEED;
		
		// X ekseninde hareket güvenli mi?
		if (is_valid_move(cub, cub->player.pos_y, new_x))
			cub->player.pos_x = new_x;
		// Y ekseninde hareket güvenli mi?
		if (is_valid_move(cub, new_y, cub->player.pos_x))
			cub->player.pos_y = new_y;
	}
	// S Tuşu (Geri)
	if (cub->keys.s)
	{
		new_x = cub->player.pos_x - cub->player.dir_x * MOVE_SPEED;
		new_y = cub->player.pos_y - cub->player.dir_y * MOVE_SPEED;

		if (is_valid_move(cub, cub->player.pos_y, new_x))
			cub->player.pos_x = new_x;
		if (is_valid_move(cub, new_y, cub->player.pos_x))
			cub->player.pos_y = new_y;
	}
	// A ve D tuşları için de aynı mantığı uygula...
    // (Aşağıda A ve D için de örnek var)
    if (cub->keys.a)
    {
        new_x = cub->player.pos_x - cub->player.plane_x * MOVE_SPEED;
        new_y = cub->player.pos_y - cub->player.plane_y * MOVE_SPEED;
        if (is_valid_move(cub, cub->player.pos_y, new_x))
            cub->player.pos_x = new_x;
        if (is_valid_move(cub, new_y, cub->player.pos_x))
            cub->player.pos_y = new_y;
    }
    if (cub->keys.d)
    {
        new_x = cub->player.pos_x + cub->player.plane_x * MOVE_SPEED;
        new_y = cub->player.pos_y + cub->player.plane_y * MOVE_SPEED;
        if (is_valid_move(cub, cub->player.pos_y, new_x))
            cub->player.pos_x = new_x;
        if (is_valid_move(cub, new_y, cub->player.pos_x))
            cub->player.pos_y = new_y;
    }
}

// Sağa-Sola Dönme (Rotasyon Matrisi)
void	rotate_player(t_cub3d *cub)
{
	double	old_dir_x;
	double	old_plane_x;
    double  speed;

    // Hangi yöne döneceğiz?
    if (cub->keys.right)
        speed = ROT_SPEED; // Sağa dönüş (pozitif açı) - Not: Koordinat sistemine göre eksi de olabilir, denemelisin.
    else if (cub->keys.left)
        speed = -ROT_SPEED; // Sola dönüş
    else
	{
        return ; // Tuşa basılmıyorsa çık
	}

	// Yön Vektörünü Döndür
	old_dir_x = cub->player.dir_x;
	cub->player.dir_x = cub->player.dir_x * cos(speed) - cub->player.dir_y * sin(speed);
	cub->player.dir_y = old_dir_x * sin(speed) + cub->player.dir_y * cos(speed);

	// Kamera Düzlemini (Plane) de Aynı Şekilde Döndür
	old_plane_x = cub->player.plane_x;
	cub->player.plane_x = cub->player.plane_x * cos(speed) - cub->player.plane_y * sin(speed);
	cub->player.plane_y = old_plane_x * sin(speed) + cub->player.plane_y * cos(speed);
}
