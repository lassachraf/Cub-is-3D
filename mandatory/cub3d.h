/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:19:43 by alassiqu          #+#    #+#             */
/*   Updated: 2024/10/17 18:21:41 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include "../libs/mlx/mlx.h"
# include "../libs/libft/libft.h"
# include "../libs/get-next-line/get_next_line.h"

/*  Our defines  */
# define PI				3.14159265358979323846
# define RED			"\033[1;31m"
# define RESET			"\033[0m"
# define TILE_SIZE		32

# define ESC_KEY		65307

# define RIGHT_ARROW	65363
# define LEFT_ARROW		65361

# define A_KEY			97
# define W_KEY			119
# define D_KEY			100
# define S_KEY			115

# define ESC			53
# define W				13
# define A				0
# define S				1
# define D				2
# define L				123
# define R				124

# define DEG_TO_RAD(a)	((a) * PI / 180.0)

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

typedef struct s_ray
{
	float		ray_s;
	float		ray_x;
	float		ray_y;
	float		wall_h;
	float		wall_t;
	float		wall_b;
	float		ang_inc;
	float		ray_dist;
	float		curr_ang;
	///////////////
	int			x;
	int			y;
	int			hit;
	float		side;
	float		step_x;
	float		step_y;
	float		side_x;
	float		side_y;
	float		delta_x;
	float		delta_y;
	float		final_distance;
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
	t_tex		*gun;
	t_tex		*door;
	t_tex		*fstp;
	int			person;
	int			oc_door;
	t_player	*player;
	int			gun_shots;
}				t_cub3d;


// All prototypes :

// Parsing

long	ft_colors(t_cub3d *cub, char *s);
void	create_color(t_cub3d **cub, int type, char *s);

void	ft_open(t_cub3d *cub, char *filename);
void	ft_extension(char *mapfile, char *ext);

int     is_map_element(char c);
char	**skip_white_lines(char **map);
char	*free_and_join(char **line, char **lines, int fd);
char	*ft_strncpy_2(char *dest, char *src, unsigned int n);

void	get_2d_map(t_cub3d *cub, char *line);
void	map_parsing(t_cub3d **cub, char **map);

void	parsing(t_cub3d *cub, char *av);

int	    get_angle(char c);
int	    is_it_player(char c);
void	get_player(t_cub3d *cub);

void	load_textures(t_cub3d *cub);
int	    get_texture_color(t_tex *texture, int x, int y);
void	create_texture(t_cub3d **cub, int type, char *file);

int	    ft_exit(t_cub3d *cub);
int	    is_white_line(char *s);
void	skip_whitespaces(char **line);
void	ft_error(t_cub3d *cub, char *msg);
void	double_check(t_cub3d *cub, char **line, int count);




// Free memory

void	free_double(char **s);
void	general_free(t_cub3d *cub);
void	free_cub_element(t_cub3d *cub);
void	free_map_element(t_cub3d *cub);
void	free_texture(t_cub3d *cub, t_tex *tex);

// Main-utils

int		cub_loop(t_cub3d *cub);

float	normalize_angle(float angle);
int		ft_moving(int keycode, t_cub3d *cub);

float	calculate_ray_distance(t_cub3d *cub, float ray_angle);
void	my_mlx_pixel_put(t_cub3d *cub, float x, float y, int color);

void	dda(t_cub3d *cub, float *xy);
void	draw_wall_slice(t_cub3d *cub, int x, int wall_height, float ray_distance);

#endif /* CUB3D_H */