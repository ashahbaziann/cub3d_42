// #include "cub3d.h"

// // void put_pixel(t_image *img, int x, int y, int color)
// // {
// // 	printf("x = _%d_\n", x);
// // 	printf("y = _%d_\n", y);
// // 	printf("S_W = _%d_\n", S_W);
// // 	printf("S_H = _%d_\n", S_H);

// //     if (x >= 0 && x < S_W && y >= 0 && y < S_H) // Проверяем, что координаты находятся в пределах экрана
// //     {
// // 		printf("\nya ustal\n");
// //         mlx_pixel_put(game->mlx, game -> mlx_win, x*50, y*50, color); // Рисуем пиксель с помощью mlx_pixel_put
// //     }
// // }


// // int get_wall_color(double *distance)
// // {
// //     int color;

// //     // Нормализуем расстояние (если нужно, можно подстроить это)
// //     double normalized_distance = *distance / MAX_DISTANCE;

// //     // Чем дальше, тем темнее
// //     int brightness = (int)(255 - (normalized_distance * 255));

// //     // Возвращаем цвет с измененной яркостью
// //     color = (brightness << 16) | (brightness << 8) | brightness; // RGB (грейскейл)

// //     return color;
// // }

// static void render_walls(t_game *game, double distance, int i)
// {
// 	int wall_height;
// 	int wall_top;
// 	int wall_bottom;
// 	int color;
// 	int y = 0;


// 	//printf("distance == _%f_\n", distance);
// 	wall_height =(int)((game -> height * SPRITE / ((int)distance)));
// 	wall_top = ((game -> height / 2) - (wall_height / 2)) * SPRITE;
// 	wall_bottom = ( (game -> height / 2) + (wall_height / 2)) * SPRITE;
// 	if (wall_top < 0)
// 		wall_top = 0;
// 	if (wall_bottom >= game -> height * SPRITE)
// 		wall_bottom = (game -> height - 1) * SPRITE;

// 	color = 0x800080;
// 	y = wall_top;
// 	while(y <= wall_bottom)
// 	{
// 		// printf("y = %d\n", y);
// 		// printf("x = %d\n", i);
// 		my_mlx_pixel_put(&game->img, i, y, color);
// 		y++;
// 	}
// }

// static double cast_single_ray(t_game *game, double ray_angle)
// {
// 	double step_x;
// 	double step_y;
// 	double distance;
// 	int grid_x;
// 	int grid_y;
// 	double x;
// 	double y;

// 	distance = 0.0;
// 	step_x = cos(ray_angle);
// 	step_y = sin(ray_angle);
// 	x = game->player.x;
// 	//printf("x -==== %f\n",x/50);
// 	y = game->player.y;
// 	//printf("y -==== %f\n",y/50);
// 	grid_x = (int)x;
// 	grid_y = (int)y;
// 	while(1)
// 	{
// 		x += step_x;
// 		y += step_y;
// 		grid_x = (int)x / 50;
// 		grid_y = (int)y / 50;
// 		if(game->map[grid_y][grid_x] == '1')
// 		{
// 			// distance = sqrt(pow(x - game->player.x, 2)) + pow(y - game->player.y, 2);
// 			 distance = sqrt((x - game->player.x) * (x - game->player.x) + (y - game->player.y) * (y - game->player.y));
// 			 break;
// 		}
// 	}
// 	return distance;

// }

// void cast_ray(t_game *game)
// {
// 	(void)game;
// 	// int i;
// 	// double ray_angle;
// 	// double distance_to_wall;

// 	// i = 0;
// 	// ray_angle = 0;
// 	// ray_angle = (game->player.angle * M_PI / 180.0) + 0.017 * (FOV);
// 	// while(i < 240)
// 	// {
// 	// 	printf("ray_angle == _%f_\n", ray_angle);
// 	// 	distance_to_wall = cast_single_ray(game, ray_angle);
// 	// 	render_walls(game, distance_to_wall, i);
// 	// 	ray_angle += 0.00218;
// 	// 	i++;
// 	// }
// 	//printf("i = _%d_\n", i);
// }
