#include "cub3d.h"

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
    if (keycode == EXIT)
        game->player.exit = 1;
    if (keycode == L_A)
        game->player.rot_left = 1;
    if (keycode == R_A)
        game->player.rot_right = 1;
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
    if (keycode == EXIT)
        game->player.exit = 0;
    if (keycode == L_A)
        game->player.rot_left = 0;
    if (keycode == R_A)
        game->player.rot_right = 0;
    return (0);
}