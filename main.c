/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:50:42 by ashahbaz          #+#    #+#             */
/*   Updated: 2025/03/13 19:25:38 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void print_game(t_game *game)
// {
// 	int i = 0;
// 	printf("north = %s\n", game -> north.path );
// 	printf("south = %s\n", game -> south.path );
// 	printf("east = %s\n", game -> east.path );
// 	printf("west = %s\n", game -> west.path );
// 	printf("floor = %s\n", game -> floor);
// 	printf("ceiling = %s\n", game -> ceiling);
// 	printf("f_colur = %d\n",game -> floor_colour);
// 	printf("c_colour = %d\n",game -> ceiling_colour);
// 	if (game -> map)
// 	{
// 		while (game -> map[i])
// 			printf("[%s]\n", game -> map[i++]);
// 	}
// }
static int end_game(t_game *game)
{
	clean(game, NULL, NULL);
	return (0);
}

static void the_game(t_game *game, int fd)
{
	init_game(game, fd);
	validate_textures(game);
	map_parsing(game);
	if (game -> player.count > 1 || game ->player.count == 0)
		clean(game, NULL, "More than one or absolute no player!\n");
	init_window(game);
	init_image(game);
	load_textures(game);
	mlx_hook(game->mlx_win, 2, 1L << 0, key_press, game);
    mlx_hook(game->mlx_win, 3, 1L << 1, key_release, game);
	mlx_loop_hook(game->mlx, update, game);
	mlx_hook(game->mlx_win, 17, 0, end_game, game);
	if (game->mlx_win)
		mlx_loop(game->mlx);
	clean(game,NULL,NULL);
}

int main(int argc, char **argv)
{
	t_game	game;
	int		fd;

	if ((fd = validate_args(argc, argv)) == -1)
		return (1);
	the_game(&game, fd);
}
