/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:23:12 by alassiqu          #+#    #+#             */
/*   Updated: 2024/11/11 18:26:05 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*  Headers  */

# include "../libs/get-next-line/get_next_line.h"
# include "../libs/libft/libft.h"
# include "../../mlx/mlx.h"
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

# define ESC_KEY		53

# define LEFT_ARROW		123
# define RIGHT_ARROW	124

# define A_KEY			0
# define W_KEY			13
# define D_KEY			2
# define S_KEY			1

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
	t_tex		*north;
	t_tex		*south;
	int			height;
	t_color		*colors;
}				t_map;

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
	t_player	*player;
}					t_cub3d;

/*  All prototypes  */

/*  Libs  */

char	*get_next_line(int fd);

/*  Executing  */

void	cast_fov(t_cub3d *cub);
int		cub_loop(t_cub3d *cub);

void	draw_wall_slice(t_cub3d *cub, t_ray ray, int x);
void	my_mlx_pixel_put(t_cub3d *cub, float x, float y, int color);

void	update(t_cub3d *cub);
int		ft_reset(int keycode, t_cub3d *cub);
int		ft_moving(int keycode, t_cub3d *cub);

float	calculate_ray_distance(t_cub3d *cub, t_ray *ray);

int		check_wall(t_cub3d *cub, float new_x, float new_y);

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

float	deg_to_rad(int angle);
float	normalize_angle(float angle);

void	parsing(t_cub3d *cub, char *av);

float	get_angle(char c);
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

/*  Free Memory  */

void	free_double(char **s);
void	general_free(t_cub3d *cub);
void	free_map_element(t_cub3d *cub);
void	free_cub_element(t_cub3d *cub);
void	free_texture(t_cub3d *cub, t_tex *tex);

#endif /* CUB3D_H */