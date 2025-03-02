# include "cub3d.h"
// static void	clear_current_position(t_game *game)
// {
// 	game -> map[(int)((game ->player.x) - SPRITE/2)/SPRITE ][(int)((game ->player.y) - SPRITE/2)/SPRITE ] = '0';
// 	draw_player(game, game->player.x- SPRITE / 2, game->player.y- SPRITE / 2, SPRITE,166661);
// }



static void move_player(t_game *game, int dir_x, int dir_y)
{
	// if (game -> map[(int)(((game ->player.y) - SPRITE/2)/SPRITE  + dir_y)][(int)(((game ->player.x) - SPRITE/2)/SPRITE  + dir_x)] == '1')
	// 	return ;
	int new_x = (int)((game->player.x + dir_x * SPRITE) / SPRITE);
	int new_y = (int)((game->player.y + dir_y * SPRITE) / SPRITE);

	printf("x = %d, y = %d\n",new_x, new_y);
	if (new_y <= 0 || new_x >= S_W/ SPRITE || new_x <= 0 || new_y >= S_H/SPRITE)
    	return ;
	// if (game->map[new_x][new_y] == '1')
	//     printf("what\n");
	//clear_current_position(game);
	game -> player.x += dir_x * SPRITE;
	game -> player.y += dir_y * SPRITE;
	draw_player(game, game -> player.x - SPRITE / 2, game -> player.y - SPRITE / 2, SPRITE, 16777261);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, 0, 0);
}

int	handle_movement(int keycode, t_game *game)
{
	//if (keycode == EXIT) HANDLE
	if (keycode == W)
		move_player(game, 0, -1);
	else if (keycode == S)
		move_player(game, 0, 1);
	else if (keycode == A)
		move_player(game, -1, 0);
	else if (keycode == D)
		move_player(game, 1, 0);
	return (0);
}
