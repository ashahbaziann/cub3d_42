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
	if (!str)
		exit (0);
	while (*str)
		write (STDERR_FILENO, str++, 1);
	if (str2)
		free(str2);
	str2 = NULL;
	exit (0);
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
	if (!map)
		return;
	while (map[i])
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
}

void	game_free(t_game *game)
{
	map_free(game->file);
	game->file = NULL;
	free_line(game -> floor, game -> ceiling);
	free_line(game -> north.path, game -> south.path);
	free_line(game -> west.path, game -> east.path);
	if (game->north.image.img)
		mlx_destroy_image(game->mlx, game->north.image.img);
	if (game->south.image.img)
		mlx_destroy_image(game->mlx, game->south.image.img);
	if (game->west.image.img)
		mlx_destroy_image(game->mlx, game->west.image.img);
	if (game->east.image.img)
		mlx_destroy_image(game->mlx, game->east.image.img);
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);	
	if (game->mlx_win)
	{
		mlx_clear_window(game->mlx, game->mlx_win);
		mlx_destroy_window(game -> mlx, game -> mlx_win);
		game ->mlx_win = NULL;
	}
	if(game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
}
void	clean(t_game *game, char **map, char *str)
{
	(void)map;
	(void)str;
	if (game)
		game_free(game);
	error(str, NULL);
}
