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


static void clear_image(t_game *game)
{
    int x, y;
    for (y = 0; y < S_H; y++)
    {
        for (x = 0; x < S_W; x++)
        {
            my_mlx_pixel_put(&game->img, x, y, 16000);
        }
    }
}

int key_press(int keycode, t_game *game)
{
    if (keycode == W)
        game->player.move_forward = 1;
    if (keycode == S)
        game->player.move_backward = 1;
    if (keycode == A)
        game->player.move_left = 1;
    if (keycode == D)
        game->player.move_right = 1;
    return (0);
}

int key_release(int keycode, t_game *game)
{
    if (keycode == W)
        game->player.move_forward = 0;
    if (keycode == S)
        game->player.move_backward = 0;
    if (keycode == A)
        game->player.move_left = 0;
    if (keycode == D)
        game->player.move_right = 0;
    return (0);
}


static void move_player(t_game *game, double dir_x, double dir_y)
{
    int new_x;
    int new_y ;
    new_x = (int)(game->player.x + dir_x);
    new_y = (int)(game->player.y + dir_y);
    if (game->map[new_y][new_x] != '1')
    {
        game->player.x += dir_x;
        game->player.y += dir_y;
    }
    else
        printf("SHIT\n");
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


static void move_to_direction(t_game *game)
{

    if (game->player.move_forward)
		move_player(game, game -> player.dx * SPEED, game -> player.dy * SPEED);
	else if (game->player.move_backward)
		move_player(game, -game -> player.dx * SPEED, -game -> player.dy * SPEED);
	else if (game->player.move_left)
		move_player(game, game -> player.dy * SPEED, -game -> player.dx * SPEED);
	else if (game->player.move_right)
		move_player(game, -game -> player.dy * SPEED, game -> player.dx * SPEED);
}
int	handle_movement(int keycode, t_game *game)
{
    clear_image(game); 
	if (keycode == L_A || keycode == R_A)
		rotate_player(keycode, game);
    move_to_direction(game);
    if (keycode == W || keycode == S || keycode == A || keycode == D)
    {
        game->player.move_forward = 0;
        game->player.move_backward = 0;
        game->player.move_left = 0;
        game->player.move_right = 0;
    }
	raycast(game);
	return (0);
}


