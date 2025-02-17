/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:31:53 by ashahbaz          #+#    #+#             */
/*   Updated: 2025/02/17 13:39:27 by ashahbaz         ###   ########.fr       */
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
	game -> texture -> north =	NULL;
	game -> texture -> south =	NULL;
	game -> texture -> east =	NULL;
	game -> texture -> west =	NULL;
}


static void init_player(t_game *game)
{
	game -> player.x = 0;
	game -> player.y = 0;
	game -> player.count = 0;
	game -> player.angle = 0;
}

int init_game(t_game *game, int fd)
{
	game -> file = read_map(fd);
	// int i = 0;
	// while (game -> map[i])
	// 	printf("[%s]\n",game -> map[i++]);
	//fill_file(game -> file);
	game -> width = 0;
	game -> height = 0;
	game -> map = NULL;
	game -> floor = NULL;
	game -> ceiling = NULL;
	game -> floor_colour = 0;
	game -> ceiling_colour = 0;
	game -> texture = malloc(sizeof(t_texture));
	if (!game -> texture)
		clean(game, NULL, "Allocation failed\n");
	init_textures(game);
	init_player(game);
	return (0);
}
