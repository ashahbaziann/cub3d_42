/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:26:31 by ashahbaz          #+#    #+#             */
/*   Updated: 2025/02/10 20:02:13 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	skip_empty_lines(char	**map, int *i)
{
	while (line_is_empty(map[*i]))
		(*i)++;
}
static char	*get_direction(t_direction type)
{
	if (type == NO)
		return ("NO");
	else if (type == SO)
		return ("SO");
	else if (type == EA)
		return ("EA");
	else if (type == WE)
		return ("WE");
	else if (type == F)
		return ("F");
	else if (type == C)
		return ("C");
	return (NULL);
}

static void get_texture_path(t_game *game, char **dir, char *line, t_direction type)
{
	char	**arr;

	if (count_words(line, ' ') != 2)
		clean(game, NULL, "Invalid arguments for textures\n");
	arr = split(line, ' ');
	if (arr[0] && !ft_strcmp(arr[0], get_direction(type)))
		*dir = ft_strdup(arr[1]);
	else if (arr[1])
		*dir = ft_strdup(arr[0]);
	map_free(arr);
}

int textures_all_set(t_game *game)
{
	t_texture	*tmp;

	tmp = game -> texture;
	if (!tmp -> west || !tmp -> east || !tmp -> north || !tmp -> south)
		return (0);
	if (!game -> floor || !game -> ceiling)
		return (0);
	return (1);
}

static int empty_map(t_game *game)
{
	int	i;

	i = 0;
	if (game -> map)
	{
		while (game -> map[i])
		{
			if (!line_is_empty(game -> map[i]))
				return (0);
			i++;
		}
	}
	return (1);
}
static void set_map(t_game *game, int i)
{
	if(!textures_all_set(game))
		clean(game, NULL, "Map is not set");
	game -> map = &game -> file[i];
	fill_file(game -> map);
	if(empty_map(game))
		clean(game, NULL, "Map is not set");
	game -> width = width(game -> map);
	game -> height = height(game -> map);
}
void	validate_textures(t_game *game)
{
	char	**file;
	int		i;

	i = 0;
	file = game -> file;
	while (file[i])
	{
		if (textures_all_set(game))
			break ;
		if (ft_strnstr(file[i], "NO", ft_strlen(file[i])))
			get_texture_path(game, &game -> texture -> north, file[i], NO);
		if (ft_strnstr(file[i], "SO", ft_strlen(file[i])))
			get_texture_path(game, &game -> texture -> south, file[i], SO);
		if (ft_strnstr(file[i], "EA", ft_strlen(file[i])))
			get_texture_path(game, &game -> texture -> east, file[i], EA);
		if (ft_strnstr(file[i], "WE", ft_strlen(file[i])))
			get_texture_path(game, &game -> texture -> west, file[i], WE);
		if (ft_strnstr(file[i], "F", ft_strlen(file[i])))
			get_texture_path(game, &game -> floor, file[i], F);
		if (ft_strnstr(file[i], "C", ft_strlen(file[i])))
			get_texture_path(game, &game -> ceiling, file[i], C);
		i++;
	}
	if (textures_all_set(game))
		set_map(game, i);
}
