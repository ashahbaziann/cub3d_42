# include "cub3d.h"


// static void	clear_current_position(t_game *game)
// {
// 	int	x;
// 	int	y;

// 	x = (int)(game->player.x / SPRITE);
// 	y = (int)(game->player.y / SPRITE);
// 	game -> map[y][x] = '0';
// 	draw_square(game, game->player.x - SPRITE / 2, game->player.y- SPRITE / 2, 15, 16777215);
// 	draw_direction(game,16777215);
// }

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
	// draw_map(game);
	// mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, 0, 0);
}

int	handle_movement(int keycode, t_game *game)
{
		//if (keycode == EXIT) HANDLE
	if (keycode == W)
		move_player(game, game -> player.dx, game -> player.dy);
	else if (keycode == S)
		move_player(game, -game -> player.dx, -game -> player.dy);
	else if (keycode == A)
	{
		// if (game -> player.dx == 0)
		// {

		// 	game -> player.dx++;
		// }
		move_player(game, -1, 0);
	}
	else if (keycode == D)
	{
		// if (game -> player.dx == (double)0)
		// {
		// 	game -> player.dx++;

		// }
		move_player(game, 1, 0);
	}
	else if (keycode == L_A || keycode == R_A)
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
		mlx_clear_window(game->mlx, game->mlx_win);
		draw_map(game);
		mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, 0, 0);
	return (0);
}
