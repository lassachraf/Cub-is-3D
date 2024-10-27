/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:23:12 by alassiqu          #+#    #+#             */
/*   Updated: 2024/10/27 14:12:32 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*  Headers  */

# include "../libs/get-next-line/get_next_line.h"
# include "../libs/libft/libft.h"
# include "../libs/mlx/mlx.h"
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>

/*  Our defines  */

# define PI				3.14159265358979323846
# define RED			"\033[1;31m"
# define RESET			"\033[0m"
# define TILE_SIZE		32

# define ESC_KEY		65307

# define LEFT_ARROW		65361
# define RIGHT_ARROW	65363

# define A_KEY			97
# define W_KEY			119
# define D_KEY			100
# define S_KEY			115

# define C_KEY			99
# define O_KEY			111

# define G_KEY			103
# define R_KEY			114
// # define V_KEY			114
// # define F_KEY			114

# define MINIMAP_SCALE	0.2
# define PLAYER_RADIUS	3
# define LINE_LENGTH	10

/*  All structs  */

typedef struct s_tex
{
	int			bpp;
	int			end;
	int			szl;
	void		*img;
	void		*add;
	char		*file;
	int			width;
	int			height;
}				t_tex;

typedef struct s_color
{
	char		*ceil;
	char		*floor;
	long		ceil_h;
	long		floor_h;
}				t_color;

typedef struct s_player
{
	float		x;
	float		y;
	float		fov;
	t_tex		*tex;
	double		angle;
	int			count;
	float		rot_ang;
	float		movespeed;
	float		rotationspeed;
	int			turndirection;
	int			walkdirection;
	int			sidedirection;
}				t_player;

typedef struct s_map
{
	int			fd;
	char		**map;
	int			width;
	t_tex		*west;
	t_tex		*east;
	int			door_c;
	t_tex		*north;
	t_tex		*south;
	int			height;
	t_color		*colors;
	t_tex		*ani[73];
}				t_map;

typedef struct s_minimap
{
	int			color;
	int			tile_size;
	int			max_map_size;
	int			player_radius;
	int			max_mini_size;
}					t_minimap;

typedef struct s_wall
{
	int			end;
	int			start;
	int			color;
	float		tex_x;
	float		tex_y;
	float		ray_x;
	float		ray_y;
	float		wall_x;
}					t_wall;

typedef struct s_ray
{
	int			hit;
	int			side;
	int			map_x;
	int			map_y;
	float		ray_x;
	float		ray_y;
	int			wall_h;
	int			wall_t;
	int			wall_b;
	float		side_x;
	float		side_y;
	float		step_x;
	float		step_y;
	float		delta_x;
	float		delta_y;
	float		fl_dist;
	float		ang_inc;
	float		curr_ang;
	float		ray_dist;
	float		ray_start;
}				t_ray;

typedef struct s_gun
{
	int			is_shoot;
	int			is_focus;
	int			is_reload;
	int			state_hand;
	int			is_animation_run;
}					t_gun;

typedef struct s_cub3d
{
	int			bpp;
	int			szl;
	int			end;
	int			hov;
	int			wov;
	int			side;
	void		*mlx;
	void		*win;
	void		*img;
	void		*add;
	t_map		*map;
	t_tex		*gun;
	t_tex		*door;
	t_tex		*fstp;
	int			oc_door;
	t_player	*player;
	t_gun		info_gun;
	int			gun_shots;
}					t_cub3d;

/*  All prototypes  */

/*  Libs  */

char	*get_next_line(int fd);

void	free_double(char **s);
void	general_free(t_cub3d *cub);
void	free_map_element(t_cub3d *cub);
void	free_cub_element(t_cub3d *cub);
void	free_texture(t_cub3d *cub, t_tex *tex);

/*  Executing  */

int		gun_shots(t_cub3d *cub);
void	gun_focus(t_cub3d *cub);
void	reload_gun(t_cub3d *cub);
void	focus_shoot(t_cub3d *cub);
void	gun_default_view(t_cub3d *cub);

void	load_player(t_cub3d *cub);
void	default_shoot(t_cub3d *cub);
void	draw_gun(t_cub3d *cub, int index);

void	cast_fov(t_cub3d *cub);
int		cub_loop(t_cub3d *cub);

void	dda(t_cub3d *cub, float *xy);
void	draw_wall_slice(t_cub3d *cub, t_ray ray, int x);
void	my_mlx_pixel_put(t_cub3d *cub, float x, float y, int color);

int		ft_reset(int keycode, t_cub3d *cub);
int		ft_moving(int keycode, t_cub3d *cub);

void	draw_minimap(t_cub3d *cub);

float	calculate_ray_distance(t_cub3d *cub, t_ray *ray);

int		check_collision(t_cub3d *cub, float new_x, float new_y);

// int		gun_shots(t_cub3d *cub);

/*  Should be deleted after  */

void	update(t_cub3d *cub);

/*  Parsing  */

long	ft_colors(t_cub3d *cub, char *s);
int		ft_atoi_rgb(t_cub3d *cub, char *str);
void	create_color(t_cub3d **cub, int type, char *s);

void	ft_open(t_cub3d *cub, char *filename);
void	ft_extension(char *mapfile, char *ext);

int		is_map_element(char c);
char	**skip_white_lines(char **map);
char	*free_and_join(char **line, char **lines, int fd);
char	*ft_strncpy_2(char *dest, char *src, unsigned int n);

void	get_2d_map(t_cub3d *cub, char *line);
void	map_parsing(t_cub3d **cub, char **map);
void	check_surrounded(t_cub3d *cub, char **map);
void	alloc_and_fill_map(t_cub3d **cub, char **map);
void	general_check(t_cub3d *cub, char **map, int *i, int *j);

float	deg_to_rad(int angle);
float	normalize_angle(float angle);

void	get_file_content(t_cub3d *cub);
void	parsing(t_cub3d *cub, char *av);
void	get_textures_and_colors(t_cub3d *cub, char **line);
void	compare_and_set(t_cub3d **cub, char **s, int *count);
int		check_texture_color(t_cub3d **cub, char *line, int *count);

float	get_angle(char c);
int		is_it_player(char c);
void	get_player(t_cub3d *cub);
void	alloc_and_set(t_cub3d *cub);
int		player_in_doorway(t_cub3d *cub);

void	load_textures(t_cub3d *cub);
void	load_animation_textures(t_cub3d *cub);
int		get_texture_color(t_tex *texture, int x, int y);
void	add_texture(t_cub3d *cub, t_tex **tex, char *name);
void	create_texture(t_cub3d **cub, int type, char *file);

int		ft_exit(t_cub3d *cub);
int		is_white_line(char *s);
void	skip_whitespaces(char **line);
void	ft_error(t_cub3d *cub, char *msg);
void	double_check(t_cub3d *cub, char **line, int count);

#endif /* CUB3D_H */