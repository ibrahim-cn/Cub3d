/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ican <ican@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:02:17 by ican              #+#    #+#             */
/*   Updated: 2025/12/12 00:01:13 by ican             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include "./minilibx-linux/mlx.h"
# include <math.h>
# include <stdio.h>
# include <fcntl.h>

# define FLOOR '0'
# define WALL '1'
# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080
# define KEY_ESC 65307
# define EVENT_KEY_PRESS 2
# define EVENT_DESTROY 17
# define MOVE_SPEED 0.1
# define ROT_SPEED 0.1
# define PLAYER_SIZE 0.2

typedef struct s_map
{
	char	*name;
	char	**map_lines;
	int		height;
	int		fd;
	int		map_start_index;
	int		map_height;
	char	*one_line;

}	t_map;

typedef struct s_map_comp
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f;
	char	*c;
	int		floor_color[3];
	int		ceiling_color[3];
}	t_map_comp;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_tex_data
{
	t_img	*texture;
	int		tex_x;
	double	step;
	double	tex_pos;
}	t_tex_data;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_textures
{
	t_img	no;
	t_img	so;
	t_img	ea;
	t_img	we;
}	t_textures;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_cub3d
{
	void		*mlx;
	void		*win;
	t_img		imgt;
	t_map		*map;
	t_map_comp	*comp;
	char		player_dir;
	int			player_x;
	int			player_y;
	t_player	player;
	t_ray		ray;
	t_textures	textures;
	t_keys		keys;
}	t_cub3d;

void	error_msg(char *message, int code, t_cub3d *cub);
char	*trim_spaces(char *str);
char	*extract_path(char *line);
int		count_commas(char *str);
void	skip_spaces(char **ptr);
void	free_map(t_cub3d *cub);
void	free_comp(t_cub3d *cub);
void	free_split(char **split);
void	all_free(t_cub3d *cub);
int		check_tab(char *line);
int		ft_empty(char c);
char	*extract_color(char *line, t_cub3d *cub);
void	validate_texture_file(char *path, t_cub3d *cub);
int		cub_check(char *file_name);
void	check_map_exist(t_cub3d *cub);
void	copy_map(t_cub3d *cub);
int		check_comp(char *line, t_map_comp *comp, t_cub3d *cub);
void	is_map_valid(char **map_lines, t_cub3d *cub);
void	eliminate_one_line(t_cub3d *cub);
void	split_one_line(t_cub3d *cub);
void	init_game(t_cub3d *cub);
void	set_dir_vectors(t_cub3d *cub, double x, double y);
void	set_plane_vectors(t_cub3d *cub, double p_x, double p_y);
void	init_player(t_cub3d *cub);
void	free_textures(t_cub3d *cub);
int		close_window(t_cub3d *cub);
int		render_loop(t_cub3d *cub);
int		key_press(int keycode, t_cub3d *cub);
int		key_release(int keycode, t_cub3d *cub);
void	validate_colors(t_cub3d *cub);
void	check_map_layout(t_cub3d *cub);
void	validate_chars_and_find_player(t_cub3d *cub);
char	get_map_cell(t_cub3d *cub, int map_y, int map_x);
void	free_map_copy(char **map_copy);
void	raycasting(t_cub3d *cub);
void	init_ray_vars(t_cub3d *cub, int x);
void	init_dda(t_cub3d *cub);
void	perform_dda(t_cub3d *cub);
void	calculate_wall_height(t_cub3d *cub);
t_img	*select_texture(t_cub3d *cub);
void	calculate_texture_coords(t_cub3d *cub, t_img *texture,
			t_tex_data *tex_data);
void	draw_ceiling(t_cub3d *cub, int x);
void	draw_wall_slice(t_cub3d *cub, int x, t_tex_data *tex_data);
void	draw_floor(t_cub3d *cub, int x);
void	draw_column(t_cub3d *cub, int x, t_tex_data *tex_data);
void	my_mlx_pixel_put(t_cub3d *cub, int x, int y, int color);
int		create_rgb(int r, int g, int b);
void	init_textures(t_cub3d *cub);
void	move_player(t_cub3d *cub);
void	rotate_player(t_cub3d *cub);
int		all_comps_found(t_map_comp *comp);
void	init_texture_struct(t_img *texture);
void	find_map_bounds(char **map_lines, int *start, int *end,
			t_cub3d *cub);

#endif