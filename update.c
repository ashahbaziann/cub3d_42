/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 17:05:39 by ashahbaz          #+#    #+#             */
/*   Updated: 2025/03/30 17:56:09 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_player(t_game *game, double dir_x, double dir_y)
{
	double	n_x;
	double	n_y;
	double	buffer;

	n_x = game->player.x + dir_x;
	n_y = game->player.y + dir_y;
	buffer = 0.2;
	if (n_x < 0.25 || n_x >= S_W - 1.25 || n_y < 0.25 || n_y >= S_H - 0.25)
		return ;
	if (game->map[(int)(game->player.y)][(int)(n_x + buffer)] != '1'
		&& game->map[(int)(game->player.y)][(int)(n_x - buffer)] != '1')
		game->player.x += dir_x;
	if (game->map[(int)(n_y + buffer)][(int)(game->player.x)] != '1'
		&& game->map[(int)(n_y - buffer)][(int)(game->player.x)] != '1')
		game->player.y += dir_y;
}

static void	rotate_player(t_game *game)
{
	double		old_dx;
	double		old_plane_x;
	double		speed;
	t_player	*player;

	speed = 0.1;
	player = &game->player;
	if (player->rot_left)
		speed *= -1;
	old_dx = player->dx;
	player->dx = player->dx * cos(speed) - player->dy * sin(speed);
	player->dy = old_dx * sin(speed) + player->dy * cos(speed);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(speed) - player->plane_y
		* sin(speed);
	player->plane_y = old_plane_x * sin(speed) + player->plane_y * cos(speed);
}

static void	move_to_direction(t_game *game)
{
	if (game->player.move_forward)
		move_player(game, game->player.dx * SPEED, game->player.dy * SPEED);
	else if (game->player.move_backward)
		move_player(game, -game->player.dx * SPEED, -game->player.dy * SPEED);
	else if (game->player.move_left)
		move_player(game, game->player.dy * SPEED, -game->player.dx * SPEED);
	else if (game->player.move_right)
		move_player(game, -game->player.dy * SPEED, game->player.dx * SPEED);
}

int	update(t_game *game)
{
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
