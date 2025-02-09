/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:31:53 by ashahbaz          #+#    #+#             */
/*   Updated: 2025/02/09 18:20:49 by ashahbaz         ###   ########.fr       */
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
		dest[j] = src[i];
		i++;
		j++;
		len--;
	}
	while (len > 0)
	{
		dest[j] = ' ';
		j++;
		len--;
	}
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

static void fill_file(char **map)
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

int init_game(t_game *game, int fd)
{
	game -> file = read_map(fd);
	// int i = 0;
	// while (game -> map[i])
	// 	printf("[%s]\n",game -> map[i++]);
	fill_file(game -> file);
	game -> width = width(game -> file);
	game -> height = height(game -> file);
	game -> map = NULL;
	game -> floor = NULL;
	game -> ceiling = NULL;
	game -> texture = malloc(sizeof(t_texture));
	if (!game -> texture)
		clean(game, NULL, "Allocation failed\n");
	init_textures(game);
	return (0);
}
