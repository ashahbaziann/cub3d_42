#include "cub3d.h"

static unsigned int get_pixel_color(t_image *img, int x, int y)
{
    if (x < 0 || x >= S_W || y < 0 || y >= S_H)
        return 0;
    int pixel = (y * img->line_length) + (x * (img->bpp / 8));
    return *(unsigned int *)(img->address + pixel);
}

void my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
    // if (x < 0 || y < 0 || x >= img->width || y >= img->height)
    // {
    //     return;
    // }
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
    int y;
    unsigned int color;
    int tex_x;
    t_image *img;

    img = get_dir(game, &game->ray);
    tex_x = (int)(ray->wall_x * img->width);

    y = ray->draw_start;
    while (y < ray->draw_end)
    {
        int tex_y = (int)((y - ray->draw_start) * img->height / ray->line_height);
        color = get_pixel_color(img, tex_x, tex_y);
        my_mlx_pixel_put(&game->img, x, y, color);
        y++;
    }
}

void draw_ceiling_and_floor(t_game *game,int x, t_ray *ray)
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