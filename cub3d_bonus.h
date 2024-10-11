/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:23:12 by alassiqu          #+#    #+#             */
/*   Updated: 2024/10/11 15:18:45 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*  Headers  */

# include "libs/get-next-line/get_next_line.h"
# include "libs/libft/libft.h"
# include "libs/mlx/mlx.h"
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

# define DEG_TO_RAD(a)	((a) * PI / 180.0)

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
	double		angle;
	int			count;
	float		rot_ang;
	float		movespeed;
	float		rotationspeed;
	int			turndirection;
	int			walkdirection;
	int			sidedirection;
}				t_player;

typedef struct s_door
{
	int	x;
	int	y;
}				t_door;

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
	t_door		*doors;
	t_color		*colors;
}				t_map;

// typedef struct s_ray
// {
// 	int			x;
// 	int			y;
// 	int			hit;
// 	float		side;
// 	float		step_x;
// 	float		step_y;
// 	float		ray_dir_x;
// 	float		ray_dir_y;
// 	float		side_dist_x;
// 	float		side_dist_y;
// 	float		delta_dist_x;
// 	float		delta_dist_y;
// 	float		final_distance;
// }				t_ray;

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
	t_tex		*door;
	int			oc_door;
	t_player	*player;
}				t_cub3d;

/*  All prototypes  */

void	set_nb_doors(t_map *mapp);
int		check_if_player_in_wall(t_cub3d *cub);

/*  Libs  */

char    *get_next_line(int fd);

void	free_double(char **s);
void	general_free(t_cub3d *cub);
void	free_map_element(t_cub3d *cub);
void	free_cub_element(t_cub3d *cub);

/*  Main-utils  */

void	cast_fov(t_cub3d *cub);
int		cub_loop(t_cub3d *cub);

float	normalize_angle(float angle);

float   calculate_ray_distance(t_cub3d *cub, float ray_angle);

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

void	get_file_content(t_cub3d *cub);
void	parsing(t_cub3d *cub, char *av);
void	get_textures_and_colors(t_cub3d *cub, char **line);
void	compare_and_set(t_cub3d **cub, char **s, int *count);
int		check_texture_color(t_cub3d **cub, char *line, int *count);

int		get_angle(char c);
int		is_it_player(char c);
void	get_player(t_cub3d *cub);
void	alloc_and_set(t_cub3d *cub);

void	load_textures(t_cub3d *cub);
int		get_texture_color(t_tex *texture, int x, int y);
void	add_texture(t_cub3d *cub, t_tex **tex, char *name);
void	create_texture(t_cub3d **cub, int type, char *file);

int		ft_exit(t_cub3d *cub);
int		is_white_line(char *s);
void	skip_whitespaces(char **line);
void	ft_error(t_cub3d *cub, char *msg);
void	double_check(t_cub3d *cub, char **line, int count);

/*  Rendering  */

void	dda(t_cub3d *cub, float *xy);
void	draw_wall_slice(t_cub3d *cub, int x, int wall_height, float ray_dist);

void	render_map(t_cub3d *cub);
void	render_map_2(t_cub3d *cub);
void	render_player(t_cub3d *cub, int x, int y);
void	render_square(t_cub3d *cub, float x, float y, int color);
void	render_circle(t_cub3d *cub, int cx, int cy, int radius, int color);

void	update(t_cub3d *cub);
int		reset(int keycode, t_cub3d *cub);
int		ft_moving(int keycode, t_cub3d *cub);
void	is_walkable(t_cub3d *cub, float new_x, float new_y);
void	my_mlx_pixel_put(t_cub3d *cub, float x, float y, int color);



#endif /* CUB3D_H */