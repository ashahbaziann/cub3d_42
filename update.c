# include "cub3d.h"

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


static void rotate_player(t_game *game)
{
   //(void)delta;
    double old_dx;
    double old_plane_x; 
    double rotspeed = 0.1;
            
    if (game ->player.rot_left)
        rotspeed *= -1;

    old_dx = game->player.dx;
    game->player.dx = game->player.dx * cos(rotspeed) - game->player.dy * sin(rotspeed);
    game->player.dy = old_dx * sin(rotspeed) + game->player.dy * cos(rotspeed);

    old_plane_x = game->player.plane_x;
    game->player.plane_x = game->player.plane_x * cos(rotspeed) - game->player.plane_y * sin(rotspeed);
    game->player.plane_y = old_plane_x * sin(rotspeed) + game->player.plane_y * cos(rotspeed);
}


static void move_to_direction(t_game *game)
{
    //(void)delta;
    if (game->player.move_forward)
		move_player(game, game -> player.dx * SPEED , game -> player.dy * SPEED);
	else if (game->player.move_backward)
		move_player(game, -game -> player.dx * SPEED , -game -> player.dy * SPEED);
	else if (game->player.move_left)
		move_player(game, game -> player.dy * SPEED , -game -> player.dx * SPEED);
	else if (game->player.move_right)
		move_player(game, -game -> player.dy * SPEED , game -> player.dx * SPEED);
}


// double get_time_in_ms(void)
// {
//     struct timeval time;
//     gettimeofday(&time, NULL);
//     return (time.tv_sec * 1000.0) + (time.tv_usec / 1000.0);
// }
int update(t_game *game)
{
	// static double last_time;
    // double current_time = get_time_in_ms();
    // double delta_time = (current_time - last_time) / 1000.0;
    // last_time = current_time;
    if (game->player.exit)
    {
        clean(game, NULL, NULL);
        exit(0);
    }
	if (game->player.rot_left || game->player.rot_right)
		rotate_player(game);
    move_to_direction(game);
	raycast(game);
	return (0);
}
