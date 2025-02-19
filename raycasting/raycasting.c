#include "cub3d.h"

void put_pixel(t_game *game, int x, int y, int color)
{
	// printf("x = _%d_\n", x);
	// printf("y = _%d_\n", y);
	// printf("game->width = _%d_\n", game->width);
	// printf("game->height = _%d_\n", game->height);

    if (x >= 0 && x < game->width && y >= 0 && y < game->height) // Проверяем, что координаты находятся в пределах экрана
    {
		//printf("\nya ustal\n");
        mlx_pixel_put(game->mlx, game -> mlx_win, x, y, color); // Рисуем пиксель с помощью mlx_pixel_put
    }
}
// int get_wall_color(double *distance)
// {
//     int color;

//     // Нормализуем расстояние (если нужно, можно подстроить это)
//     double normalized_distance = *distance / MAX_DISTANCE;

//     // Чем дальше, тем темнее
//     int brightness = (int)(255 - (normalized_distance * 255));

//     // Возвращаем цвет с измененной яркостью
//     color = (brightness << 16) | (brightness << 8) | brightness; // RGB (грейскейл)

//     return color;
// }

static void render_walls(t_game *game, double *distance, int i)
{
	int wall_height;
	int wall_top;
	int wall_bottom;
	int color;
	int y;

	wall_height =(int)(game->height / ((int)distance + 1));
	wall_top = (game->height/2) - (wall_height / 2);
	wall_bottom = (game->height / 2) + (wall_height / 2);
	if (wall_top < 0)
		wall_top = 0;
	if (wall_bottom >= game->height)
		wall_bottom = game->height - 1;
	color = 0x800080;
	y = wall_top;

	// printf("y = _%d_\n", y);
	// printf("wall_top = _%d_\n", wall_top);
	while(y <= wall_bottom)
	{
		//printf("y = _%d_\n", y);
		put_pixel(game, i, y, color);
		y++;
		//printf("y = _%d_\n", y);
	}

}

static double cast_single_ray(t_game *game, double ray_angle)
{
	double step_x;
	double step_y;
	double distance;
	int grid_x;
	int grid_y;
	double x;
	double y;

	distance = 0.0;
	step_x = cos(ray_angle);
	step_y = sin(ray_angle);
	x = game->player.x;
	y = game->player.y;
	grid_x = (int)x;
	grid_y = (int)y;
	while(1)
	{
		x += step_x;
		y += step_y;
		grid_x = (int)x / 50;
		grid_y = (int)y / 50;
		if(game->map[grid_y][grid_x] == '1')
		{
			 distance = sqrt((x - game->player.x) * (x - game->player.x) + (y - game->player.y) * (y - game->player.y));
			 break;
		}
	}
	return distance;

}

void cast_ray(t_game *game)
{
	int i;
	double ray_angle;
	double distance_to_wall;

	i = 0;
	ray_angle = 0;
	while(i < NUM_RAYS)
	{
		ray_angle = game->player.angle - (FOV / 2) + (i * FOV / NUM_RAYS);
		distance_to_wall = cast_single_ray(game, ray_angle);
		render_walls(game, &distance_to_wall, i);
		i++;
	}
}
