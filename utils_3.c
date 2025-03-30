/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:49:43 by ashahbaz          #+#    #+#             */
/*   Updated: 2025/03/30 17:58:02 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_direction(t_direction type)
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

int	textures_all_set(t_game *game)
{
	if (!game->west.path || !game->east.path || !game->north.path
		|| !game->south.path)
		return (0);
	if (!game->floor || !game->ceiling)
		return (0);
	return (1);
}

int	is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

t_image	*get_dir(t_game *game, t_ray *ray)
{
	t_image	*img;

	img = NULL;
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			img = &game->east.image;
		else
			img = &game->west.image;
	}
	else
	{
		if (ray->dir_y > 0)
			img = &game->south.image;
		else
			img = &game->north.image;
	}
	return (img);
}

void	ft_strcpy(char *dest, char *src, int len)
{
	int	i;
	int	j;
	int	hold;

	i = 0;
	j = 0;
	while (src[i])
	{
		while (src[i] == '\t')
		{
			hold = j;
			while (j != hold + 4)
			{
				dest[j++] = ' ';
				len--;
			}
			i++;
		}
		dest[j++] = src[i++];
		len--;
	}
	while (len-- > 0)
		dest[j++] = ' ';
	dest[j] = '\0';
}
