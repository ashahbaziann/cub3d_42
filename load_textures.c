#include "cub3d.h"

void load_textures(t_game *game)
{
	t_image *no;
	t_image *so;
	t_image *we;
	t_image *ea;

	no = &game->north.image;
	so = &game->south.image;
	we = &game->west.image;
	ea = &game->east.image;
    printf("south %s\n",game -> south.path);
	no->img = mlx_xpm_file_to_image(game->mlx,game->north.path,&no->width,&no->height);
	so->img = mlx_xpm_file_to_image(game->mlx,game->south.path,&so->width,&so->height);
	we->img = mlx_xpm_file_to_image(game->mlx,game->west.path,&we->width,&we->height);
	ea->img = mlx_xpm_file_to_image(game->mlx,game->east.path,&ea->width,&ea->height);
	if (!no->img || !so->img || !we->img || !ea->img)
		clean(game,NULL,"Failed to load texture\n");
	no->address = mlx_get_data_addr(no->img,&no->bpp,&no->line_length,&no->endian);
	so->address = mlx_get_data_addr(so->img,&so->bpp,&so->line_length,&so->endian);
	we->address = mlx_get_data_addr(we->img,&we->bpp,&we->line_length,&we->endian);
	ea->address = mlx_get_data_addr(ea->img,&ea->bpp,&ea->line_length,&ea->endian);
	if (!no->address || !so->address || !we->address || !ea->address)
  		clean(game,NULL,"Failed to load texture\n");
}