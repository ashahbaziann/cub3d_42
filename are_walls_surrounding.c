/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   are_walls_surrounding.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:23:24 by ashahbaz          #+#    #+#             */
/*   Updated: 2025/02/07 18:48:49 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static void check_rows(t_game *game, int i)
{
	int		j;
	char	**map;

	j = 0;
	map = game -> map;
	if (!map[i] || !map[i][j])
		return;
	while(map[i][j] && map[i][j] == ' ')
		j++;
	if (map[i][j] && map[i][j] == '0')
		clean(game, NULL, "Missing walls 2!\n");
	if (map[i] && ft_strlen(map[i]) > 0)
		j = ft_strlen(map[i]) - 1;
	else
		return ;
	while (j >= 0 && (map[i][j] == ' ' || map[i][j] == '\0'))
		j--;
	if (j >= 0 && map[i][j] == '0')
		clean(game, NULL, "Missing walls 4!\n");
}


static void check_columns(t_game *game ,int i, int j)
{
	//int		i;
	char	**map;

	//i = 0;
	map = game -> map;
	if (!map || !map[i])
		return ;
		printf("element = [%c] , j = %d\n",game -> map[i][j], j);
	while (map[i][j] && map[i][j] == ' ')
		i++;
	if (map[i][j] && map[i][j] == '0')
		clean(game, NULL, "Missing walls 7!\n");
	i = game -> height - 1;
	while (i >= 0 && (map[i][j] == ' ' || map[i][j] == '\0'))
		i--;
	if (i >= 0 && map[i][j] == '0')
		clean(game, NULL, "Missing walls 8!\n");
}

static void	are_horizontal_walls_valid(t_game *game)
{
	int i;

	i = 0;
	while (game -> map[i])
	{
		if (game -> map[i][0] == '0')
			clean(game, NULL, "Missing walls 1!\n");
		else if (game ->map[i][0] == ' ')
			check_rows(game, i);
		if (game -> map[i] && game -> map[i][ft_strlen(game -> map[i]) - 1] == '0')
			clean(game, NULL, "Missing walls 3!\n");
		else
			check_rows(game, i);
		i++;
	}
}

static void	are_vertical_walls_valid(t_game *game)
{
	int	i;
	int	j;
	int max = max_column(game -> map);

	i = 0;
	j = 0;
	if (!game->map[0] || !game->map[game->height - 1])
		return;
	while (max != 0)
	{
		while (game -> map[i][j] == '\0')
		{
			i++;
			max--;
		}
		if (game -> map[i][j] == '0')
			clean(game, NULL, "Missing walls 5!\n");
		else if (game -> map[i][j] == ' ')
			check_columns(game,0, j);
		if (game -> map[game -> height - 1][j] == '0')
			clean(game, NULL, "Missing walls 6!\n");
		else
			check_columns(game,i, j);
		j++;
		max--;
	}
}

void	are_walls_surrounding(t_game *game)
{
	if (!game -> map)
		clean(game, NULL, "Invalid map!\n");
		printf("len %d\n", max_column(game->map));
	are_horizontal_walls_valid(game);
	are_vertical_walls_valid(game);
}
