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
    int new_x = (int)(game->player.x + dir_x);
    int new_y = (int)(game->player.y + dir_y);

    // Check for wall collision before updating position
    if (game->map[new_y][new_x] != '1')
    {
        game->player.x += dir_x;
        game->player.y += dir_y;
    }
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

void calculate_step_and_side_dist(t_game *game, t_ray *ray, double camera_x)
{
    ray->dir_x = game->player.dx + game->player.plane_x * camera_x;
    ray->dir_y = game->player.dy + game->player.plane_y * camera_x;

    ray->map_x = (int)(game->player.x);
    ray->map_y = (int)(game->player.y);

    ray->delta_x = fabs(1 / ray->dir_x);
    ray->delta_y = fabs(1 / ray->dir_y);

    if (ray->dir_x < 0)
    {
        ray->step_x = -1;
        ray->side_x = (game->player.x - ray->map_x) * ray->delta_x;
    }
    else
    {
        ray->step_x = 1;
        ray->side_x = (ray->map_x + 1.0 - game->player.x) * ray->delta_x;
    }

    if (ray->dir_y < 0)
    {
        ray->step_y = -1;
        ray->side_y = (game->player.y - ray->map_y) * ray->delta_y;
    }
    else
    {
        ray->step_y = 1;
        ray->side_y = (ray->map_y + 1.0 - game->player.y) * ray->delta_y;
    }
}

void perform_dda(t_game *game, t_ray *ray)
{
    ray->hit = 0;
    while (!ray->hit)
    {
        if (ray->side_x < ray->side_y)
        {
            ray->side_x += ray->delta_x;
            ray->map_x += ray->step_x;
            ray->side = 0;
        }
        else
        {
            ray->side_y += ray->delta_y;
            ray->map_y += ray->step_y;
            ray->side = 1;
        }
        if (ray->map_y < 0.25//idk the point
			|| ray->map_x < 0.25
			|| ray->map_y > game->height - 0.25
			|| ray->map_x > game->width - 1.25)
			break ;
        if (game ->map[ray->map_y][ray->map_x] == '1' )
		{
			//printf("map Y %d, map X %d\n",ray->map_y /SPRITE, ray->map_x/SPRITE);
            ray->hit = 1;
		}
    }
}

void calculate_wall_distance(t_game *game,t_ray *ray)
{
   // double wall_dist;
    if (ray->side == 0)
	{
       ray->wall_dist = (ray->map_x - game->player.x + (1 - ray->step_x) / 2) / ray->dir_x;
	}
    else
        ray->wall_dist = (ray->map_y - game->player.y + (1 - ray->step_y) / 2) / ray->dir_y;
}


void draw_wall(t_game *game, int x,t_ray *ray)
{
    ray->line_height = (int)(S_H/ ray->wall_dist);
		//printf("wall_dist %f, line %d\n",wall_dist, line_height);
    ray->draw_start = (-ray->line_height / 2 + S_H/ 2);
    if (ray->draw_start < 0)
		ray->draw_start = 0;
    ray->draw_end =( ray->line_height / 2 + S_H/ 2);
    if (ray->draw_end >= S_H)
		ray->draw_end = S_H/SPRITE - 1 * SPRITE;
    if (ray->side == 0)
		ray->wall_x = game->player.y + ray->wall_dist * ray->dir_y;
	else
		ray->wall_x = game->player.x + ray->wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
    int color = 0xFFFFFF;
	//printf("start %d, end %d\n", ray->draw_start,ray->draw_end);
    for (int y = ray->draw_start; y < ray->draw_end; y++)
	{
		//printf("x = %d, y = %d\n",x ,y);
        my_mlx_pixel_put(&game->img, x, y, color);
	}
   /// mlx_clear_window(game->mlx, game->mlx_win);
}


void raycast(t_game *game)
{
    int x;

    x = 0;
    while (x < S_W)
    {
		double camera_x = 2 * x / (double)(S_W - 1) - 1;

        calculate_step_and_side_dist(game, &game ->ray, camera_x);
        perform_dda(game, &game ->ray);

        calculate_wall_distance(game, &game ->ray);
        draw_wall(game, x, &game ->ray);
        x++;
    }
    mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, 0, 0);
   
}


static void move_to_direction(t_game *game)
{
    if (game->player.move_forward)
		move_player(game, game -> player.dx * SPEED, game -> player.dy * SPEED);
	else if (game->player.move_backward)
		move_player(game, -game -> player.dx * SPEED, -game -> player.dy * SPEED);
	else if (game->player.move_left)
		move_player(game, -game -> player.dy * SPEED, game -> player.dx * SPEED);
	else if (game->player.move_right)
		move_player(game, game -> player.dy * SPEED, -game -> player.dx * SPEED);
}
int	handle_movement(int keycode, t_game *game)
{
   clear_image(game); 
    ///mlx_clear_window(game->mlx, game->mlx_win);
	//raycast(game);
	if (keycode == L_A || keycode == R_A)
		rotate_player(keycode, game);
    move_to_direction(game);
	//mlx_clear_window(game->mlx, game->mlx_win);
	//draw_map(game);
	raycast(game);
   // mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, 0, 0);
   // mlx_clear_window(game->mlx, game->mlx_win);
	return (0);
}


