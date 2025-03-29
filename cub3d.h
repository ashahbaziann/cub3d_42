/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:02:19 by ashahbaz          #+#    #+#             */
/*   Updated: 2025/03/10 12:50:06 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <mlx.h>
#include <math.h>
#include <sys/time.h>
# include "gnl/get_next_line.h"


# define SPRITE 32
# define FOV	60
# define NUM_RAYS 120
# define S_W 2600
# define S_H 1800
# define W 119
# define A 97
# define S 115
# define D 100
# define L_A 65361
# define R_A 65363
# define EXIT 65307
# define SPEED 0.7
# define ROT_SPEED 0.3

typedef struct s_player
{
	double		x;
	double		y;
	int			count;
	double		angle;
	double		dx;
	double		dy;
	double		plane_x;
	double		plane_y;
	int			move_backward;
	int			move_forward;
	int			move_left;
	int			move_right;
	int			exit;
	int			rot_left;
	int			rot_right;
}	t_player;


typedef struct s_image
{
	void	*img;
	char	*address;
	int		bpp;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_image;

typedef struct s_texture
{
	char	*path;
	t_image	image;
}	t_texture;


typedef struct s_ray
{
	double	cameraX;
	double	cameraY;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_x;
	double	side_y;
	double	delta_x;
	double	delta_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	wall_dist;
	double	wall_x;
	int		line_height;
	double	draw_start;
	double	draw_end;
}	t_ray;

typedef	struct s_tex_info
{
	double	x;
	double	y;
	double	step;
	double	pos;
}	t_tex_info;

typedef struct s_game
{
	void		*mlx;
	void		*mlx_win;
	char		**file;
	char		**map;
	int			height;
	int			width;
	char		*floor;
	char		*ceiling;
	int			floor_colour;
	int			ceiling_colour;
	t_texture	north;
	t_texture	south;
	t_texture	west;
	t_texture	east;
	t_image		img;
	t_ray		ray;
	t_tex_info	tex;
	t_player	player;
} t_game;


typedef enum
{
	NO,
	SO,
	WE,
	EA,
	F,
	C,
} t_direction;

//update
int update(t_game *game);

//error
void	error(char *str, char *str2);
void	free_line(char	*line1, char *line2);
void	map_free(char **map);
void	game_free(t_game *game);
void	clean(t_game *game, char **copy, char *str);

//utils
char	*ft_strtrim(char *s1, char *set);
char	*another_strtrim(char *s1, char *set);
int		line_is_empty(char *str);
char	*ft_strdup(char *s1);
int		ft_strchr(char *s, int c);

//utils_1
int		is_whitespace(char c);
char	*substr_alter(char const *s, unsigned int start, size_t len);
int		height(char **map);
int		width(char **map);
int		max_column(char **map);


//utils_2
char	*ft_strrchr(char *s, int c);
char	*ft_strnstr(char *haystack, char *needle, size_t len);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);


//utils_3
char	*get_direction(t_direction type);
int		textures_all_set(t_game *game);
int		is_player(char c);

//validate_args
int		validate_args(int argc, char **argv);

//init_game
int		init_game(t_game *game, int fd);
void	fill_file(char **map);

//split
char	**split(char const *s, char c);
size_t	count_words(char const *s, char c);

//read_map
char	**read_map(int fd);

//map_integrity
void	map_parsing(t_game *game);

//validate_textures
void	validate_textures(t_game *game);

//get_colour
void	get_colour(t_game *game, char **dir, t_direction type);

//init_window
void	init_window(t_game *game);
void	init_image(t_game *game);

//////////////////////////////////////////////////////

//raycasting
//void cast_ray(t_game *player);
void draw_square(t_game *game, int x, int y, int size, int color);
void draw_player(t_game *game, int x, int y, int size, int color);
void my_mlx_pixel_put(t_image *img, int x, int y, int color);
void draw_map(t_game *game);
void raycast(t_game *game);

//events
int key_press(int keycode, t_game *game);
int key_release(int keycode, t_game *game);


//load_textures
void load_textures(t_game *game);


//draw
void draw_wall(t_game *game, int x, t_ray *ray);
void draw_ceiling_and_floor(t_game *game,int x, t_ray *ray);
#endif
