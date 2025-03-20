# include "cub3d.h"


// void draw_direction(t_game *game, int color)
// {
//     int line_length = 20;
//     int i;

//     int x_start = game->player.x;
//     int y_start = game->player.y;

//     for (i = 0; i < line_length; i++)
//     {
//         int dx = x_start - 5 + cos(game->player.angle) * i;
//         int dy = y_start - 5 + sin(game->player.angle) * i;
//         my_mlx_pixel_put(&game->img, dx, dy, color);
//     }
// }


// static void clear_image(t_game *game)
// {
//     int x, y;
//     for (y = 0; y < S_H; y++)
//     {
//         for (x = 0; x < S_W; x++)
//         {
//             my_mlx_pixel_put(&game->img, x, y, 0);
//         }
//     }
// }
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
}


static void rotate_player(int keycode, t_game *game)
{
    double old_dx;
    double old_plane_x;
    double rotspeed = SPEED;

    if (keycode == L_A)
        rotspeed = -0.1;

    old_dx = game->player.dx;
    game->player.dx = game->player.dx * cos(rotspeed) - game->player.dy * sin(rotspeed);
    game->player.dy = old_dx * sin(rotspeed) + game->player.dy * cos(rotspeed);

    old_plane_x = game->player.plane_x;
    game->player.plane_x = game->player.plane_x * cos(rotspeed) - game->player.plane_y * sin(rotspeed);
    game->player.plane_y = old_plane_x * sin(rotspeed) + game->player.plane_y * cos(rotspeed);
}


static void move_to_direction(t_game *game, double delta)
{
    printf("delta %f\n",delta);
// (void)delta;
    if (delta > 0.1)
        delta = 0.1;
    if (game->player.move_forward)
		move_player(game, game -> player.dx * SPEED , game -> player.dy * SPEED );
	else if (game->player.move_backward)
		move_player(game, -game -> player.dx * SPEED , -game -> player.dy * SPEED );
	else if (game->player.move_left)
		move_player(game, game -> player.dy * SPEED , -game -> player.dx * SPEED );
	else if (game->player.move_right)
		move_player(game, -game -> player.dy * SPEED , game -> player.dx * SPEED );
}


double get_time_in_ms(void)
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000.0) + (time.tv_usec / 1000.0);
}

int	handle_movement(int keycode, t_game *game)
{
    static double last_time = 0;
    double current_time = get_time_in_ms();
    double delta_time = (current_time - last_time) / 1000.0;
    last_time = current_time;

    if (keycode == EXIT)
    {
        mlx_destroy_window(game->mlx, game->mlx_win);
        //game_free(game);
        exit(0);
    }
	if (keycode == L_A || keycode == R_A)
		rotate_player(keycode, game);
    move_to_direction(game, delta_time);
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


