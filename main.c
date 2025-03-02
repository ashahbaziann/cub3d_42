/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:50:42 by ashahbaz          #+#    #+#             */
/*   Updated: 2025/02/20 18:15:08 by gmelikya         ###   ########.fr       */
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
	//printf("first line %d\n",img -> width);
	// while (y > img->height)
	// 	y -= img->height;
	// while (x > img -> width)
	// 	x -= img -> width;
	// printf("!!!!!!!\n");
	// printf("x == _%d_\n", x);
	// printf("y == _%d_\n", y);
	// printf("img->width == _%d_\n", img->width);
	// printf("img->height == _%d_\n", img->height);
    if (x < 0 || y < 0 || x >= img->width || y >= img->height)
    {
        //printf("Skipping pixel (%d, %d) - Out of bounds\n", x, y);
        return;  // Prevent writing outside the image buffer
    }

    char *dst = img->address + (y * img->line_length + x * (img->bpp / 8));
    *(unsigned int *)dst = color;

    //printf("Placing pixel at (%d, %d) with color %d\n", x, y, color);
}



// void my_mlx_pixel_put(t_image *img, int x, int y, int color)
// {
//     char    *dst;

//     dst = img->address + (y * img->line_length + x * (img->bpp / 8));
//     *(unsigned int*)dst = color;
// }



static void color_ceiling_and_floor(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < game -> img.height)
	{
		j = 0;
		while (j < game ->img.width)
		{
			my_mlx_pixel_put(&game->img, j, i, game -> ceiling_colour);
			j++;
		}
		i++;
	}
	// while (i < game -> img.height)
	// {
	// 	j = 0;
	// 	while (j < game ->img.width)
	// 	{
	// 		my_mlx_pixel_put(&game -> img, j, i, game -> floor_colour);
	// 		j++;
	// 	}
	// 	i++;
	// }
}

	static void	init_image(t_game *game)
{

	game -> img.img = mlx_new_image(game -> mlx, S_W, S_H);
	game -> img.address = mlx_get_data_addr(game -> img.img, &game -> img.bpp, &game -> img.line_length, &game -> img.endian);
	game -> img.width = S_W;
	game -> img.height = S_H;
	printf("Image width: %d, height: %d\n", game->img.width, game->img.height);
	printf("Game width: %d, height: %d\n", S_W, S_H);

}

void draw_player(t_game *game, int x, int y, int size, int color)
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
	color_ceiling_and_floor(&game);
	draw_player(&game, game.player.x - SPRITE / 2, game.player.y - SPRITE / 2, SPRITE, 16777261);
	//cast_ray(&game);
	mlx_put_image_to_window(game.mlx, game.mlx_win, game.img.img, 0, 0);
	mlx_hook(game.mlx_win, 2, 0, handle_movement, &game);
	mlx_loop(game.mlx);
	print_game(&game);
}
