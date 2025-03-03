# include "cub3d.h"
static void	clear_current_position(t_game *game)
{
	int	x;
	int	y;

	x = (int)(game->player.x / SPRITE);
	y = (int)(game->player.y / SPRITE);
	game -> map[y][x] = '0';
	draw_square(game, game->player.x- SPRITE / 2, game->player.y- SPRITE / 2, SPRITE - 1, 16777215);
}

static void move_player(t_game *game, int dir_x, int dir_y)
{
	int new_x = (int)((game->player.x + dir_x * SPRITE) / SPRITE);
	int new_y = (int)((game->player.y + dir_y * SPRITE) / SPRITE);

	if (game->map[new_y][new_x] == '1')
	    return ;
	clear_current_position(game);
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
