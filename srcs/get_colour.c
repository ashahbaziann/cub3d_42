/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colour.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:51:28 by ashahbaz          #+#    #+#             */
/*   Updated: 2025/05/25 18:51:35 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	only_digits(char *colour)
{
	int	i;

	i = 0;
	while (colour[i] == ' ')
		i++;
	while (colour[i])
	{
		if (colour[i] && (colour[i] < '0' || colour[i] > '9'))
		{
			if (colour[i] && is_whitespace(colour[i]))
			{
				while (colour[i] && is_whitespace(colour[i]))
					i++;
				if (colour[i] != '\0')
					return (0);
			}
			if (colour[i] && (colour[i] < 48 || colour[i] > 57))
				return (0);
		}
		if (!colour[i])
			return (1);
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
		{
			map_free(rgb);
			clean(game, NULL, "Invalid rgb values\n");
		}
		i++;
	}
	if (i != 3)
	{
		map_free(rgb);
		clean(game, NULL, "Invalid rgb values\n");
	}
}

static void	get_rgb(t_game *game, char **dir, t_direction type)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	rgb = split(*dir, ',');
	if (check_semicol(*dir) != 2)
	{
		map_free(rgb);
		clean(game, NULL, "Invalid arguments for textures\n");
	}
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
