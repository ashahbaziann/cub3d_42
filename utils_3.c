/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:49:43 by ashahbaz          #+#    #+#             */
/*   Updated: 2025/02/17 13:58:32 by ashahbaz         ###   ########.fr       */
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
int textures_all_set(t_game *game)
{
	//t_texture	*tmp;

	//tmp = game -> texture;
	if (!game -> west.path || !game -> east.path  || !game -> north.path  || !game -> south.path )
		return (0);
	if (!game -> floor || !game -> ceiling)
		return (0);
	return (1);
}
