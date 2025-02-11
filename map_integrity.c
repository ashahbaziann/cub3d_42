/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_integrity.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:23:24 by ashahbaz          #+#    #+#             */
/*   Updated: 2025/02/11 16:00:57 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void check_space_interval(t_game *game, int i, int j)
{
	char	**map;

	map = game -> map;
	if (i + 1 < game ->height - 1 && map[i][j] &&  map[i + 1][j] && map[i + 1][j] == '0')
		clean(game, NULL, "Missing walls!\n");
	if (j + 1 < game ->width - 1 && map[i][j] && map[i][j + 1] && map[i][j + 1] == '0')
		clean(game, NULL, "Missing walls!\n");
	if (i > 0 && map[i][j] && map[i - 1][j] && map[i - 1][j] == '0')
		clean(game, NULL, "Missing walls!\n");
	if (j > 0 && map[i][j] && map[i][j - 1] && map[i][j - 1] == '0')
		clean(game, NULL, "Missing walls!\n");
}


static int is_valid_char(char c)
{
	if (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ')
		return (1);
	return (0);
}

void map_integrity(t_game *game)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (i < game -> height)
	{
		j = 0;
		while (game -> map[i][j])
		{
			if (!is_valid_char(game -> map[i][j]))
			{
				printf("char is [%c]\n", game -> map[i][j]);
				clean(game, NULL, "Invalid character");
			}
			if (game -> map[i][j] == '0')
			{
				if (i == 0 || j == 0 || i == game -> height - 1 || j == game -> width - 1)
					clean(game, NULL, "Missing walls!\n");
			}
			else if (game -> map[i][j] == ' ')
				check_space_interval(game, i, j);
			j++;
		}
		i++;
	}
}
