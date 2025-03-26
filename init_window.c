/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:36:42 by ashahbaz          #+#    #+#             */
/*   Updated: 2025/03/03 13:33:34 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_window(t_game *game)
{
	game -> mlx = mlx_init();
	if (!game -> mlx)
		clean(game, NULL, "Couldn't create window!\n");
	game -> mlx_win = mlx_new_window(game -> mlx, S_W,
			S_H, "cub_3d");
	if (!game -> mlx_win)
		clean(game, NULL, "Couldn't create window!\n");
}
void	init_image(t_game *game)
{
	game -> img.img = mlx_new_image(game -> mlx, S_W, S_H);
	game -> img.address = mlx_get_data_addr(game -> img.img, &game -> img.bpp, &game -> img.line_length, &game -> img.endian);
	game -> img.width = S_W;
	game -> img.height = S_H;
}