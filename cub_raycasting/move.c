#include "../cub3d.h"

#define MOVE_SPEED 0.05
#define ROT_SPEED 0.03
#define PLAYER_SIZE 0.2 // Oyuncunun kapladığı alan (Hitbox boyutu)

// Verilen (x, y) noktasının haritada güvenli olup olmadığını kontrol eder
static int	is_safe_point(t_cub3d *cub, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;

	// Harita sınırları
	if (map_y < 0 || map_y >= cub->map->map_height)
		return (0);
	if (map_x < 0 || map_x >= (int)ft_strlen(cub->map->map_lines[map_y]))
		return (0);

	// Duvar veya Boşluk kontrolü
	if (cub->map->map_lines[map_y][map_x] == '1' || cub->map->map_lines[map_y][map_x] == ' ')
		return (0); // Yasak bölge

	return (1); // Güvenli
}

// Oyuncunun "Kutusu" (Hitbox) gideceği yere sığıyor mu?
// Sadece merkezi değil, 4 köşeyi de kontrol ediyoruz.
static int	check_hitbox(t_cub3d *cub, double new_x, double new_y)
{
	// Sol-Üst Köşe
	if (!is_safe_point(cub, new_x - PLAYER_SIZE, new_y - PLAYER_SIZE))
		return (0);
	// Sağ-Üst Köşe
	if (!is_safe_point(cub, new_x + PLAYER_SIZE, new_y - PLAYER_SIZE))
		return (0);
	// Sol-Alt Köşe
	if (!is_safe_point(cub, new_x - PLAYER_SIZE, new_y + PLAYER_SIZE))
		return (0);
	// Sağ-Alt Köşe
	if (!is_safe_point(cub, new_x + PLAYER_SIZE, new_y + PLAYER_SIZE))
		return (0);
	
	return (1); // Tüm köşeler güvenli, yürüyebilirsin.
}

void	move_player(t_cub3d *cub)
{
	double	move_x = 0;
	double	move_y = 0;

	// 1. Hareket Yönünü Belirle
	if (cub->keys.w)
	{
		move_x += cub->player.dir_x * MOVE_SPEED;
		move_y += cub->player.dir_y * MOVE_SPEED;
	}
	if (cub->keys.s)
	{
		move_x -= cub->player.dir_x * MOVE_SPEED;
		move_y -= cub->player.dir_y * MOVE_SPEED;
	}
	if (cub->keys.a)
	{
		move_x -= cub->player.plane_x * MOVE_SPEED;
		move_y -= cub->player.plane_y * MOVE_SPEED;
	}
	if (cub->keys.d)
	{
		move_x += cub->player.plane_x * MOVE_SPEED;
		move_y += cub->player.plane_y * MOVE_SPEED;
	}

	// 2. X Ekseninde Hareket Kontrolü (Kayma - Sliding için ayrı kontrol)
	// Oyuncunun Y'si değişmeden, sadece yeni X konumuna gitmesi güvenli mi?
	if (check_hitbox(cub, cub->player.pos_x + move_x, cub->player.pos_y))
		cub->player.pos_x += move_x;

	// 3. Y Ekseninde Hareket Kontrolü
	// Oyuncunun X'i değişmeden, sadece yeni Y konumuna gitmesi güvenli mi?
	if (check_hitbox(cub, cub->player.pos_x, cub->player.pos_y + move_y))
		cub->player.pos_y += move_y;
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
