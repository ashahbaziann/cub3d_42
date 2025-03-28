/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_integrity.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:23:24 by ashahbaz          #+#    #+#             */
/*   Updated: 2025/03/12 16:40:53 by ashahbaz         ###   ########.fr       */
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



static void set_player(t_game *game, int i, int j)
{
	// if (game -> player.count > 1 || game ->player.count == 0)
	// 	clean(game, NULL, "More than one or absolute no player!\n");
	if (is_player(game -> map[i][j]))
	{
		game -> player.count++;
		if (game -> map[i][j] == 'N')
			game -> player.angle = 3 * M_PI / 2;
		else if (game -> map[i][j] == 'S')
			game -> player.angle = M_PI / 2;
		else if (game -> map[i][j] == 'W')
			game -> player.angle = 0;
		else if (game -> map[i][j] == 'E')
			game -> player.angle = M_PI;
		game -> player.x = j + 1 / 2;
		game -> player.y = i + 1 / 2;
		game -> player.dx = cos(game -> player.angle);
		game -> player.dy = sin(game -> player.angle);
		game->player.plane_x = -game->player.dy * 0.66;
		game->player.plane_y = game->player.dx * 0.66;
	}
}
void map_parsing(t_game *game)
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
				clean(game, NULL, "Invalid character");
			set_player(game, i, j);
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


