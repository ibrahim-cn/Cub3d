/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaydogdu <aaydogdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:00:41 by ican              #+#    #+#             */
/*   Updated: 2025/11/08 11:39:15 by aaydogdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "minilibx-linux/mlx.h"

void all_free(t_cub3d *cub)
{
	free_map(cub);
	free_comp(cub);
}

void eliminate_one_line(t_cub3d *cub)
{
	char	*trimmed;

	if (check_tab(cub->map->one_line))
	{
		printf("error düzenle");
		exit(1);
	}
	if (!cub->map->one_line)
		return;
	trimmed = ft_strtrim(cub->map->one_line, "\t\n\v\f\r");
	if (!trimmed)
		error_msg("Memory allocation failed\n", 2, cub);
	free(cub->map->one_line);
	cub->map->one_line = trimmed;
	split_one_line(cub);
}

static void	free_existing_map_lines(t_cub3d *cub)
{
	int	i;

	if (!cub->map->map_lines)
		return;
	i = 0;
	while (cub->map->map_lines[i])
	{
		free(cub->map->map_lines[i]);
		i++;
	}
	free(cub->map->map_lines);
	cub->map->map_lines = NULL;
}

static int	count_lines_in_one_line(char *one_line)
{
	char	*str;
	int		count;

	count = 0;
	str = one_line;
	while (*str)
	{
		if (*str == '\n')
			count++;
		str++;
	}
	if (one_line[ft_strlen(one_line) - 1] != '\n')
		count++;
	return (count);
}

static void	parse_lines_from_one_line(char **lines, char *one_line, int count, t_cub3d *cub)
{
	char	*str;
	char	*start;
	int		len;
	int		i;

	i = 0;
	str = one_line;
	while (*str && i < count)
	{
		start = str;
		len = 0;
		while (*str && *str != '\n')
		{
			len++;
			str++;
		}
		lines[i] = ft_substr(start, 0, len);
		if (!lines[i])
			error_msg("Memory allocation failed\n", 2, cub);
		i++;
		if (*str == '\n')
			str++;
	}
	lines[i] = NULL;
}

void split_one_line(t_cub3d *cub)
{
	char	**lines;
	int		count;

	free_existing_map_lines(cub);
	count = count_lines_in_one_line(cub->map->one_line);
	lines = (char **)malloc(sizeof(char *) * (count + 1));
	if (!lines)
		error_msg("Memory allocation failed\n", 2, cub);
	parse_lines_from_one_line(lines, cub->map->one_line, count, cub);
	cub->map->map_lines = lines;
}

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
static void set_vectors(t_cub3d *cub, double x, double y, double p_x, double p_y)
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

int	close_window(t_cub3d *cub)
{
	if (!cub)
		return (0);
	if (cub->imgt.img)
		mlx_destroy_image(cub->mlx, cub->imgt.img);
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

	// 2. Sonra Yeni Konuma Göre Çiz
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

int main(int ac, char **arg)
{
	static t_cub3d	cub;
	static t_map	map;
	static t_map_comp	comp; // zero-initialized

	cub.map = &map;
	cub.comp = &comp;
	if (ac != 2)
		error_msg("Wrong number of arguments!\n", 1, &cub);
	if (cub_check(arg[1]))
		error_msg("Wrong Type of file\n", 2, &cub);
	(cub.map)->name = arg[1];
	check_map_exist(&cub);
	copy_map(&cub);
	eliminate_one_line(&cub);
	is_map_valid(cub.map->map_lines, &cub);

	init_game(&cub);
	init_textures(&cub);
	init_player(&cub);
	mlx_loop_hook(cub.mlx, render_loop, &cub);
	mlx_hook(cub.win, EVENT_KEY_PRESS, 1L << 0, key_press, &cub);
	mlx_hook(cub.win, EVENT_DESTROY, 0, close_window, &cub);
	mlx_hook(cub.win, 2, 1L << 0, key_press, &cub);
	mlx_hook(cub.win, 3, 1L << 1, key_release, &cub);
	
	mlx_loop(cub.mlx);
	/* int i = 0;
	while (cub.map->map_lines[i] != NULL)
	{
		printf("%s", cub.map->map_lines[i]);
		printf("\n");
		i++;
	}
	//is_map_valid(cub.map->map_lines, &cub);
	printf("NO: %s\n", cub.comp->no);
	*/
	all_free(&cub);
	return (0);
}
