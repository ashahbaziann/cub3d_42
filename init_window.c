/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:36:42 by ashahbaz          #+#    #+#             */
/*   Updated: 2025/02/17 18:23:50 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_window(t_game *game)
{
	game -> mlx = mlx_init();
	if (!game -> mlx)
		clean(game, NULL, "Couldn't create window!\n");
	game -> mlx_win = mlx_new_window(game -> mlx, game -> width * SPRITE,
			game -> height * SPRITE, "so_long");
	if (!game -> mlx_win)
		clean(game, NULL, "Couldn't create window!\n");
}
