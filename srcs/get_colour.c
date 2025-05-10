/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colour.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:51:28 by ashahbaz          #+#    #+#             */
/*   Updated: 2025/05/08 14:47:30 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	only_digits(char *colour)
{
	int	i;

	i = 0;
	while (colour[i])
	{
		while (colour[i] == ' ')
			i++;
		if (!colour[i])
			break ;
		if (colour[i] && (colour[i] < 48 || colour[i] > 57))
			return (0);
		i++;
	}
	return (1);
}

static void	check_rgb(char **rgb, t_game *game)
{
	int	i;

	i = 0;
	while (rgb[i])
	{
		if (rgb[i] && !only_digits(rgb[i]))
			clean(game, NULL, "Invlaid rgb values\n");
		i++;
	}
	if (i != 3)
		clean(game, NULL, "Invlaid rgb values\n");
}

static void	get_rgb(t_game *game, char **dir, t_direction type)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	rgb = split(*dir, ',');
	if (count_words(*dir, ',') != 3)
		clean(game, NULL, "Invalid arguments for textures\n");
	check_rgb(rgb, game);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	map_free(rgb);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		clean(game, NULL, "Invalid rgb values\n");
	if (type == F)
		game -> floor_colour = r * 65536 + g * 256 + b;
	if (type == C)
		game -> ceiling_colour = r * 65536 + g * 256 + b;
}

void	get_colour(t_game *game, char **dir, char *line, t_direction type)
{
	if (line)
	{
		while (*line == ' ')
			line++;
		if (!ft_strncmp(line, get_direction(type), 1))
		{
			line++;
			while (*line == ' ')
				line++;
			*dir = ft_strdup(line);
			get_rgb(game, dir, type);
		}
	}
}
