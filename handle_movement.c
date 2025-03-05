# include "cub3d.h"


void draw_direction(t_game *game, int color)
{
    int line_length = 20;
    int i;

    int x_start = game->player.x;
    int y_start = game->player.y;

    for (i = 0; i < line_length; i++)
    {
        int dx = x_start - 5 + cos(game->player.angle) * i;
        int dy = y_start - 5 + sin(game->player.angle) * i;
        my_mlx_pixel_put(&game->img, dx, dy, color);
    }
}

static void move_player(t_game *game, double dir_x, double dir_y)
{
	int new_x = (int)((game->player.x + dir_x * SPRITE) / SPRITE);
	int new_y = (int)((game->player.y + dir_y * SPRITE) / SPRITE);

	if (game->map[new_y][new_x] == '1')
	    return ;
	game -> player.x += dir_x * SPRITE;
	game -> player.y += dir_y * SPRITE;
}
static void rotate_player(int keycode, t_game *game)
{
	if (keycode == L_A)
		{
			game->player.angle -= 0.1;
			if (game->player.angle < 0)
				game->player.angle += 2 * M_PI;
		}
		else
		{
			game->player.angle += 0.1;
			if (game->player.angle > 2 * M_PI)
				game->player.angle -= 2 * M_PI;
		}
		game -> player.dx = cos(game -> player.angle);
		game -> player.dy = sin(game -> player.angle);
}
int	handle_movement(int keycode, t_game *game)
{
		//if (keycode == EXIT) HANDLE
	if (keycode == W)
		move_player(game, game -> player.dx * 0.5, game -> player.dy * 0.5);
	else if (keycode == S)
		move_player(game, -game -> player.dx * 0.5, -game -> player.dy * 0.5);
	else if (keycode == A)
		move_player(game, -0.5, 0);
	else if (keycode == D)
		move_player(game, 0.5, 0);
	else if (keycode == L_A || keycode == R_A)
		rotate_player(keycode, game);
	mlx_clear_window(game->mlx, game->mlx_win);
	draw_map(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, 0, 0);
	return (0);
}
