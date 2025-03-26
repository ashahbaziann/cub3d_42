/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:52:17 by ashahbaz          #+#    #+#             */
/*   Updated: 2025/02/17 13:59:52 by ashahbaz         ###   ########.fr       */
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
	if (line1)
	{
		free (line1);
		line1 = NULL;
	}
	if (line2)
	{
		free (line2);
		line2 = NULL;
	}
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
	//map_free(game->file);
	free_line(game -> floor, game -> ceiling);
	free_line(game -> north.path, game -> south.path);
	free_line(game -> west.path, game -> east.path);
	// free_line(game -> north.image.img, game->north.image.address);
	// free_line(game -> south.image.img, game->south.image.address);
	// free_line(game -> west.image.img, game->west.image.address);
	// free_line(game -> east.image.img, game->east.image.address);
	if (game->north.image.img)
		mlx_destroy_image(game->mlx, game->north.image.img);
	if (game->south.image.img)
		mlx_destroy_image(game->mlx, game->south.image.img);
	if (game->west.image.img)
		mlx_destroy_image(game->mlx, game->west.image.img);
	if (game->east.image.img)
		mlx_destroy_image(game->mlx, game->east.image.img);
	//mlx_destroy_display(game->mlx);
	if (game -> mlx_win)
		mlx_destroy_window(game -> mlx, game -> mlx_win);
	if (game)
	{
		free(game);
		game = NULL;
	}
}
void	clean(t_game *game, char **map, char *str)
{
	(void)game;
	if (map)
		map_free(map);
	// if (game)
	// 	game_free(game);
	map = NULL;
	//game = NULL;
	error(str, NULL);
}
