/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:31:53 by ashahbaz          #+#    #+#             */
/*   Updated: 2025/02/07 16:27:39 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int init_game(t_game *game, int fd)
{
	game -> map = read_map(fd);
	game -> width = width(game -> map);
	game -> height = height(game -> map);
	//are_textures_valid(game);
	are_walls_surrounding(game);
	return (0);
}
