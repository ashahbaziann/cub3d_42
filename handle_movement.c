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
        if (game ->map[ray->map_y][ray->map_x] == '1')
		{
			printf("map Y %d, map X %d\n",ray->map_y /SPRITE, ray->map_x/SPRITE);
            ray->hit = 1;
		}
    }
}

double calculate_wall_distance(t_game *game,t_ray *ray)
{
    double wall_dist;
    if (ray->side == 0)
	{
        wall_dist = (ray->map_x - game->player.x + (1 - ray->step_x) / 2) / ray->dir_x;
	}
    else
        wall_dist = (ray->map_y - game->player.y + (1 - ray->step_y) / 2) / ray->dir_y;
    return wall_dist;
}


void draw_wall(t_game *game, int x, double wall_dist)
{
    int line_height = (int)(game->height * SPRITE/ wall_dist);
		printf("wall_dist %f, line %d\n",wall_dist, line_height);
    int draw_start = (-line_height / 2 + game->height * SPRITE/ 2);
    if (draw_start < 0)
		draw_start = 0;
    int draw_end =( line_height / 2 + game->height * SPRITE/ 2);
    if (draw_end >= game->height * SPRITE)
		draw_end = (game->height - 1) * SPRITE;
    int color = 0xFFFFFF;
	printf("start %d, end %d\n", draw_start,draw_end);
    for (int y = draw_start; y < draw_end; y++)
	{
		printf("x = %d, y = %d\n",x ,y);
        my_mlx_pixel_put(&game->img, x, y, color);
	}
}


void raycast(t_game *game)
{
    for (int x = 0; x < game -> width * SPRITE; x++)
    {
        //double camera_x = 2 * x / (double)(game->width - 1) * SPRITE;
		double camera_x = 2 * x / (double)(game->width * SPRITE - 1) - 1;

        calculate_step_and_side_dist(game, &game ->ray, camera_x);
        perform_dda(game, &game ->ray);

        double wall_dist = calculate_wall_distance(game, &game ->ray);
        draw_wall(game, x, wall_dist);
    }
}
int	handle_movement(int keycode, t_game *game)
{
	//if (keycode == EXIT) HANDLE
	(void)keycode;
	raycast(game);
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
	raycast(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, 0, 0);
	return (0);
}


