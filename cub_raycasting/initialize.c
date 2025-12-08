#include "../cub3d.h"

void	init_game(t_cub3d *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		error_msg("MLX init failed\n", 1, cub);

	cub->win = mlx_new_window(cub->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	if (!cub->win)
		error_msg("MLX window failed\n", 1, cub);

	cub->imgt.img = mlx_new_image(cub->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!cub->imgt.img)
		error_msg("MLX image failed\n", 1, cub);

	cub->imgt.addr = mlx_get_data_addr(cub->imgt.img, &cub->imgt.bpp, 
			&cub->imgt.line_len, &cub->imgt.endian);
}

void set_vectors(t_cub3d *cub, double x, double y, double p_x, double p_y)
{
	cub->player.dir_x = x;
	cub->player.dir_y = y;
	cub->player.plane_x = p_x;
	cub->player.plane_y = p_y;
}

void	init_player(t_cub3d *cub)
{
	cub->player.pos_x += 0.5;
	cub->player.pos_y += 0.5;

	if (cub->player_dir == 'N')
		set_vectors(cub, 0, -1, 0.66, 0);
	else if (cub->player_dir == 'S')
		set_vectors(cub, 0, 1, -0.66, 0);
	else if (cub->player_dir == 'E')
		set_vectors(cub, 1, 0, 0, 0.66);
	else if (cub->player_dir == 'W')
		set_vectors(cub, -1, 0, 0, -0.66);
}
void	free_textures(t_cub3d *cub)
{
	if (!cub || !cub->mlx)
		return ;
	if (cub->textures.no.img)
		mlx_destroy_image(cub->mlx, cub->textures.no.img);
	if (cub->textures.so.img)
		mlx_destroy_image(cub->mlx, cub->textures.so.img);
	if (cub->textures.we.img)
		mlx_destroy_image(cub->mlx, cub->textures.we.img);
	if (cub->textures.ea.img)
		mlx_destroy_image(cub->mlx, cub->textures.ea.img);
	if (cub->imgt.img)
		mlx_destroy_image(cub->mlx, cub->imgt.img);
	cub->textures.no.img = NULL;
	cub->textures.so.img = NULL;
	cub->textures.we.img = NULL;
	cub->textures.ea.img = NULL;
	cub->imgt.img = NULL;
}
int	close_window(t_cub3d *cub)
{
	if (!cub)
		return (0);
	free_map(cub);
	free_comp(cub);
	free_textures(cub);
	if (cub->win)
		mlx_destroy_window(cub->mlx, cub->win);
	if (cub->mlx)
	{
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
		cub->mlx = NULL;
	}
	exit(0);
	return (0);
}

int	render_loop(t_cub3d *cub)
{
	move_player(cub);
	rotate_player(cub);
	raycasting(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->imgt.img, 0, 0);
	return (0);
}

int	key_press(int keycode, t_cub3d *cub)
{
	if (keycode == KEY_ESC)
		close_window(cub);
	else if (keycode == 119) // W
		cub->keys.w = 1;
	else if (keycode == 97) // A
		cub->keys.a = 1;
	else if (keycode == 115) // S
		cub->keys.s = 1;
	else if (keycode == 100) // D
		cub->keys.d = 1;
	else if (keycode == 65361) // Sol Ok
		cub->keys.left = 1;
	else if (keycode == 65363) // Sağ Ok
		cub->keys.right = 1;
	else if (keycode == 65307) // ESC
		close_window(cub);
	return (0);
}
int	key_release(int keycode, t_cub3d *cub)
{
	if (keycode == 119)
		cub->keys.w = 0;
	else if (keycode == 97)
		cub->keys.a = 0;
	else if (keycode == 115)
		cub->keys.s = 0;
	else if (keycode == 100)
		cub->keys.d = 0;
	else if (keycode == 65361)
		cub->keys.left = 0;
	else if (keycode == 65363)
		cub->keys.right = 0;
	return (0);
}
