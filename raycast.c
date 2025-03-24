#include "cub3d.h"


static void init_ray(t_game *game, t_ray *ray, double camera_x)
{
    ray->dir_x = game->player.dx + game->player.plane_x * camera_x;
    ray->dir_y = game->player.dy + game->player.plane_y * camera_x;

    ray->map_x = (int)(game->player.x);
    ray->map_y = (int)(game->player.y);

    ray->delta_x = fabs(1 / ray->dir_x);
    ray->delta_y = fabs(1 / ray->dir_y);   
}


void calculate_step(t_game *game, t_ray *ray)
{
    if (ray->dir_x < 0)
    {
        ray->step_x = -1;
        ray->side_x = (game->player.x - ray->map_x) * ray->delta_x;
    }
    else
    {
        ray->step_x = 1;
        ray->side_x = (ray->map_x + 1 - game->player.x) * ray->delta_x;
    }

    if (ray->dir_y < 0)
    {
        ray->step_y = -1;
        ray->side_y = (game->player.y - ray->map_y) * ray->delta_y;
    }
    else
    {
        ray->step_y = 1;
        ray->side_y = (ray->map_y + 1 - game->player.y) * ray->delta_y;
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
        if (ray->map_y < 0.25
			|| ray->map_x < 0.25
			|| ray->map_y > game->height - 0.25
			|| ray->map_x > game->width - 1.25)
			break ;
        if (game ->map[ray->map_y][ray->map_x] == '1' )
            ray->hit = 1;
    }
}


static void calculate_wall_height(t_game *game, t_ray *ray)
{
    if (ray->side == 0)
       ray->wall_dist = (ray->map_x - game->player.x + (1 - ray->step_x) / 2) / ray->dir_x;
    else
        ray->wall_dist = (ray->map_y - game->player.y + (1 - ray->step_y) / 2) / ray->dir_y;
    ray->line_height = (int)(S_H/ ray->wall_dist);
    ray->draw_start = (-ray->line_height / 2 + S_H/ 2);
    if (ray->draw_start < 0)
        ray->draw_start = 0;
    ray->draw_end =(ray->line_height / 2 + S_H/ 2);
    if (ray->draw_end >= S_H)
        ray->draw_end = S_H - 1;
    if (ray->side == 0)
		ray->wall_x = game->player.y + ray->wall_dist * ray->dir_y;
	else
		ray->wall_x = game->player.x + ray->wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
}
unsigned int get_pixel_color(t_image *img, int x, int y)
{
    if (x < 0 || x >= S_W || y < 0 || y >= S_H)
        return 0;
    int pixel = (y * img->line_length) + (x * (img->bpp / 8));
    return *(unsigned int *)(img->address + pixel);
}


void draw_wall(t_game *game, int x, t_ray *ray)
{
    int y;
    unsigned int color;
    int tex_x;

    tex_x = (int)(ray->wall_x * game->north.image.width);

    y = ray->draw_start;
    while (y < ray->draw_end)
    {
        int tex_y = (int)((y - ray->draw_start) * game->north.image.height / ray->line_height);
        color = get_pixel_color(&game->north.image, tex_x, tex_y);
        my_mlx_pixel_put(&game->img, x, y, color);
        y++;
    }
}


static void draw_ceiling_and_floor(t_game *game,int x, t_ray *ray)
{

    int i;

    i = 0;
    while (i < ray->draw_start)
    {
        my_mlx_pixel_put(&game->img, x, i, game->ceiling_colour);
        i++;
    }
    i = ray->draw_end;
    while(i < S_H)
    {
        my_mlx_pixel_put(&game->img, x, i, game->floor_colour);
        i++;
    }
}


void raycast(t_game *game)
{
    int x;

    x = 0;
    mlx_destroy_image(game->mlx, game->img.img);
    game->img.img = mlx_new_image(game->mlx, S_W, S_H); 
    game->img.address = mlx_get_data_addr(game->img.img, &game->img.bpp,&game->img.line_length, &game->img.endian);
    while (x < S_W)
    {
        double camera_x = 2 * x / (double)(S_W - 1) - 1;
        init_ray(game, &game->ray, camera_x);
        calculate_step(game, &game ->ray);
        perform_dda(game, &game ->ray);
        calculate_wall_height(game, &game->ray);
        draw_wall(game, x, &game ->ray);
        draw_ceiling_and_floor(game, x, &game->ray);
        x++;
    }
    mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, 0, 0);
}