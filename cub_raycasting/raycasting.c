/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaydogdu <aaydogdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 11:38:59 by aaydogdu          #+#    #+#             */
/*   Updated: 2025/11/08 11:50:23 by aaydogdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// Yardımcı fonksiyonları buraya prototype olarak ekleyebilir veya ayrı dosyalara koyabilirsin.
// static void init_ray_vars(...);
// static void perform_dda(...);
// static void calculate_wall_height(...);
// static void draw_wall_slice(...);

//#define TEX_WIDTH 64
//#define TEX_HEIGHT 64

void	raycasting(t_cub3d *cub)
{
	int		x;
	t_img	*texture;
	double	wall_x;
	int		tex_x;
	double	step;
	double	tex_pos;
	int		y;
	int		tex_y;
	int		color;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		// 1. Işın Pozisyonu ve Yönü
		cub->ray.camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
		cub->ray.ray_dir_x = cub->player.dir_x + cub->player.plane_x * cub->ray.camera_x;
		cub->ray.ray_dir_y = cub->player.dir_y + cub->player.plane_y * cub->ray.camera_x;

		cub->ray.map_x = (int)cub->player.pos_x;
		cub->ray.map_y = (int)cub->player.pos_y;

		// 2. DDA Hazırlığı
		cub->ray.delta_dist_x = fabs(1 / cub->ray.ray_dir_x);
		cub->ray.delta_dist_y = fabs(1 / cub->ray.ray_dir_y);

		if (cub->ray.ray_dir_x < 0)
		{
			cub->ray.step_x = -1;
			cub->ray.side_dist_x = (cub->player.pos_x - cub->ray.map_x) * cub->ray.delta_dist_x;
		}
		else
		{
			cub->ray.step_x = 1;
			cub->ray.side_dist_x = (cub->ray.map_x + 1.0 - cub->player.pos_x) * cub->ray.delta_dist_x;
		}
		if (cub->ray.ray_dir_y < 0)
		{
			cub->ray.step_y = -1;
			cub->ray.side_dist_y = (cub->player.pos_y - cub->ray.map_y) * cub->ray.delta_dist_y;
		}
		else
		{
			cub->ray.step_y = 1;
			cub->ray.side_dist_y = (cub->ray.map_y + 1.0 - cub->player.pos_y) * cub->ray.delta_dist_y;
		}

		// 3. DDA Algoritması
		int hit = 0;
		while (hit == 0)
		{
			if (cub->ray.side_dist_x < cub->ray.side_dist_y)
			{
				cub->ray.side_dist_x += cub->ray.delta_dist_x;
				cub->ray.map_x += cub->ray.step_x;
				cub->ray.side = 0;
			}
			else
			{
				cub->ray.side_dist_y += cub->ray.delta_dist_y;
				cub->ray.map_y += cub->ray.step_y;
				cub->ray.side = 1;
			}
			// Harita sınır kontrolü (Segfault önlemek için)
			if (cub->ray.map_y < 0 || cub->ray.map_y >= cub->map->height || 
				!cub->map->map_lines[cub->ray.map_y] ||
				cub->ray.map_x < 0 || cub->ray.map_x >= (int)ft_strlen(cub->map->map_lines[cub->ray.map_y]))
			{
				hit = 1; // Harita dışına çıktıysa döngüyü kır
			}
			else if (cub->map->map_lines[cub->ray.map_y][cub->ray.map_x] == '1')
				hit = 1;
		}

		// 4. Duvar Mesafesi ve Yüksekliği
		if (cub->ray.side == 0)
			cub->ray.perp_wall_dist = (cub->ray.side_dist_x - cub->ray.delta_dist_x);
		else
			cub->ray.perp_wall_dist = (cub->ray.side_dist_y - cub->ray.delta_dist_y);

		cub->ray.line_height = (int)(SCREEN_HEIGHT / cub->ray.perp_wall_dist);

		cub->ray.draw_start = -cub->ray.line_height / 2 + SCREEN_HEIGHT / 2;
		if (cub->ray.draw_start < 0)
			cub->ray.draw_start = 0;

		cub->ray.draw_end = cub->ray.line_height / 2 + SCREEN_HEIGHT / 2;
		if (cub->ray.draw_end >= SCREEN_HEIGHT)
			cub->ray.draw_end = SCREEN_HEIGHT - 1;

		// ---------------------------------------------------------
		// 5. TEXTURE SEÇİMİ VE HESAPLAMALAR (DÜZELTİLDİ)
		// ---------------------------------------------------------
		
		if (cub->ray.side == 0) // X ekseni
		{
			if (cub->ray.ray_dir_x < 0)
				texture = &cub->textures.we;
			else
				texture = &cub->textures.ea;
		}
		else // Y ekseni
		{
			if (cub->ray.ray_dir_y < 0)
				texture = &cub->textures.no;
			else
				texture = &cub->textures.so;
		}

		// wall_x hesabı
		if (cub->ray.side == 0)
			wall_x = cub->player.pos_y + cub->ray.perp_wall_dist * cub->ray.ray_dir_y;
		else
			wall_x = cub->player.pos_x + cub->ray.perp_wall_dist * cub->ray.ray_dir_x;
		wall_x -= floor(wall_x);

		// tex_x: Texture genişliğini dinamik kullanıyoruz
		tex_x = (int)(wall_x * (double)texture->width);
		if (cub->ray.side == 0 && cub->ray.ray_dir_x > 0)
			tex_x = texture->width - tex_x - 1;
		if (cub->ray.side == 1 && cub->ray.ray_dir_y < 0)
			tex_x = texture->width - tex_x - 1;

		// step: Texture yüksekliğini dinamik kullanıyoruz
		step = 1.0 * texture->height / cub->ray.line_height;
		tex_pos = (cub->ray.draw_start - SCREEN_HEIGHT / 2.0 + cub->ray.line_height / 2.0) * step;

		// ---------------------------------------------------------
		// 6. ÇİZİM DÖNGÜSÜ
		// ---------------------------------------------------------

		// TAVAN
		int ceil_c = create_rgb(cub->comp->ceiling_color[0], cub->comp->ceiling_color[1], cub->comp->ceiling_color[2]);
		y = 0;
		while (y < cub->ray.draw_start)
		{
			my_mlx_pixel_put(cub, x, y, ceil_c);
			y++;
		}

		// DUVAR
		y = cub->ray.draw_start;
		while (y < cub->ray.draw_end)
		{
			// Maskeleme yerine Modulo kullan (Farklı boyutlar için güvenli)
			tex_y = (int)tex_pos % texture->height; 
			tex_pos += step;
			
			// Güvenlik: tex_y negatif olmasın
			if (tex_y < 0) tex_y = 0;
			
			// Texture pixel'ini al
			char *dst = texture->addr + (tex_y * texture->line_len + tex_x * (texture->bpp / 8));
			color = *(unsigned int *)dst;

			my_mlx_pixel_put(cub, x, y, color);
			y++;
		}

		// ZEMİN
		int floor_c = create_rgb(cub->comp->floor_color[0], cub->comp->floor_color[1], cub->comp->floor_color[2]);
		y = cub->ray.draw_end;
		while (y < SCREEN_HEIGHT)
		{
			my_mlx_pixel_put(cub, x, y, floor_c);
			y++;
		}
		
		x++;
	}
}