/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:31:53 by ashahbaz          #+#    #+#             */
/*   Updated: 2025/03/10 14:09:29 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void ft_strcpy(char *dest, char *src, int len)
{
	int	i;
	int	j;
	int hold;

	i = 0;
	j = 0;
	while (src[i])
	{
		while (src[i] == '\t')
		{
			hold = j;
			while (j != hold + 4)
			{
				dest[j++] = ' ';
				len--;
			}
			i++;
		}
		dest[j++] = src[i++];
		len--;
	}
	while (len-- > 0)
		dest[j++] = ' ';
	dest[j] = '\0';
}

static int	tab_count(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\t')
			count += 3;
		i++;
	}
	return (count);
}

void fill_file(char **map)
{
	int		i;
	char	*tmp;
	size_t	max;
	int		tab;

	i = 0;
	max = (size_t)max_column(map);
	while (map[i])
	{
		tab = tab_count(map[i]);
		if (ft_strlen(map[i]) < max)
		{
			tmp = malloc(sizeof(char) * (max + 1));
			ft_strcpy(tmp, map[i], max);
			free_line(map[i], NULL);
			map[i] = tmp;
		}
		i++;
	}
}


static void init_textures(t_game *game)
{
	game -> north.path = NULL;
	game -> south.path = NULL;
	game -> east.path = NULL;
	game -> west.path =	NULL;
}


static void init_player(t_game *game)
{
	game -> player.x = 0;
	game -> player.y = 0;
	game -> player.count = 0;
	game -> player.angle = 0;
	game -> player.dx = 0;
	game -> player.dy = 0;
	game -> player.plane_x = 0;
	game -> player.plane_y = 0.66;


}



static void	init_ray(t_game *game)
{
	game -> ray.cameraX = 0;
	game -> ray.cameraY = 0;
	game -> ray.dir_x = 0;
	game -> ray.dir_y = 0;
	game -> ray.map_x = 0;
	game -> ray.map_y = 0;
	game -> ray.side_x = 0;
	game -> ray.side_y = 0;
	game -> ray.delta_x = 0;
	game -> ray.delta_y = 0;
	game -> ray.wallDist = 0;
	game -> ray.step_x = 0;
	game -> ray.step_y = 0;
	game -> ray.hit = 0;
	game -> ray.side = 0;
	game -> ray.lineHeight = 0;
}

int init_game(t_game *game, int fd)
{
	int i;

	i = 0;
	game -> file = read_map(fd);
	game -> width = 0;
	game -> height = 0;
	game -> map = NULL;
	game -> floor = NULL;
	game -> ceiling = NULL;
	game -> floor_colour = 0;
	game -> ceiling_colour = 0;
	// while (game->ray_angle[i] < NUM_RAYS)
	// {
	// 	game->ray_angle[i] = 0;
	// 	i++;
	// }
	init_textures(game);
	init_player(game);
	init_ray(game);
	//init_image(game);
	return (0);
}
