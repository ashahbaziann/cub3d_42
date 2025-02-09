/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:02:19 by ashahbaz          #+#    #+#             */
/*   Updated: 2025/02/09 18:20:56 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <mlx.h>
# include "gnl/get_next_line.h"

typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double 		plane_y;
	double		moving_spd;
	double		rotate_spd;
}	t_player;
typedef struct s_texture
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}	t_texture;

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
	t_texture	*texture;
	t_player	*player;
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

//validate_args
int validate_args(int argc, char **argv);

//init_game
int init_game(t_game *game, int fd);

//split
char	**split(char const *s, char c);
size_t	count_words(char const *s, char c);

//read_map
char	**read_map(int fd);

//map_integrity
void	map_integrity(t_game *game);
#endif

//validate_textures
void	validate_textures(t_game *game);
