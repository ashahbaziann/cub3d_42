/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:52:17 by ashahbaz          #+#    #+#             */
/*   Updated: 2025/02/07 14:58:03 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error(char *str, char *str2)
{
	while (*str)
		write (STDERR_FILENO, str++, 1);
	if (str2)
		free(str2);
	str2 = NULL;
	exit (1);
}

void	free_line(char	*line1, char *line2)
{
	free (line1);
	free (line2);
	line1 = NULL;
	line2 = NULL;
}
void	map_free(char **map)
{
	int	i;

	i = 0;
	if (map[i])
	{
		while (map[i])
		{
			free(map[i]);
			i++;
		}
		free(map[i]);
		map[i] = NULL;
		free(map);
		map = NULL;
	}
}

void	game_free(t_game *game)
{
	map_free(game->map);
	if (game -> mlx_win)
		mlx_destroy_window(game -> mlx, game -> mlx_win);
	if (game)
	{
		free(game);
		game = NULL;
	}
}
void	clean(t_game *game, char **copy, char *str)
{
	//printf("shit\n");
	if (copy)
		map_free(copy);
	//printf("shit1\n");
	// if (game)
	// 	game_free(game);
	//printf("shit3\n");
	copy = NULL;
	game = NULL;
	error(str, NULL);
}
