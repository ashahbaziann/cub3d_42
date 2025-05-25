/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:26:31 by ashahbaz          #+#    #+#             */
/*   Updated: 2025/05/25 16:00:13 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	open_file(t_game *game, char *dir)
{
	int	fd;

	fd = open(dir, O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		clean(game, NULL, "Validation failed: Invalid textures\n");
	}
	close(fd);
}

static void	get_value(t_game *game, char **dir, char *line, t_direction type)
{
	char	**arr;

	arr = NULL;
	if (count_words(line, ' ') != 2)
		clean(game, NULL, "Validation failed: invalid texture arguments\n");
	arr = split(line, ' ');
	if (!*dir && arr[0] && !ft_strcmp(arr[0], get_direction(type)))
		*dir = ft_strdup(arr[1]);
	else
	{
		map_free(arr);
		clean(game, NULL, "Validation failed:  Invalid texture arguments\n");
	}
	map_free(arr);
	open_file(game, *dir);
}

static void	set_map(t_game *game, int i)
{
	if (!textures_all_set(game))
		clean(game, NULL, "Validation failed: map is not set\n");
	game->map = &game->file[i];
	row_last_char(game, game->map);
	fill_file(game->map);
	if (empty_map(game))
		clean(game, NULL, "Validation failed: map is not set\n");
	game->width = width(game->map);
	game->height = height(game->map);
	game->img.width = game->width;
	game->img.height = game->height;
	col_last_char(game);
}

static void	set_textures(t_game *game, char *line)
{
	if (ft_strnstr(line, "NO", ft_strlen(line)))
		get_value(game, &game->north.path, line, NO);
	else if (ft_strnstr(line, "SO", ft_strlen(line)))
		get_value(game, &game->south.path, line, SO);
	else if (ft_strnstr(line, "EA", ft_strlen(line)))
		get_value(game, &game->east.path, line, EA);
	else if (ft_strnstr(line, "WE", ft_strlen(line)))
		get_value(game, &game->west.path, line, WE);
	else if (ft_strnstr(line, "F", ft_strlen(line)))
		get_colour(game, &game->floor, line, F);
	else if (ft_strnstr(line, "C", ft_strlen(line)))
		get_colour(game, &game->ceiling, line, C);
	else
		clean(game, NULL, "Validation failed: invalid characters\n");
}

void	validate_textures(t_game *game)
{
	char	**file;
	int		i;

	i = 0;
	file = game->file;
	while (file[i])
	{
		if (textures_all_set(game))
			break ;
		set_textures(game, file[i]);
		i++;
	}
	set_map(game, i);
}
