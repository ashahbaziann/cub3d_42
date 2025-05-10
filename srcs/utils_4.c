/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:21:17 by ashahbaz          #+#    #+#             */
/*   Updated: 2025/05/10 14:49:46 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	empty_map(t_game *game)
{
	int	i;

	i = 0;
	if (game->map)
	{
		while (game->map[i])
		{
			if (!line_is_empty(game->map[i]))
				return (0);
			i++;
		}
	}
	return (1);
}

void	row_last_char(t_game *game, char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		if (map[i][ft_strlen(map[i]) - 1] != '1')
			clean(game, NULL, "Missing row's last wall!\n");
		i++;
	}
}

void	col_last_char(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!game->map)
		return ;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == ' ')
			{
				if (i + 1 < game->height)
				{
					if (game->map[i + 1][j] != '1' &&
						!is_whitespace(game->map[i + 1][j]))
						clean(game, NULL, "Missing col's wall!\n");
				}
			}
			j++;
		}
		i++;
	}
}
