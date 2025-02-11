/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:50:42 by ashahbaz          #+#    #+#             */
/*   Updated: 2025/02/11 18:03:47 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void print_game(t_game *game)
{
	int i = 0;
	printf("north = %s\n", game -> texture -> north);
	printf("south = %s\n", game -> texture -> south);
	printf("east = %s\n", game -> texture -> east);
	printf("west = %s\n", game -> texture -> west);
	printf("floor = %s\n", game -> floor);
	printf("ceiling = %s\n", game -> ceiling);
	printf("f_colur = %d\n",game -> floor_colour);
	printf("c_colour = %d\n",game -> ceiling_colour);
	if (game -> map)
	{
		while (game -> map[i])
			printf("[[[%s]]]\n", game -> map[i++]);
	}
}

int main(int argc, char **argv)
{
	t_game	game;
	int		fd;

	if ((fd = validate_args(argc, argv)) == -1)
		return (1);
	init_game(&game, fd);
	validate_textures(&game);
	map_integrity(&game);
	// init_window(&game);
	// mlx_loop(game.mlx);
	print_game(&game);
}
