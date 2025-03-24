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




static void	init_image(t_game *game)
{

	game -> img.img = mlx_new_image(game -> mlx, S_W, S_H);
	game -> img.address = mlx_get_data_addr(game -> img.img, &game -> img.bpp, &game -> img.line_length, &game -> img.endian);
	game -> img.width = S_W;
	game -> img.height = S_H;
	printf("Image width: %d, height: %d\n", game->img.width, game->img.height);
	printf("Game width: %d, height: %d\n", S_W, S_H);

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

void draw_line(t_game *game, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(i < size && i  < 2)
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
	//put_background(game, game -> ceiling_colour);
	while (i < S_H / SPRITE)
	{
		j = 0;
		while (j < S_W / SPRITE)
		{
			//if (game -> map[i][j] == '1')
				draw_square(game, j * SPRITE , i * SPRITE , SPRITE, 0);
			// else
			// 	draw_square(game, j * SPRITE , i * SPRITE , SPRITE - 2, 16777215);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, 0, 0);
	mlx_clear_window(game->mlx, game->mlx_win);
}

static void open_path(t_game *game, char **direction)
{
	if (access(*direction, F_OK) != -1)
	printf("%s\n",*direction);
	game->north.image.img = mlx_xpm_file_to_image(game->mlx,*direction,&game->north.image.width,&game->north.image.height);
	if (game->north.image.img == NULL)
    {
        printf("Error: Failed to load texture: %s\n", *direction);
        exit(1);
    }
	game->north.image.address = mlx_get_data_addr(game->north.image.img,&game->north.image.bpp,&game->north.image.line_length,&game->north.image.endian);
	// game->south.image.img = mlx_xpm_file_to_image(game->mlx,*direction,&game->north.image.width,&game->north.image.height);
	// game->west.image.img = mlx_xpm_file_to_image(game->mlx,*direction,&game->north.image.width,&game->north.image.height);
	// game->east.image.img = mlx_xpm_file_to_image(game->mlx,*direction,&game->north.image.width,&game->north.image.height);
	// game->south.image.address = mlx_get_data_addr(&game->north.image.img,&game->north.image.bpp,&game->north.image.line_length,&game->north.image.endian);
	// game->west.image.address = mlx_get_data_addr(&game->north.image.img,&game->north.image.bpp,&game->north.image.line_length,&game->north.image.endian);
	// game->east.image.address = mlx_get_data_addr(&game->north.image.img,&game->north.image.bpp,&game->north.image.line_length,&game->north.image.endian);
}
int main(int argc, char **argv)
{
	t_game	game;
	int		fd;

	if ((fd = validate_args(argc, argv)) == -1)
		return (1);
	init_game(&game, fd);
	validate_textures(&game);
	map_parsing(&game);
	init_window(&game);
	init_image(&game);
	open_path(&game,&game.north.path);
	mlx_hook(game.mlx_win, 2, 1L << 0, key_press, &game);
    mlx_hook(game.mlx_win, 3, 1L << 1, key_release, &game);
	mlx_loop_hook(game.mlx, update, &game);
	mlx_loop(game.mlx);
	print_game(&game);
	clean(&game,NULL,NULL);
}
