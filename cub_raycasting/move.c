#include "../cub3d.h"
#define MOVE_SPEED 0.05
#define ROT_SPEED 0.03

void	move_player(t_cub3d *cub)
{
	double	new_x;
	double	new_y;

	// W Tuşu: İleri git (Yön vektörünü ekle)
	if (cub->keys.w)
	{
		new_x = cub->player.pos_x + cub->player.dir_x * MOVE_SPEED;
		new_y = cub->player.pos_y + cub->player.dir_y * MOVE_SPEED;
        // Basit Duvar Kontrolü: Gideceğimiz yer duvar değilse yürü
		if (get_map_cell(cub, (int)cub->player.pos_y, (int)new_x) != '1')
			cub->player.pos_x = new_x;
		if (get_map_cell(cub, (int)new_y, (int)cub->player.pos_x) != '1')
			cub->player.pos_y = new_y;
	}
	// S Tuşu: Geri git (Yön vektörünü çıkar)
	if (cub->keys.s)
	{
		new_x = cub->player.pos_x - cub->player.dir_x * MOVE_SPEED;
		new_y = cub->player.pos_y - cub->player.dir_y * MOVE_SPEED;
		if (get_map_cell(cub, (int)cub->player.pos_y, (int)new_x) != '1')
			cub->player.pos_x = new_x;
		if (get_map_cell(cub, (int)new_y, (int)cub->player.pos_x) != '1')
			cub->player.pos_y = new_y;
	}
    // A Tuşu: Sola git (Yön vektörüne dik hareket et - Plane vektörünü ters ekle)
    // Not: A ve D için dir_y ve dir_x'in yerleri değiştirilerek dik vektör elde edilir.
    // Ancak basitlik için plane vektörü zaten diktir, onu kullanabilirsin ya da:
    // Sol Vektör: (dir_y, -dir_x)
    if (cub->keys.a)
    {
        new_x = cub->player.pos_x - cub->player.plane_x * MOVE_SPEED;
        new_y = cub->player.pos_y - cub->player.plane_y * MOVE_SPEED;
        if (get_map_cell(cub, (int)cub->player.pos_y, (int)new_x) != '1')
            cub->player.pos_x = new_x;
        if (get_map_cell(cub, (int)new_y, (int)cub->player.pos_x) != '1')
            cub->player.pos_y = new_y;
    }
    // D Tuşu: Sağa git
    if (cub->keys.d)
    {
        new_x = cub->player.pos_x + cub->player.plane_x * MOVE_SPEED;
        new_y = cub->player.pos_y + cub->player.plane_y * MOVE_SPEED;
        if (get_map_cell(cub, (int)cub->player.pos_y, (int)new_x) != '1')
            cub->player.pos_x = new_x;
        if (get_map_cell(cub, (int)new_y, (int)cub->player.pos_x) != '1')
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
