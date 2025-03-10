/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:02:19 by ashahbaz          #+#    #+#             */
/*   Updated: 2025/02/18 14:40:26 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <mlx.h>
#include <math.h>
# include "gnl/get_next_line.h"


# define SPRITE 50

typedef struct s_player
{
	double		x;
	double		y;
	int			count;
	double		angle;
}	t_player;

typedef struct s_texture
{
	char	*path;
	double	x;
	double	y;
}	t_texture;

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

//validate_args
int validate_args(int argc, char **argv);

//init_game
int init_game(t_game *game, int fd);
void fill_file(char **map);

//split
char	**split(char const *s, char c);
size_t	count_words(char const *s, char c);

//read_map
char	**read_map(int fd);

//map_integrity
void	map_integrity(t_game *game);

//validate_textures
void	validate_textures(t_game *game);

//get_colour
void get_colour(t_game *game, char **dir, t_direction type);

//init_window
void	init_window(t_game *game);

#endif
