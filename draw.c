#include "cub3d.h"

// static unsigned int get_pixel_color(t_image *img, int x, int y)
// {
//     // if (x < 0.25 || x >= S_W - 1.25 || y < 0.25 || y >= S_H - 0.25)
//     //     return 0;
//     int pixel = (y * img->line_length) + (x * (img->bpp / 8));
//     return *(unsigned int *)(img->address + pixel);
// }

// void my_mlx_pixel_put(t_image *img, int x, int y, int color)
// {
//     if (x < 0.25 || x >= S_W - 1.25 || y < 0.25 || y >= S_H - 0.25)
//         return ;
//     char *dst = img->address + (y * img->line_length + x * (img->bpp / 8));
//     *(unsigned int *)dst = color;
// }


static unsigned int get_pixel_color(t_image *img, int x, int y)
{
    if (x < 0 || x >= img->width || y < 0 || y >= img->height)
        return 0;
    int pixel = (y * img->line_length) + (x * (img->bpp / 8));
    return *(unsigned int *)(img->address + pixel);
}

void my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
    if (x < 0 || x >= S_W || y < 0 || y >= S_H)
        return;
    char *dst = img->address + (y * img->line_length + x * (img->bpp / 8));
    *(unsigned int *)dst = color;
}

static t_image *get_dir(t_game *game, t_ray *ray)
{
    t_image *img;

    img = NULL;
    if (ray->side == 0)
    {
        if (ray->dir_x > 0)
            img = &game->east.image;
        else
            img = &game->west.image;
    }
    else
    {
        if (ray->dir_y > 0)
            img = &game->south.image;
        else
            img = &game->north.image;
    }
    return(img);
}

void draw_wall(t_game *game, int x, t_ray *ray)
{
    t_image *img;
    int y;
    unsigned int color;

    img = get_dir(game, ray);
    y = ray->draw_start;
    game->tex.x = (int)(ray->wall_x * img->width);
    if ((ray->side == 0 && ray->dir_x > 0) || (ray->side == 1 && ray->dir_y > 0))
        game->tex.x = img->width - game->tex.x - 1;
    game->tex.step = 1.0 * img->height / ray->line_height;
    game->tex.pos = (ray->draw_start - (S_H / 2) + (ray->line_height / 2)) * game->tex.step;
    if (game->tex.pos < 0)
        game->tex.pos = 0;
    while (y < ray->draw_end)
    {
        //game->tex.y = (int)game->tex.pos;
        game->tex.y = (int)floor(game->tex.pos);

        if (game->tex.y >= img->height)
            game->tex.y = img->height - 1;
        color = get_pixel_color(img, game->tex.x, game->tex.y);
        my_mlx_pixel_put(&game->img, x, y, color);
        game->tex.pos += game->tex.step;
        y++;
    }
}


void draw_ceiling_and_floor(t_game *game, int x, t_ray *ray)
{
    for (int i = 0; i < ray->draw_start; i++)
        *(unsigned int *)(game->img.address + (i * game->img.line_length) + (x * (game->img.bpp / 8))) = game->ceiling_colour;
    for (int i = ray->draw_end; i < S_H; i++)
        *(unsigned int *)(game->img.address + (i * game->img.line_length) + (x * (game->img.bpp / 8))) = game->floor_colour;
}

// void draw_ceiling_and_floor(t_game *game,int x, t_ray *ray)
// {
//     int i;

//     i = 0;
//     while (i < ray->draw_start)
//     {
//         my_mlx_pixel_put(&game->img, x, i, game->ceiling_colour);
//         i++;
//     }
//     i = ray->draw_end;
//     while(i < S_H)
//     {
//         my_mlx_pixel_put(&game->img, x, i, game->floor_colour);
//         i++;
//     }
// }