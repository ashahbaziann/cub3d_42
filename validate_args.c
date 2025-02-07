/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:24:26 by ashahbaz          #+#    #+#             */
/*   Updated: 2025/02/06 18:42:40 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	valid_argv(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (!str1)
		return (0);
	if (ft_strlen(str1) <= 4)
		return (0);
	while (*str1)
		str1++;
	while (*str2)
		str2++;
	while (i < 4 && *str1 == *str2)
	{
		i++;
		str1--;
		str2--;
	}
	if (i == 4)
		return (1);
	return (0);
}

int validate_args(int argc, char **argv)
{
	int	fd;

	fd = 0;
	if (argc != 2 || !valid_argv(argv[1], ".cub"))
		return (error("Invalid arguments!\n", NULL) , -1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (error("Invalid file descriptor!\n", NULL), -1);
	return (fd);
}


