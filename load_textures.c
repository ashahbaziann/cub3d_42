/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 17:08:14 by ashahbaz          #+#    #+#             */
/*   Updated: 2025/03/30 17:25:18 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_data_addr(t_game *game)
{
	t_image	*no;
	t_image	*so;
	t_image	*we;
	t_image	*ea;

	no = &game->north.image;
	so = &game->south.image;
	we = &game->west.image;
	ea = &game->east.image;
	no->address = mlx_get_data_addr(no->img, &no->bpp,
			&no->line_length, &no->endian);
	so->address = mlx_get_data_addr(so->img, &so->bpp,
			&so->line_length, &so->endian);
	we->address = mlx_get_data_addr(we->img, &we->bpp,
			&we->line_length, &we->endian);
	ea->address = mlx_get_data_addr(ea->img, &ea->bpp,
			&ea->line_length, &ea->endian);
	if (!no->address || !so->address || !we->address || !ea->address)
		clean(game, NULL, "Failed to load texture\n");
}

void	load_textures(t_game *game)
{
	game->north.image.img = mlx_xpm_file_to_image(game->mlx, game->north.path,
			&game->north.image.width, &game->north.image.height);
	game->south.image.img = mlx_xpm_file_to_image(game->mlx, game->south.path,
			&game->south.image.width, &game->south.image.height);
	game->west.image.img = mlx_xpm_file_to_image(game->mlx, game->west.path,
			&game->west.image.width, &game->west.image.height);
	game->east.image.img = mlx_xpm_file_to_image(game->mlx, game->east.path,
			&game->east.image.width, &game->east.image.height);
	if (!game->north.image.img || !game->south.image.img)
		clean(game, NULL, "Failed to load texture\n");
	if (!game->west.image.img || !game->east.image.img)
		clean(game, NULL, "Failed to load texture\n");
	get_data_addr(game);
}
