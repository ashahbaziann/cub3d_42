/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:50:42 by ashahbaz          #+#    #+#             */
/*   Updated: 2025/03/03 14:05:52 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void print_game(t_game *game)
{
	int i = 0;
	printf("north = %s\n", game -> north.path );
	printf("south = %s\n", game -> south.path );
	printf("east = %s\n", game -> east.path );
	printf("west = %s\n", game -> west.path );
	printf("floor = %s\n", game -> floor);
	printf("ceiling = %s\n", game -> ceiling);
	printf("f_colur = %d\n",game -> floor_colour);
	printf("c_colour = %d\n",game -> ceiling_colour);
	if (game -> map)
	{
		while (game -> map[i])
			printf("[%s]\n", game -> map[i++]);
	}
}


void my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
    // if (x < 0 || y < 0 || x >= img->width || y >= img->height)
    // {
    //     return;
    // }

    char *dst = img->address + (y * img->line_length + x * (img->bpp / 8));
    *(unsigned int *)dst = color;
}



// static void color_ceiling_and_floor(t_game *game)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (i < game -> img.height)
// 	{
// 		j = 0;
// 		while (j < game ->img.width)
// 		{
// 			my_mlx_pixel_put(&game->img, j, i, game -> ceiling_colour);
// 			j++;
// 		}
// 		i++;
// 	}
// 	// while (i < game -> img.height)
// 	// {
// 	// 	j = 0;
// 	// 	while (j < game ->img.width)
// 	// 	{
// 	// 		my_mlx_pixel_put(&game -> img, j, i, game -> floor_colour);
// 	// 		j++;
// 	// 	}
// 	// 	i++;
// 	// }
// }

	static void	init_image(t_game *game)
{

	game -> img.img = mlx_new_image(game -> mlx, game -> width * SPRITE, game -> height * SPRITE);
	game -> img.address = mlx_get_data_addr(game -> img.img, &game -> img.bpp, &game -> img.line_length, &game -> img.endian);
	game -> img.width = game -> width * SPRITE;
	game -> img.height = game -> height * SPRITE;
	printf("Image width: %d, height: %d\n", game->img.width, game->img.height);
	printf("Game width: %d, height: %d\n", game -> width * SPRITE, game -> height * SPRITE);

}

void put_background(t_game *game, int color)
{
    int	i;
	int	j;

	i = 0;
	j = 0;
    int *pixels = (int *)game->img.address;
	while(i < game -> height * SPRITE)
	{
		j = 0;
		while (j < game -> width * SPRITE)
		{
            pixels[i * game -> width * SPRITE + j] = color;
			j++;
		}
		i++;
	}
}

void draw_square(t_game *game, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(i < size)
	{
		j = 0;
		while (j < size)
		{
            my_mlx_pixel_put(&game->img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void draw_player(t_game *game, int x, int y, int size, int color)
{
	draw_square(game, x + 4, y + 4, size - 10, color);
}

void draw_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	(void)game;
	while (i < game -> height)
	{
		j = 0;
		while (j < game -> width)
		{
			if (game -> map[i][j] == '1')
				draw_square(game, j * SPRITE , i * SPRITE , SPRITE - 1, 0);
			else
				draw_square(game, j * SPRITE , i * SPRITE , SPRITE - 1, 16777215);
			if (is_player(game -> map[i][j]))
				draw_player(game, game -> player.x - SPRITE / 2, game -> player.y - SPRITE / 2, SPRITE, 16777261);
			j++;
		}
		i++;
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
	init_window(&game);
	init_image(&game);
	put_background(&game, game.ceiling_colour);
	draw_map(&game);
	//color_ceiling_and_floor(&game);
	//draw_player(&game, game.player.x - SPRITE / 2, game.player.y - SPRITE / 2, SPRITE, 16777261);
	//cast_ray(&game);
	mlx_put_image_to_window(game.mlx, game.mlx_win, game.img.img, 0, 0);
	mlx_hook(game.mlx_win, 2, 0, handle_movement, &game);
	mlx_loop(game.mlx);
	print_game(&game);
}
